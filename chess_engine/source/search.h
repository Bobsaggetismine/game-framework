#pragma once
#pragma once
#include <bq.h>
#include "surge/surge.h"
#include "chess_utils.h"
#include "evaluator.h"
#include "transposition_table.h"
#include "move_ordering.h"
class search {
private:
	Move m_move;
	long long nodes_searched = 0;
	int sel_depth_reached = 0;
	int max_depth;
	int max_sel_depth = 8;
	int max_time =  60 * 3 * 1000;
	bool mate_found = false;
	Color m_us;
	transposition_table m_tt;

public:

	search(Color us, int depth = 8) : max_depth(depth),m_us(us) {
		m_tt.load();
	}
	~search() {
		m_tt.save();
	}
private:
	
public:

	


	Move initiate_search(Position p) {
#if ANALYTICS
		bq::logger::info("------------------------------------------");
		bq::logger::info("searching to depth: " + std::to_string(max_depth));
#endif
		alpha_beta(p, max_depth, -checkmate_score, checkmate_score);
#if ANALYTICS
		bq::logger::info("nodes searched : " + std::to_string(nodes_searched / 1000) + "K" + " - selective depth: " + std::to_string(sel_depth_reached));
		bq::logger::info("------------------------------------------");
#endif
		return m_move;
	}

private:
	int calculate_attacks(Position& p, int depth, int alpha, int beta) {

		sel_depth_reached = std::max(depth, sel_depth_reached);

		if (sel_depth_reached > max_sel_depth) return score_board<WHITE>(p);

		if (p.turn() == WHITE) {
			int max_score = -checkmate_score;
			bool move_played = false;
			
			MoveList<WHITE> moves(p);

			if (moves.size() == 0) {
				if (p.in_check<WHITE>()) {
					
					return -checkmate_score;
				}
				else {
					return stalemate_score;
				}
			}
			order_moves<WHITE>(p,moves,m_tt);
			for (Move move : moves) {
				if (move.is_capture()) {
					move_played = true;
					p.play<WHITE>(move);
					#if ANALYTICS
					nodes_searched++;
					#endif
					int score = calculate_attacks(p, depth + 1, alpha, beta);
					p.undo<WHITE>(move);
					if (score > max_score) {
						max_score = score;
					}
					if (max_score > beta)
						break;
					alpha = std::max(alpha, max_score);
				}
			}
			if (!move_played) return score_board<WHITE>(p);

			return max_score;
		}
		else if (p.turn() == BLACK) {
			bool move_played = false;
			int min_score = checkmate_score;

			MoveList<BLACK> moves(p);
			if (moves.size() == 0) {
				if (p.in_check<BLACK>()) {
					
					return checkmate_score;
				}
				else {
					return stalemate_score;
				}
			}
			order_moves_reverse<BLACK>(p,moves,m_tt);
			for (Move move : moves) {
				if (move.is_capture()) {

					move_played = true;
					p.play<BLACK>(move);
					#if ANALYTICS
					nodes_searched++;
					#endif
					int score = calculate_attacks(p, depth + 1, alpha, beta);
					p.undo<BLACK>(move);
					if (score < min_score) {
						min_score = score;
					}
					
					if (min_score < alpha)
						break;

					beta = std::min(beta, min_score);
				}
			}
			if (!move_played) return score_board<WHITE>(p);
			return min_score;
		}
	}
	

	int alpha_beta(Position& p, int depth, int alpha, int beta) {

		int tt_lookup = m_tt.lookup(p.get_hash(), depth);
		if (tt_lookup != m_tt.LOOKUP_FAILED && depth!= max_depth) {
			return tt_lookup;
		}
		if (depth == 0) {
			return calculate_attacks(p, 0, alpha, beta);
		}
		


		if (p.turn() == WHITE) {

			int max_score = -checkmate_score;
			MoveList<WHITE> moves(p);

			if (moves.size() == 0) {
				if (p.in_check<WHITE>()) {
					
					return -checkmate_score;
				}
				else {
					return stalemate_score;
				}
			}
			if (depth == max_depth) {
				m_move = *moves.begin();
			}
			order_moves<WHITE>(p,moves,m_tt);
			for (Move move : moves) {
				p.play<WHITE>(move);
				#if ANALYTICS
				nodes_searched++;
				#endif
				int score = alpha_beta(p, depth - 1, alpha, beta);
				p.undo<WHITE>(move);

				if (score > max_score) {
					max_score = score;
					if (depth == max_depth) {
						m_move = move;
						if (max_score == checkmate_score) mate_found = true;
						bq::logger::info(move.str_d() + " : " + std::to_string(score) + " : " + std::to_string(nodes_searched / 1000) + "K");
					}

				}
				if (max_score > beta)
					break;
					
				alpha = std::max(alpha, max_score);

			}
			m_tt.insert(p.get_hash(), depth, max_score);
			return max_score;
		}
		else if (p.turn() == BLACK) {
			int min_score = checkmate_score;
			MoveList<BLACK> moves(p);
			if (moves.size() == 0) {
				if (p.in_check<BLACK>()) {
					return checkmate_score;
				}
				else {
					return stalemate_score;
				}
			}
			if (depth == max_depth) {
				m_move = *moves.begin();
			}
			order_moves_reverse<BLACK>(p,moves,m_tt);
			for (Move move : moves) {

				p.play<BLACK>(move);
				#if ANALYTICS
				nodes_searched++;
				#endif
				int score = alpha_beta(p, depth - 1, alpha, beta);
				p.undo<BLACK>(move);

				if (score < min_score) {
					min_score = score;
					if (depth == max_depth) {
						if (min_score == -checkmate_score) mate_found = true;
						m_move = move;
						bq::logger::info(move.str_d() + " : " + std::to_string(score) + " : " + std::to_string(nodes_searched / 1000) + "K");
					}
				}
				bool skip = max_depth != 1;
				if ((min_score < alpha) && skip)
					break;
					
				beta = std::min(beta, min_score);
			}
			m_tt.insert(p.get_hash(), depth, min_score);
			return min_score;
		}
	}
	
};



