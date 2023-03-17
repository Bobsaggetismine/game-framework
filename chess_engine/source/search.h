#pragma once
#pragma once
#include <bq.h>
#include "surge/surge.h"
#include "chess_utils.h"
#include "evaluator.h"
#include "transposition_table.h"
#include "move_ordering.h"
#include "utils.h"
#include <future>
class search {
private:
	Move m_move;
	transposition_table m_tt;
	long long nodes_searched = 0;
	int sel_depth_reached = 0;
	int max_depth = 9;
	int max_sel_depth = 10;
	bool mate_found = false;
	bool stopping = false;
	Color start_color = WHITE;

public:

	void signal_stop() {
		stopping = true;
	}

	template <Color us>
	Move initiate_iterative_search(Position& p, int depth) {
		m_tt.clear();
		start_color = WHITE;
		for (int i = 1; i <= depth; ++i) {
			initiate_search<us>(p, i);
			if (stopping) return m_move;
			if (mate_found) return m_move;
		}
		
		return m_move;
	}

	template <Color us>
	Move initiate_search(Position p, int depth) {
		nodes_searched = 0;
		stopping = false;
		mate_found = false;
		sel_depth_reached = 0;
		max_depth = depth;
#if ANALYTICS
		bq::logger::info("------------------------------------------");
		bq::logger::info("searching to depth: " + std::to_string(max_depth));
		auto start = std::chrono::high_resolution_clock::now();
#endif
		int score = pvs<us>(p, depth, -checkmate_score, checkmate_score);
#if ANALYTICS
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = duration_cast<std::chrono::microseconds>(stop - start);
		float millions_of_nodes = roundf((float(nodes_searched) / 1000000.0f) * 100) / 100;
		float mnps = float(nodes_searched) / float(duration.count());
		bq::logger::info("Nodes Searched : " + format_decimal(millions_of_nodes) + "M(" + std::to_string(duration.count() / 1000000) + "S)(" + format_decimal(mnps) + "MN/S) - Selective Depth reached: " + std::to_string(sel_depth_reached) + " - Move Selection : " + m_move.str_d());
		bq::logger::info("------------------------------------------");
#endif
		return m_move;
	}



private:


	template<Color Us>
	int quiescence(Position& p, int depth, int alpha, int beta){

		if (stopping) return 0;

		sel_depth_reached = std::max(depth, sel_depth_reached);
		int score = score_board<Us>(p);

		if (score >= beta || depth == max_sel_depth) {
			return score;
		}
		if (alpha < score)
			alpha = score;

		MoveList<Us> moves(p);
		
		order_moves<Us>(p, moves, m_tt,false);
		for (Move& move : moves) {
			if (!move.is_capture()) continue;
		
			if (score + piece_values[type_of(p.at(move.to()))] + 200 < alpha) {
				continue;
			}

			p.play<Us>(move);
#if ANALYTICS
			nodes_searched++;
#endif
			int score = -quiescence<~Us>(p, depth + 1, -beta, -alpha);
			p.undo<Us>(move);
			if (score >= beta) {
				return beta;
			}
			if (score > alpha)
				alpha = score;
		}

		return alpha;
	}

	//antiquated search
	template <Color Us>
	int negamax(Position& p, int depth, int alpha, int beta) {

		if (stopping) return 0;

		int orig_alpha = alpha;

		auto tt_lookup = m_tt.lookup(p.get_hash(), depth);

		if (tt_lookup.valid && tt_lookup.score != checkmate_score && tt_lookup.score != -checkmate_score) {
			if (tt_lookup.depth >= depth) {
				if (tt_lookup.flag == TT_FLAG::EXACT) {
					return tt_lookup.score;
				}
				else if (tt_lookup.flag == TT_FLAG::LOWERBOUND) {
					alpha = std::max(alpha, tt_lookup.score);
				}
				else if (tt_lookup.flag == TT_FLAG::UPPERBOUND) {
					beta = std::min(beta, tt_lookup.score);
				}
				if (alpha > beta) {
					return tt_lookup.score;
				}
			}

		}

		if (depth == 0) {

			return quiescence<Us>(p, 0, alpha, beta);
			
		}

		bool is_pv = alpha != beta - 1;

		// Reverse futility pruning
		
		if (!is_pv && !p.in_check<Us>() && depth <= 4 ) {
			int evaluation = score_board<Us>(p);
			if (evaluation - (120 * depth) >= beta) {
				return evaluation;
			}
		}


		int max_score = -checkmate_score;
		MoveList<Us> moves(p);

		if (moves.size() == 0) {
			if (p.in_check<Us>()) {
				return -checkmate_score;
			}
			else {
				return 0;
			}
		}

		bool use_tt = depth == max_depth;
		order_moves<Us>(p, moves, m_tt, use_tt);
		for (Move move : moves) {
			p.play<Us>(move);
			#if ANALYTICS
						nodes_searched++;
			#endif
			int score = -negamax<~Us>(p, depth - 1, -beta, -alpha);
			p.undo<Us>(move);
			if (score > max_score) {
				if (depth == max_depth) {
					m_move = move;
#if ANALYTICS
					bq::logger::info("move selected: " + move.str_d() + " - score: " + std::to_string(score));
#endif
					m_tt.move_scores[move.str_d()] = score+10;
					if (max_score == checkmate_score) {
						mate_found = true;
						max_score -= depth;
					}
				}
				max_score = score;
			}
			else {
#if ANALYTICS
				if (depth == max_depth) {
					bq::logger::info("move rejected: " + move.str_d() + " - score: " + std::to_string(score));
					m_tt.move_scores[move.str_d()] = score;
				}
					
#endif
			}
			alpha = std::max(alpha, max_score);
			if (alpha >= beta)
				break;
		}
		tt_entry entry;
		entry.valid = true;
		entry.score = max_score;
		entry.depth = depth;
		if (max_score <= orig_alpha) {
			entry.flag = TT_FLAG::UPPERBOUND;
		}
		else if (max_score >= beta) {
			entry.flag = TT_FLAG::LOWERBOUND;
		}
		else {
			entry.flag = TT_FLAG::EXACT;
		}
		m_tt.insert(p.get_hash(), entry);
		return max_score;
	}

