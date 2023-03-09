#pragma once
#include "surge/surge.h"

template <Color Us>
void order_moves(Position& p, MoveList<Us>& moves, transposition_table& m_tt) {

		std::sort(moves.begin(), moves.end(),
			[&](Move& a, Move& b) mutable -> bool
			{
				return a.is_capture() && !b.is_capture();
			});
}

template <Color Us>
void order_moves_reverse(Position& p, MoveList<Us>& moves, transposition_table& m_tt) {

		std::sort(moves.begin(), moves.end(),
			[&](Move& a, Move& b) mutable -> bool
			{
				return a.is_capture() && !b.is_capture();
			});
}
/*
* template <Color Us>
void swap_if_contains(MoveList<Us>& movelist) {
	for (Move* i = movelist.list; i != movelist.last; ++i) {
		if ((*i) == m_move) {
			Move temp = movelist.list[0];
			movelist.list[0] = m_move;
			(*i) = temp;
			break;
		}
	}
}
*/
