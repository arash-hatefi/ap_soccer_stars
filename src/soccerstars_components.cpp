#include "../include/soccerstars_components.hpp"


GameComponents::~GameComponents()
{
	delete pitch;
	delete ball;
	for (Marble* marble:left_team) {delete marble;}
	for (Marble* marble:right_team) {delete marble;}
}

GameComponents::GameComponents()
{
	pitch = new Pitch(PITCH_WIDTH, PITCH_HEIGHT, GOAL_RELATIVE_SIZE);
	
	Vector2d<double> ball_init_position(BALL_INIT_RELATIVE_POSITION.x*pitch->get_width(), BALL_INIT_RELATIVE_POSITION.y*pitch->get_height());
	ball = new Ball(get_init_motion(ball_init_position), BALL_MASS, BALL_RADIUS, pitch);

	left_team = build_team(TEAM1_PLAYERS_INIT_RELATIVE_COORDINATES, pitch);
	right_team = build_team(TEAM2_PLAYERS_INIT_RELATIVE_COORDINATES, pitch);
}

void GameComponents::reset()
{
	Vector2d<double> ball_init_position(BALL_INIT_RELATIVE_POSITION.x*pitch->get_width(), BALL_INIT_RELATIVE_POSITION.y*pitch->get_height());
	ball->set_motion(get_init_motion(ball_init_position));
	for (int marble_idx=0; marble_idx<left_team.size(); marble_idx++) 
	{
		Vector2d<double> marble_init_position(TEAM1_PLAYERS_INIT_RELATIVE_COORDINATES[marble_idx].x*pitch->get_width(), 
			TEAM1_PLAYERS_INIT_RELATIVE_COORDINATES[marble_idx].y*pitch->get_height());
		left_team[marble_idx]->set_motion(get_init_motion(marble_init_position));
	}
	for (int marble_idx=0; marble_idx<right_team.size(); marble_idx++) 
	{
		Vector2d<double> marble_init_position(TEAM2_PLAYERS_INIT_RELATIVE_COORDINATES[marble_idx].x*pitch->get_width(), 
			TEAM2_PLAYERS_INIT_RELATIVE_COORDINATES[marble_idx].y*pitch->get_height());
		right_team[marble_idx]->set_motion(get_init_motion(marble_init_position));
	}
}

vector<Marble*> GameComponents::build_team(vector<Vector2d<double>> init_relative_positions, Pitch* pitch)
{
	vector<Marble*> team;
	for(Vector2d<double> relative_position : init_relative_positions)
	{
		Vector2d<double> init_position(relative_position.x*pitch->get_width(), relative_position.y*pitch->get_height());
		team.push_back(new Marble(get_init_motion(init_position), MARBLE_MASS, MARBLE_RADIUS, pitch));
	}
	return team;
}

Motion GameComponents::get_init_motion(Vector2d<double> position)
{
	Velocity init_velocity(Vector2d<double>(0,0), FRICTION);
	Position init_position(position);
	return Motion(init_position, init_velocity);
}