	//chad 1990s search
	template <Color Us>
	int pvs(Position& p, int depth, int alpha, int beta) {
		if (stopping) return 0;

		int orig_alpha = alpha;

		auto tt_lookup = m_tt.lookup(p.get_hash(), depth);

		if (tt_lookup.valid && tt_lookup.score != checkmate_score && tt_lookup.score != -checkmate_score) {
			if (tt_lookup.depth >= depth) {
				if (tt_lookup.flag == TT_FLAG::EXACT) {
					return tt_lookup.score;
				}
				else if (tt_lookup.flag == TT_FLAG::LOWERBOUND) {
					alpha = std::max(alpha, tt_lookup.score);
				}
				else if (tt_lookup.flag == TT_FLAG::UPPERBOUND) {
					beta = std::min(beta, tt_lookup.score);
				}
				if (alpha > beta) {
					return tt_lookup.score;
				}
			}
		}
		if (depth <= 0) {
			return quiescence<Us>(p, 0, alpha, beta);
		}

		bool is_pv = alpha != beta - 1;

		// Reverse futility pruning

		if (!is_pv && !p.in_check<Us>() && depth <= 4) {
			int evaluation = score_board<Us>(p);
			if (evaluation - (120 * depth) >= beta) {
				return evaluation;
			}
		}

		MoveList<Us> moves(p);
		order_moves<Us>(p, moves, m_tt, depth==max_depth);
		if (moves.size() == 0) {
			if (p.in_check<Us>()) {
				return -checkmate_score;
			}
			else {
				return 0;
			}
		}

		int move_num = 0;
		for (Move move : moves) {
			p.play<Us>(move);
#if ANALYTICS
			nodes_searched++;
#endif

			int move_reduct = 0;

			if (!is_pv && move_num > 2 && moves.size() > 3 && depth >= 3) {
				move_reduct = 1;
			}

			int score;
			if (move_num == 0 || p.in_check<Us>()) {
				score = -pvs<~Us>(p, (depth - 1), -beta, -alpha);

			}
			else {
				score = -pvs<~Us>(p, (depth - 1) - move_reduct, -alpha - 1, -alpha);

				if (score > alpha && move_reduct > 0) {
					score = -pvs<~Us>(p, (depth - 1), -alpha - 1, -alpha);
				}

				if (score > alpha && score < beta) {
					score = -pvs<~Us>(p, (depth - 1), -beta, -alpha);
				}
			}
			p.undo<Us>(move);
			if (score > alpha) {
				alpha = score;
				if (depth == max_depth) {
					m_move = move;
					bq::logger::info("move selected: " + move.str_d() + " - score: " + std::to_string(score));
					m_tt.move_scores[move.str_d()] = score + 10;
					if (score == checkmate_score) {
						mate_found = true;
					}
				}
			}
			else {
				if (depth == max_depth) {
					m_tt.move_scores[move.str_d()] = score;
				}
			}
			++move_num;
			if (score >= beta) return beta;
		}
		tt_entry entry;
		entry.valid = true;
		entry.score = alpha;
		entry.depth = depth;
		if (alpha <= orig_alpha) {
			entry.flag = TT_FLAG::UPPERBOUND;
		}
		else if (alpha >= beta) {
			entry.flag = TT_FLAG::LOWERBOUND;
		}
		else {
			entry.flag = TT_FLAG::EXACT;
		}
		m_tt.insert(p.get_hash(), entry);
		return alpha;
	}

};