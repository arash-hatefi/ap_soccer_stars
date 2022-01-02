#ifndef __GUI__
#define __GUI__

#include "./src/rsdl.hpp"
#include "vector2d.hpp"
#include "soccerstars_components.hpp"
#include "soccerstars_parameters.hpp"
#include <vector>
#include <string>
#include <ctime>

const double RAD2DEGREE = 180./3.1415;


const string LEFT_TEAM_WON = "Left Team Won!";
const string RIGHT_TEAM_WON = "Right Team Won!";
const string DRAW = "It was a Draw!";

class GUI
{
public:

	GUI(GameComponents* _game_components);
	~GUI();
	void update_screen(int left_team_score, int right_team_score, int left_team_won_rounds, int right_team_won_rounds);
	void select_marble(Marble* marble);
	void deselect_marble();
	bool quit_game();
	Vector2d<int> get_mouse_position();
	bool left_click_pressed();
	void left_won();
	void right_won();
	void draw();


private:

	GameComponents* game_components;
	Window *window;
	Marble* selected_marble;
	Point mouse_position;
	bool left_click, quit;
	string result;

	void draw_back_dots();
	void draw_circle_dots();
	void draw_arrow();
	void draw_ball();
	void draw_marbles();
	void draw_marbles(vector<Marble*> team, string image_path);
	void draw_marble(Marble* marble, string image_path);
	void draw_pitch();
	void draw_result_boxes(int team1_score, int team2_score, int team1_won_rounds, int team2_won_rounds);
	void draw_left_result_boxes(int team1_score, int team1_won_rounds);
	void draw_right_result_boxes(int team2_score, int team2_won_rounds);
	void handle_event();
	void draw_result();
};



#endif