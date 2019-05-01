/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include <algorithm>
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
std::vector<OthelloBoard*> MinimaxPlayer::successor(OthelloBoard b, char symbol)
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
* Based on pseudo  code from slide 22 on adversarial search I
*/
int MinimaxPlayer::max_value(OthelloBoard b)
{
	//terminal test
	if(b.has_legal_moves_remaining(b.get_p1_symbol()) && !b.has_legal_moves_remaining(b.get_p2_symbol())){
		return utility(b);
	}
	std::vector<OthelloBoard*> children;
	int maxVal = -999; // max = -inf
	char sym = b.get_p1_symbol();
	children = successor(b, sym);
	for(int i = 0; i < children.size(); i++){
		maxVal = std::max(maxVal, min_value(*children[i]));
	}
	return maxVal;
}

/*
* Finds lowest value move
* Based on pseudo  code from slide 22 on adversarial search I
*/
int MinimaxPlayer::min_value(OthelloBoard b)
{
	//terminal test
	if(b.has_legal_moves_remaining(b.get_p1_symbol()) && !b.has_legal_moves_remaining(b.get_p2_symbol())){
		return utility(b);
	}
	std::vector<OthelloBoard*> children;
	int minVal = 999; // min = inf
	char sym = b.get_p1_symbol();
	children = successor(b, sym);
	for(int i = 0; i < children.size(); i++){
		minVal = std::min(minVal, max_value(*children[i]));
	}
	return minVal;
}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) 
{
	int bestR = -1, bestC = -1;
	int bestMin = 100;
	int val;
	std::vector<OthelloBoard*> firstChildren = successor(*b, get_symbol());
	for(int i = 0; i < firstChildren.size(); i++){
		val = max_value(*firstChildren[i]);
		if(val < bestMin){
			bestMin = val;
			bestR = firstChildren[i]->get_row();
			bestC = firstChildren[i]->get_col();
		}
	}
	row = bestR;
	col = bestC;
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
