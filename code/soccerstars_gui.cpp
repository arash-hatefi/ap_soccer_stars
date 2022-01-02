#include "soccerstars_gui.hpp"


GUI::GUI(GameComponents* _game_components) : game_components(_game_components)
{
	window = new Window(game_components->pitch->get_width(), game_components->pitch->get_height()*(1+RESULT_BOX_RELATIVE_HEIGHT), TITLE);
	quit = false;
	left_click = false;
	selected_marble = NULL;
}

GUI::~GUI() {delete window;}

void GUI::update_screen(int left_team_score, int right_team_score, int left_team_won_rounds, int right_team_won_rounds)
{
	window->clear();
	handle_event();
	draw_pitch();
	draw_ball();
	draw_marbles();
	draw_circle_dots();
	draw_arrow();
	draw_back_dots();
	draw_result_boxes(left_team_score, right_team_score, left_team_won_rounds, right_team_won_rounds);
	draw_result();
	window->update_screen();
}

void GUI::select_marble(Marble* marble) {selected_marble = marble;}

void GUI::deselect_marble() {selected_marble = NULL;}

bool GUI::quit_game()
{
	handle_event();
	return quit;
}

Vector2d<int> GUI::get_mouse_position()
{
	handle_event();
	return point2vector<int>(mouse_position);
}

bool GUI::left_click_pressed()
{
	handle_event();
	return left_click;
}

void GUI::left_won() {result = LEFT_TEAM_WON;}

void GUI::right_won() {result = RIGHT_TEAM_WON;}

void GUI::draw() {result = DRAW;}

void GUI::draw_back_dots()
{
	if (selected_marble==NULL) {return;}
	Vector2d<double> start_position = selected_marble->get_position_vector();
	Vector2d<double> directoion = cast<double>(get_mouse_position())-start_position;
	directoion *= min(directoion.norm(2), THROW_RADIUS)/directoion.norm(2);
	int dot_radius = selected_marble->get_radius()/4;
	int n_dots = directoion.norm(2)/(2*dot_radius);
	if (n_dots==0) {return;}
	Vector2d<double> step = directoion/n_dots;
	Vector2d<double>  position = start_position;
	for (int dot_counter=0; dot_counter<n_dots; dot_counter++)
	{
		start_position += step;
		window->fill_circle({(int)start_position.x, (int)start_position.y}, dot_radius, BACK_DOTS_COLOR);
	}
}

void GUI::draw_circle_dots()
{
	if (selected_marble==NULL) {return;}
	Vector2d<double> center = selected_marble->get_position_vector();
	double radius = (cast<double>(get_mouse_position())-center).norm(2);
	radius *= min(radius, THROW_RADIUS)/radius;
	double angle = 0;
	while (angle<2*PI)
	{
		Vector2d<double> circle_center = center + Vector2d<double>(cos(angle), sin(angle)) * radius;
		window->fill_circle({(int)circle_center.x, (int)circle_center.y}, selected_marble->get_radius()/10, DOTS_ON_SEROUNDING_CIRCLE_COLOR);
		angle += PI/(double)DOTS_ON_SEROUNDING_CIRCLE;
	}
}

void GUI::draw_arrow()
{
	if (selected_marble==NULL) {return;}
	Vector2d<double> start_position = selected_marble->get_position_vector();
	Vector2d<double> directoion = cast<double>(get_mouse_position())-start_position;
	int arrow_width = 2*selected_marble->get_radius();
	int arrow_length = 2*min(directoion.norm(2), THROW_RADIUS);
	window->draw_img(ARROW_IMG_PATH, 
		     		 Rectangle(start_position.x-(arrow_length/2), start_position.y-(arrow_width/2), arrow_length, arrow_width),
                	 NULL_RECT, directoion.angle()*RAD2DEGREE, true, false);
}

void GUI::draw_ball()
{
	Vector2d<int> ball_position = cast<int> (game_components->ball->get_position_vector());
	int ball_radius = game_components->ball->get_radius();
	int ball_diameter = 2*ball_radius;
	window->draw_img(BALL_IMG_PATH, Rectangle(ball_position.x-ball_radius, ball_position.y-ball_radius, ball_diameter, ball_diameter));
}

