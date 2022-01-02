#ifndef __COMPONENTS__
#define __COMPONENTS__

#include "vector2d.hpp"
#include "dynamics.hpp"
#include <math.h>
#include <bits/stdc++.h>
#include <vector>


class PhysicalObject;

class Pitch
{
public:
	Pitch(int _width, int _height, double goal_relative_length);
	bool contain(const Vector2d<double>& center, double radious, double pass_goal_allowed=false);
	void reflect(Motion* motion, int radius);
	unsigned int get_width();
	unsigned int get_height();
	bool is_goal_left(const Vector2d<double> &position);
	bool is_goal_right(const Vector2d<double> &position);

private:
	unsigned int width, height, goal_down, goal_up;
};


class PhysicalObject
{
public:
	PhysicalObject(Motion motion, unsigned int _mass, unsigned int _radius, Pitch* _pitch);
	Vector2d<double> get_position_vector();
	Vector2d<double> get_velocity_vector();
	void set_velocity_vector(Vector2d<double> velocity);
	void set_motion(Motion motion);
	int get_mass();
	int get_radius();
	bool check_impact(PhysicalObject* other_object);
	bool contain(Vector2d<double> _position);
	bool motionless();

protected:
	Pitch* pitch;
	Motion motion;
	int mass, radius;
	
private:
	void impact(PhysicalObject* other_object);
};


class Ball : public PhysicalObject
{
public:
	Ball(Motion motion, int mass, int radius, Pitch* pitch);

	bool is_ball(Vector2d<double> position);
	bool is_goal_left();
	bool is_goal_right();
	void step_time(double time);
private:
};


class Marble : public PhysicalObject
{
public:
	Marble(Motion motion, int mass, int radius, Pitch* pitch);

	bool is_marble(Vector2d<double> position);
	void step_time(double time);

private:
};





#endif