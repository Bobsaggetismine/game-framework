#pragma once

#include "surge/surge.h"
#include "chess_utils.hpp"
#include "utils.hpp"
class book {

	std::vector<Move> m_move_history;
	std::vector<std::vector<std::string>> m_games;
	
public:

	book();
	
	void reset();
	void add_move(Move move);

	template <Color Us>
	Move get_book_move(Position& p)
	{
		
		for (auto& game : m_games) {
			if (m_move_history.size() >= game.size()) continue;
			bool this_game = true;
			for (auto i = 0; i < m_move_history.size(); ++i) {
				if (m_move_history[i].str() != game[i]) {
					this_game = false;
				}
			}
			if (this_game) {
				auto next_move_str = game[m_move_history.size()];
				MoveList<Us> moves(p);
				for (auto& move : moves) {
					if (move.str() == next_move_str) {
						return move;
					}
				}
			}
		}
		return Move();
	}

};