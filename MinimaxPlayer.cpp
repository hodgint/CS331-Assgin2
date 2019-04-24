/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

/* Utility Functions */

/*
* Gets the current score
*/
int MinimaxPlayer::utility(OthelloBoard b)
{
	return (b.count_score(b.get_p1_symbol()) - b.count_score(b.get_p2_symbol()));
}

/* 
* Gets all successors for the current move
*/
std::vector<OthelloBoard*> successor(OthelloBoard b, char symbol)
{
	std::vector<OthelloBoard*> valid;
	int i, j;
	for(i = 0; i < b.get_num_rows(); i++){
		for(j = 0; j < b.get_num_cols(); j++){
			if(b.is_legal_move(j, i, symbol) && b.is_cell_empty(j, i)){
				OthelloBoard *temp = new OthelloBoard(b);
				temp->play_move(j, i, symbol);
				temp->set_row(i);
				temp->set_col(j);
				valid.push_back(temp);
			}
		}
	}
	return valid;
}

/*
* finds max value move
*/
int MinimaxPlayer::max_value(OthelloBoard b)
{
	
}

/*
* Finds lowest value move
*/
int MinimaxPlayer::min_value(OthelloBoard b)
{

}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