void GUI::draw_marbles()
{
	draw_marbles(game_components->left_team, LEFT_MARBLE_IMG_PATH);
	draw_marbles(game_components->right_team, RIGHT_MARBLE_IMG_PATH);
}

void GUI::draw_marbles(vector<Marble*> team, string image_path)
{
	for (Marble* marble : team) {draw_marble(marble, image_path);}
}

void GUI::draw_marble(Marble* marble, string image_path)
{
	Vector2d<int> marble_position = cast<int> (marble->get_position_vector());
	int marble_radius = marble->get_radius();
	int marble_diameter = 2*marble_radius;
	window->draw_img(image_path, Rectangle(marble_position.x-marble_radius, marble_position.y-marble_radius, marble_diameter, marble_diameter));
}

void GUI::draw_pitch() {window->draw_img(PITCH_IMG_PATH, Rectangle(0, 0, game_components->pitch->get_width(), game_components->pitch->get_height()));}


void GUI::draw_result_boxes(int left_team_score, int right_team_score, int left_team_won_rounds, int right_team_won_rounds)
{
	draw_left_result_boxes(left_team_score, left_team_won_rounds);
	draw_right_result_boxes(right_team_score, right_team_won_rounds);
}

void GUI::draw_left_result_boxes(int left_team_score, int left_team_won_rounds)
{
	window->fill_rect(Rectangle(game_components->pitch->get_width()/2-game_components->pitch->get_width()*RESULT_BOX_RELATIVE_WIDTH, 
					  game_components->pitch->get_height(),
					  game_components->pitch->get_width()*RESULT_BOX_RELATIVE_WIDTH,
					  game_components->pitch->get_height()*RESULT_BOX_RELATIVE_HEIGHT), LEFT_PLAYER_RESULT_BOX_COLOR);

	window->show_text(" "+std::to_string(left_team_won_rounds), 
					  Point(game_components->pitch->get_width()*(0.5-RESULT_BOX_RELATIVE_WIDTH), 
							game_components->pitch->get_height()), 
					  WHITE, 
					  FONT_PATH, ROUND_FONT_SIZE);

	window->show_text(" "+std::to_string(left_team_score), 
					  Point(game_components->pitch->get_width()*(0.5-RESULT_BOX_RELATIVE_WIDTH/2), 
							game_components->pitch->get_height()), 
					  WHITE, 
					  FONT_PATH, SCORE_FONT_SIZE);
}

void GUI::draw_right_result_boxes(int right_team_score, int right_team_won_rounds)
{
	window->fill_rect(Rectangle(game_components->pitch->get_width()/2, 
								game_components->pitch->get_height(), 
								game_components->pitch->get_width()*RESULT_BOX_RELATIVE_WIDTH, 
								game_components->pitch->get_height()*RESULT_BOX_RELATIVE_HEIGHT), RIGHT_PLAYER_RESULT_BOX_COLOR);

	window->show_text(" "+std::to_string(right_team_won_rounds), 
					  Point(game_components->pitch->get_width()/2, 
							game_components->pitch->get_height()), 
					  WHITE, 
					  FONT_PATH, ROUND_FONT_SIZE);

	window->show_text(" "+std::to_string(right_team_score), 
					  Point(game_components->pitch->get_width()*(0.5+RESULT_BOX_RELATIVE_WIDTH/2), 
							game_components->pitch->get_height()), 
					  WHITE, 
					  FONT_PATH, SCORE_FONT_SIZE);
}

void GUI::draw_result()
{
	window->show_text(" "+result, Point(0, game_components->pitch->get_height()), 
					  WHITE, FONT_PATH, ROUND_FONT_SIZE);
	window->update_screen();
}

void GUI::handle_event()
{
	while (window->has_pending_event())
	{
		Event e = window->poll_for_event();
		switch(e.get_type())
		{
			case Event::EventType::QUIT:
				quit = true;
				break;
			case Event::EventType::MMOTION:
				mouse_position = e.get_mouse_position();
				break;
			case Event::EventType::LCLICK:
				left_click = true;
				break;
			case Event::EventType::LRELEASE:
				left_click = false;
				break;
		}
	}
}