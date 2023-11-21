#ifndef __DYNAMICS__
#define __DYNAMICS__

#include "../include/vector2d.hpp"
#include "../include/utils.hpp"

const double S2MILLIS = 1000;

class Velocity
{
public:
	Velocity();
	Velocity(Vector2d<double> _velocity, double _friction);
	void step_time(double time);
	void set_velocity_vector(Vector2d<double> _velocity);
	Vector2d<double> get_velocity_vector();
	double get_speed();
	bool motionless();

private:
	Vector2d<double> velocity;
	double friction;
};


class Position
{
public:
	Position();
	Position(Vector2d<double> _position);
	void step_time(Velocity velocity, double time);
	void set_position_vector(Vector2d<double> _position);
	Vector2d<double> get_position_vector();

private:
	Vector2d<double> position;
};


class Motion
{
public:
	Motion();

	Motion(Position _position, Velocity _velocity);
	Vector2d<double> get_position_vector();
	Vector2d<double> get_velocity_vector();
	void set_position_vector(Vector2d<double> _velocity);
	void set_velocity_vector(Vector2d<double> _velocity);
	void step_time(double time);
	bool motionless();

private:
	Position position;
	Velocity velocity;
};



#endif