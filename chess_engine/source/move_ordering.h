#pragma once
#include "includes.h"



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