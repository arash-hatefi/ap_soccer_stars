#ifndef __SOCCERSTARS__
#define __SOCCERSTARS__

#include "soccerstars_gui.hpp"
#include "soccerstars_components.hpp"
#include "components.hpp"
#include "vector2d.hpp"
#include "soccerstars_parameters.hpp"

#define EXIT 0

const string SOCCERSTAR_INPUT_ERROR = "Invalied input for SoccerStar!";


const double MICRO2MILLI = 0.001;

class SoccerStars
{

public:
	SoccerStars(int _n_rounds, int _goals_to_win);
	~SoccerStars();
	void play();

private:

	GameComponents* game_components;	
	GUI* gui;
	bool left_team_turn, game_finish, motionless_condition;
	int left_team_score, right_team_score, left_team_won_rounds, right_team_won_rounds, n_rounds, goals_to_win;

	void finish_last_move();
	void step_time(double time);
	void wait_until_click();
	void get_input_velocity();
	void tuggle_turn();
	void set_velocity(Marble* marble, Vector2d<double> velocity);
	Marble* find_marble(Vector2d<int> position);
	Marble* find_marble(Vector2d<double> position);
	Vector2d<double> compute_velocity(Vector2d<int> mouse_position, Vector2d<int> marble_position);
	void set_sample_delay(int execution_time);
	unsigned int get_time();
	void ball_step_time(double time);
	void team_step_time(vector<Marble*> team, double time);
	void check_impact(PhysicalObject* object);
	void check_goal();
	void check_goal_for_left();
	void check_goal_for_right();
	void reset_game();
	bool motionless();

};


#endif