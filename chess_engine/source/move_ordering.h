#pragma once
#include "surge/surge.h"
#include "chess_utils.h"


constexpr int piece_values[NPIECE_TYPES] = {
    100,    // PAWN
    300,    // KNIGHT
    305,    // BISHOP
    500,    // ROOK
    900,    // QUEEN
    2000000 // KING
};

int sort_scores[NSQUARES][NSQUARES] = { {0} };

template <Color Us>
void order_moves(Position& p, MoveList<Us>& moves, transposition_table& tt, bool use_tt) {
    if (!use_tt) {
        std::sort(moves.begin(), moves.end(), [&](Move a, Move b) {
            int ascore = 0;
            int bscore = 0;

            if (a.is_capture())
                ascore += 10;
            if (b.is_capture())
                bscore += 10;

            if (a.flags() != QUIET) {
                ascore += 5;
            }
            if (b.flags() != QUIET) {
                bscore += 5;
            }
            //ascore += piece_values_c[p.at(a.to())] - piece_values_c[p.at(a.from())];
            //bscore += piece_values_c[p.at(b.to())] - piece_values_c[p.at(b.from())];
            return ascore > bscore;
            });
    }
    else {
        std::sort(moves.begin(), moves.end(), [&tt](Move& a, Move& b) {
            return tt.move_scores[a.str_d()] > tt.move_scores[b.str_d()];
        });
    }
    
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
