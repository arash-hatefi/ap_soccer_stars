#ifndef __SOCCERSTARS_COMPONENTS__
#define __SOCCERSTARS_COMPONENTS__

#include "vector2d.hpp"
#include "components.hpp"
#include "soccerstars_parameters.hpp"
#include "dynamics.hpp"

struct GameComponents
{
	GameComponents();
	~GameComponents();
	void reset();
	vector<Marble*> build_team(vector<Vector2d<double>> init_relative_positions, Pitch* pitch);
	Motion get_init_motion(Vector2d<double> position);

	Ball* ball;
	Pitch* pitch;
	vector<Marble*> left_team;
	vector<Marble*> right_team;
};

#endif
