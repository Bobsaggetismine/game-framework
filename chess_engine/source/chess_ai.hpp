#pragma once
#include "surge/surge.h"
#include "search.h"



struct chess_ai {

	const int max_depth = 9;
	
	search s;

	chess_ai(Color Us):s(Us, max_depth) {

	}

	
	Move get_best_move(Position& p) {
		
		return s.initiate_search(p);
	}
};