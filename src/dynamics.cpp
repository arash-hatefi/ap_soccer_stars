#include "../include/dynamics.hpp"


Velocity::Velocity() {}

Velocity::Velocity(Vector2d<double> _velocity, double _friction) : 
friction(_friction) {velocity = Vector2d<double>(_velocity.x, _velocity.y);}

void Velocity::step_time(double time)
{
	double speed = get_speed();
	if (speed==0) {return;}
	double temp = speed-(double)friction*time/1000000;
	if (sgn(speed)!=sgn(temp)) {set_velocity_vector(Vector2d<double>(0, 0));}
	else {velocity *= (temp/speed);}
}

void Velocity::set_velocity_vector(Vector2d<double> _velocity) {velocity = _velocity;}

Vector2d<double> Velocity::get_velocity_vector() {return velocity;}

double Velocity::get_speed() {return velocity.norm(2);}

bool Velocity::motionless()
{
	if (get_speed()==0) {return true;}
	return false;
}

Position::Position() {}

Position::Position(Vector2d<double> _position) {position = Vector2d<double>(_position.x, _position.y);}

void Position::step_time(Velocity velocity, double time) {position += velocity.get_velocity_vector()*time;}

void Position::set_position_vector(Vector2d<double> _position) {position = _position;}

Vector2d<double> Position::get_position_vector() {return position;}

Motion::Motion() {};

Motion::Motion(Position _position, Velocity _velocity) : position(_position), velocity(_velocity) {}

Vector2d<double> Motion::get_position_vector() {return position.get_position_vector();}

Vector2d<double> Motion::get_velocity_vector() {return velocity.get_velocity_vector();}

void Motion::set_position_vector(Vector2d<double> _position) {position.set_position_vector(_position);}

void Motion::set_velocity_vector(Vector2d<double> _velocity) {velocity.set_velocity_vector(_velocity);}

void Motion::step_time(double time)
{
	if (velocity.get_speed()==0) {return;}
	position.step_time(velocity, time);
	velocity.step_time(time);
}

bool Motion::motionless()
{
	if (velocity.motionless())
		return true;
	return false;
}