#ifndef __HYPERPARAMETER__
#define __HYPERPARAMETER__

#include "./src/rsdl.hpp"
#include "vector2d.hpp"
#include <string>
#include <vector>

const unsigned int SAMPLE_TIME = 30;
const unsigned int DELAY_AFTER_GOAL = 200;
const unsigned int MIN_DELAY = 15;

const string TITLE = "Soccer Stars";
const unsigned int ROUND_FONT_SIZE = 70;
const unsigned int SCORE_FONT_SIZE = 40;

const double RESULT_BOX_RELATIVE_HEIGHT = 1./10.;
const double RESULT_BOX_RELATIVE_WIDTH = 1./10.;

const unsigned int PITCH_HEIGHT = 480*2;
const unsigned int PITCH_WIDTH = 800*2;
const double GOAL_RELATIVE_SIZE = 1./3.;

const unsigned int MARBLE_RADIUS = 50;
const unsigned int MARBLE_MASS = 20;

const unsigned int BALL_RADIUS = 30;
const unsigned int BALL_MASS = 5;

const unsigned int FRICTION = 100;
const double MAX_INIT_SPEED = 500;
const double THROW_RADIUS = 200;

const int DOTS_ON_SEROUNDING_CIRCLE = 20;

const RGB DOTS_ON_SEROUNDING_CIRCLE_COLOR = {70, 70, 70};
const RGB LEFT_PLAYER_RESULT_BOX_COLOR = {255, 0, 0};
const RGB RIGHT_PLAYER_RESULT_BOX_COLOR = {0, 0, 255};
const RGB BACK_DOTS_COLOR = {0, 0, 0};

const vector<Vector2d<double>> TEAM1_PLAYERS_INIT_RELATIVE_COORDINATES = {{0.1,1./2.},{1./6.,1./4.},{1./6.,3./4.},{2./5.,2./5.},{2./5.,3./5.}};
const vector<Vector2d<double>> TEAM2_PLAYERS_INIT_RELATIVE_COORDINATES = {{0.9,1./2.},{5./6.,1./4.},{5./6.,3./4.},{3./5.,2./5.},{3./5.,3./5.}};
const Vector2d<double> BALL_INIT_RELATIVE_POSITION = {0.5,0.5};

const string PITCH_IMG_PATH = "./assets/field.jpg";
const string BALL_IMG_PATH = "./assets/ball.png";
const string LEFT_MARBLE_IMG_PATH = "./assets/Player2.png";
const string RIGHT_MARBLE_IMG_PATH = "./assets/Player1.png";
const string ARROW_IMG_PATH = "./assets/arrow.png";
const string FONT_PATH = "./assets/OpenSans.ttf";

#endif