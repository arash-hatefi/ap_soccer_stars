#include <iostream>
#include "soccerstars.hpp"

using namespace std;


int main(int argc, char **argv)
{
	try
	{
		int n_rounds = stoi(argv[1]);
		int goals_to_win = stoi(argv[2]);
		SoccerStars game(n_rounds, goals_to_win);
		game.play();
	}
	catch(string error) {cerr<<error<<endl;}
	return 0;
}