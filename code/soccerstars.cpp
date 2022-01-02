#include "soccerstars.hpp"

SoccerStars::SoccerStars(int _n_rounds, int _goals_to_win)
{
	if (_n_rounds<=0 || _goals_to_win<=0) {throw(SOCCERSTAR_INPUT_ERROR);}
	n_rounds = _n_rounds;
	goals_to_win = _goals_to_win;
	game_components = new GameComponents();
	gui = new GUI(game_components);
	left_team_score = 0;
	right_team_score = 0;
	left_team_won_rounds = 0;
	right_team_won_rounds = 0;
	left_team_turn = true;
	motionless_condition = true;
	game_finish = false;
}

SoccerStars::~SoccerStars()
{
	delete gui;
	delete game_components;
}

void SoccerStars::play()
{
	while (true)
	{
		try
		{
			if(game_finish)
			{
				while(!gui->quit_game());
				throw(EXIT);
			}
			wait_until_click();
			get_input_velocity();
			finish_last_move();
		}
		catch(...){break;}
	}
}

void SoccerStars::finish_last_move()
{
	while (!motionless_condition)
	{
		if (!gui->quit_game())
		{
			clock_t ref = get_time();
			step_time(SAMPLE_TIME);
			set_sample_delay((int)(get_time()-ref));
			gui->update_screen(left_team_score, right_team_score, left_team_won_rounds, right_team_won_rounds);
		}
		else {throw(EXIT);}
	}
}

void SoccerStars::step_time(double time)
{
	if (motionless_condition) {return;}

	ball_step_time(time);
	team_step_time(game_components->left_team, time);
	team_step_time(game_components->right_team, time);
	if (motionless()) {motionless_condition = true;}
	check_goal();
}

void SoccerStars::wait_until_click() 
{
	gui->update_screen(left_team_score, right_team_score, left_team_won_rounds, right_team_won_rounds);
	while (!gui->left_click_pressed()) {if (gui->quit_game()) {throw(EXIT);}}
}

void SoccerStars::get_input_velocity()
{

	Vector2d<int> mouse_init_position, mouse_final_position;
	mouse_init_position = gui->get_mouse_position();
	Marble* selected_marble = find_marble(mouse_init_position);
	gui->select_marble(selected_marble);
	while (gui->left_click_pressed())
	{
		gui->update_screen(left_team_score, right_team_score, left_team_won_rounds, right_team_won_rounds);
		mouse_final_position = gui->get_mouse_position();
	}
	gui->deselect_marble();
	if (selected_marble==NULL) {return;}
	Vector2d<double> velocity = compute_velocity(mouse_final_position, cast<int>(selected_marble->get_position_vector()));
	set_velocity(selected_marble, velocity);
	tuggle_turn();		
}

void SoccerStars::tuggle_turn() {left_team_turn = !left_team_turn;}

void SoccerStars::set_velocity(Marble* marble, Vector2d<double> velocity)
{
	marble->set_velocity_vector(velocity);
	motionless_condition=false;
}

Marble* SoccerStars::find_marble(Vector2d<int> position) {return find_marble(cast<double>(position));}

Marble* SoccerStars::find_marble(Vector2d<double> position)
{
	vector<Marble*> *team = (left_team_turn) ? &(game_components->left_team) : &(game_components->right_team);
	for (Marble* marble : *team) {if(marble->is_marble(position)) {return marble;}}
	return NULL;
}


Vector2d<double> SoccerStars::compute_velocity(Vector2d<int> mouse_position, Vector2d<int> marble_position)
{
	Vector2d<int> d = mouse_position - marble_position;
	double norm_d = d.norm(2);
	return cast<double>(d) * (-MAX_INIT_SPEED/max(THROW_RADIUS, norm_d)) / S2MILLIS;
}

void SoccerStars::set_sample_delay(int execution_time) {delay(max((int)(SAMPLE_TIME-execution_time-MIN_DELAY),0));}

unsigned int SoccerStars::get_time() {return (unsigned int)(clock()*MICRO2MILLI);}

void SoccerStars::ball_step_time(double time)
{
	game_components->ball->step_time(time);
	if (!game_components->ball->motionless()) {check_impact(game_components->ball);}
}

void SoccerStars::team_step_time(vector<Marble*> team, double time)
{
	for (int idx=0; idx<team.size(); idx++)
	{
		if(!team[idx]->motionless()) 
		{
			team[idx]->step_time(time);
			if (!team[idx]->motionless()) {check_impact(team[idx]);}
		}	
	}
}

void SoccerStars::check_impact(PhysicalObject* object)
{
	for (Marble* marble : game_components->left_team)
	{
		if (object==marble) {continue;}
		if (marble->check_impact(object)) {return;}
	}
	for (Marble* marble : game_components->right_team)
	{
		if (object==marble) {continue;}
		if (marble->check_impact(object)) {return;}
	}
	if (object==game_components->ball) {return;}
	if (object->check_impact(game_components->ball)) {return;}
}

void SoccerStars::reset_game()
{
	game_components->reset();
	left_team_turn = true;
}


void SoccerStars::check_goal()
{
	check_goal_for_left();
	check_goal_for_right();
	if(left_team_won_rounds+right_team_won_rounds==n_rounds)
	{
		if(left_team_won_rounds>right_team_won_rounds) {gui->left_won();}
		else if(right_team_won_rounds>left_team_won_rounds) {gui->right_won();}
		else {gui->draw();}
		game_finish = true;
	}
}

void SoccerStars::check_goal_for_left()
{
	if (game_components->ball->is_goal_right())
	{
		delay(DELAY_AFTER_GOAL);
		reset_game();
		left_team_score++;
		left_team_won_rounds += (int) (left_team_score/goals_to_win);
		left_team_score %=goals_to_win;
	}
}

void SoccerStars::check_goal_for_right()
{
	if (game_components->ball->is_goal_left())
	{
		delay(DELAY_AFTER_GOAL);
		reset_game();
		right_team_score++;
		right_team_won_rounds += (int) (right_team_score/goals_to_win);
		right_team_score %=goals_to_win;
	}
}

bool SoccerStars::motionless()
{
	for (Marble* marble : game_components->left_team) {if (!marble->motionless()) {return false;}}
	for (Marble* marble : game_components->right_team) {if (!marble->motionless()) {return false;}}
	if (!game_components->ball->motionless()) {return false;}
	return true;
}