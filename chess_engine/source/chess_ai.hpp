#pragma once
#include "surge/surge.h"
#include "search.h"



struct chess_ai {

	const int max_depth;
	
	search s;

	chess_ai(int depth): max_depth(depth) {}

	void signal_stop() {
		s.signal_stop();
	}

	Move get_best_move(Position& p) {
		if (p.turn() == WHITE) {
			return s.initiate_iterative_search<WHITE>(p, max_depth);
		}
		else {
			return s.initiate_iterative_search<BLACK>(p, max_depth);
		}
	}
};