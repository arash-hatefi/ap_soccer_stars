#include "../include/components.hpp"

using namespace std;


Pitch::Pitch(int _width, int _height, double goal_relative_length) : width(_width), height(_height) 
{
	goal_up = height * (0.5 + goal_relative_length/2);
	goal_down = height * (0.5 - goal_relative_length/2);
}

bool Pitch::contain(const Vector2d<double>& center, double radious, double pass_goal_allowed)
{
	if (pass_goal_allowed) {if (center.y<=goal_up && center.y>=goal_down) {return true;}}
	if (center.x<=width-radious && 
		center.y<=height-radious &&
		center.x>=radious && 
		center.y>=radious)
		return true;
	return false;
}

void Pitch::reflect(Motion* motion, int radius)
{
	Vector2d<double> p = motion->get_position_vector();
	Vector2d<double> v = motion->get_velocity_vector();

	if (p.x>width-radius || p.x<radius) {v.x=-v.x;}
	if (p.y>height-radius || p.y<radius) {v.y=-v.y;}

	if (p.x>width-radius) {p.x = 2*(width-radius)-p.x;}
	else if (p.x<radius) {p.x = 2*(radius)-p.x;}

	if (p.y>height-radius) {p.y = 2*(height-radius)-p.y;}
	else if (p.y<radius) {p.y = 2*(radius)-p.y;}

	motion->set_velocity_vector(v);
	motion->set_position_vector(p);
}

unsigned int Pitch::get_width() {return width;}

unsigned int Pitch::get_height() {return height;}

bool Pitch::is_goal_left(const Vector2d<double> &position)
{
	if (position.y<=goal_up && position.y>=goal_down && position.x<=0)
		return true;
	return false;
}

bool Pitch::is_goal_right(const Vector2d<double> &position)
{
	if (position.y<=goal_up && position.y>=goal_down && position.x>=width)
		return true;
	return false;
}

PhysicalObject::PhysicalObject(Motion _motion, unsigned int _mass, unsigned int _radius, Pitch* _pitch) : 
motion(_motion), mass(_mass), radius(_radius), pitch(_pitch) {}

Vector2d<double> PhysicalObject::get_position_vector() {return motion.get_position_vector();}

Vector2d<double> PhysicalObject::get_velocity_vector() {return motion.get_velocity_vector();}

void PhysicalObject::set_velocity_vector(Vector2d<double> velocity) {motion.set_velocity_vector(velocity);}

void PhysicalObject::set_motion(Motion _motion) {motion=_motion;}

int PhysicalObject::get_mass() {return mass;}

int PhysicalObject::get_radius() {return radius;}

bool PhysicalObject::check_impact(PhysicalObject* other_object)
{
	Vector2d<double> center2center_vec = other_object->get_position_vector() - get_position_vector();
	double center2center_distance = center2center_vec.norm(2);
	if (center2center_distance < other_object->get_radius()+get_radius()) 
	{
		if (get_angle(center2center_vec, get_velocity_vector()) <= atan((double)other_object->get_radius()/center2center_distance) ||
			get_angle(center2center_vec*(-1), other_object->get_velocity_vector()) <= atan((double)get_radius()/center2center_distance))
		{		
			impact(other_object);
			return true;
		}
	}
	return false;
}

bool PhysicalObject::contain(Vector2d<double> _position)
{
	if(distance(get_position_vector(), _position)<get_radius()) {return true;}
	return false;
}

bool PhysicalObject::motionless()
{
	if (motion.motionless()) {return true;}
	return false;
}

void PhysicalObject::impact(PhysicalObject* other_object)
{
	double m1 = (double) get_mass();
	Vector2d<double> v1 = get_velocity_vector();
	Vector2d<double> x1 = get_position_vector();

	double m2 = (double) other_object->get_mass();
	Vector2d<double> v2 = other_object->get_velocity_vector();
	Vector2d<double> x2 = other_object->get_position_vector();

	Vector2d<double> temp = (x1-x2)*2*dot(v1-v2,x1-x2)/pow((x1-x2).norm(2), 2)/(m1+m2);
	Vector2d<double> new_v1 = v1-temp*m2;
	Vector2d<double> new_v2 = v2+temp*m1;

	set_velocity_vector(new_v1);
	other_object -> set_velocity_vector(new_v2);
}

Ball::Ball(Motion motion, int mass, int radius, Pitch *pitch) : 
PhysicalObject(motion, mass, radius, pitch) {}

bool Ball::is_ball(Vector2d<double> position) {return contain(position);}

bool Ball::is_goal_left() {return pitch->is_goal_left(get_position_vector());}

bool Ball::is_goal_right() {return pitch->is_goal_right(get_position_vector());}

void Ball::step_time(double time)
{
	motion.step_time(time);
	while (!pitch->contain(get_position_vector(), radius, true)) {pitch->reflect(&motion, radius);}
}

Marble::Marble(Motion motion, int mass, int radius, Pitch *pitch) : 
PhysicalObject(motion, mass, radius, pitch) {}

bool Marble::is_marble(Vector2d<double> position) {return contain(position);}

void Marble::step_time(double time)
{
	motion.step_time(time);
	while (!pitch->contain(get_position_vector(), radius, false)) {pitch->reflect(&motion, radius);}
}