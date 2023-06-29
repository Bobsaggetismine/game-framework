#pragma once
#pragma once
#include <bq.h>
#include "includes.h"
#include "evaluator.h"
#include "transposition_table.h"
#include "move_ordering.h"
#include <future>
class search {
private:
	
	transposition_table m_tt;
	
	
	Move m_selected_move;
	long long m_nodes_searched = 0;
	int m_quinscience_depth_reached = 0;
	bool m_mate_found = false;
	bool m_stopping = false;


	int m_max_depth;
	int m_max_sel_depth;

public:

	search(int max_depth, int max_sel_depth): m_max_depth(max_depth), m_max_sel_depth(max_sel_depth){}

	void signal_stop() noexcept {
		m_stopping = true;
	}

	template <Color us>
	Move initiate_iterative_search(Position& p, int depth) {
		m_tt.clear();
		for (int i = 1; i <= depth; ++i) {
			initiate_search<us>(p, i);
			if (m_stopping) return m_selected_move;
			if (m_mate_found) return m_selected_move;
		}
		
		return m_selected_move;
	}



private:
	template <Color us>
	void initiate_search(Position& p, int depth) {
		m_nodes_searched = 0;
		m_stopping = false;
		m_mate_found = false;
		m_quinscience_depth_reached = 0;
		m_max_depth = depth;
#if ANALYTICS
		bq::logger::info("------------------------------------------");
		auto start = std::chrono::high_resolution_clock::now();
#endif
		int score = pvs<us>(p, depth, -checkmate_score, checkmate_score,false);
#if ANALYTICS
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = duration_cast<std::chrono::microseconds>(stop - start);
		float millions_of_nodes = roundf((float(m_nodes_searched) / 1000000.0f) * 100) / 100;
		float mnps = float(m_nodes_searched) / float(duration.count());
		bq::logger::info("Depth Searched: " + std::to_string(depth) + " - Nodes Searched : " + format_decimal(millions_of_nodes) + "M(" + std::to_string(duration.count() / 1000000) + "S)(" + format_decimal(mnps) + "MN / S) - Selective Depth reached : " + std::to_string(m_quinscience_depth_reached) + " - Move Selection : " + m_selected_move.str_d() + " - " + std::to_string(score));
		bq::logger::info("------------------------------------------");
#endif
	}



	template<Color Us>
	int quiescence(Position& p, int depth, int alpha, int beta){

		if (m_stopping) return 0;

		m_quinscience_depth_reached = std::max(depth, m_quinscience_depth_reached);
		int score = score_board<Us>(p);

		if (score >= beta || depth == m_max_sel_depth) {
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
			m_nodes_searched++;
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

	
	//chad 1990s search
	template <Color Us>
	int pvs(Position& p, int depth, int alpha, int beta, bool reduced) {
		if (m_stopping) return 0;

		int orig_alpha = alpha;

		auto tt_lookup = m_tt.lookup(p.get_hash(), depth);

		if (tt_lookup.valid && tt_lookup.score != checkmate_score && tt_lookup.score != -checkmate_score && depth != m_max_depth) {
			if (tt_lookup.depth >= depth) {
				if (tt_lookup.flag == tt_flag::EXACT) {
					return tt_lookup.score;
				}
				else if (tt_lookup.flag == tt_flag::LOWERBOUND) {
					alpha = std::max(alpha, tt_lookup.score);
				}
				else if (tt_lookup.flag == tt_flag::UPPERBOUND) {
					beta = std::min(beta, tt_lookup.score);
				}
			}
		}
		if (depth <= 0) {
			return quiescence<Us>(p, 0, alpha, beta);
		}

		bool is_pv = alpha != beta - 1;


		if (depth <= 4 && m_max_depth >= 7) {
			int s_eval = score_board<Us>(p);
			//razering
			if (s_eval + 190 * depth < beta) {
				int score = quiescence<Us>(p, 0, alpha, beta);
				if (score < beta)
					return score;
			}
			// Reverse futility pruning
			if (!is_pv && !p.in_check<Us>()) {
				if (s_eval - (120 * depth) >= beta) {
					return s_eval;
				}
			}
		}


		MoveList<Us> moves(p);
		order_moves<Us>(p, moves, m_tt, depth==m_max_depth);
		if (moves.size() == 0) {
			if (p.in_check<Us>()) {
				return -checkmate_score;
			}
			else {
				return 0;
			}
		}

		int move_num = 0;
		for (Move& move : moves) {
			p.play<Us>(move);
#if ANALYTICS
			m_nodes_searched++;
#endif

			int move_reduct = 0;

			if (!is_pv && move_num > 1 && moves.size() > 3 && depth >= 3 && !reduced && !move.is_capture()) {
				move_reduct = 2;
			}
			int score;
			if (move_num == 0 || p.in_check<Us>()) {
				score = -pvs<~Us>(p, (depth - 1), -beta, -alpha,reduced);

			}
			else {

				score = -pvs<~Us>(p, (depth - 1) - move_reduct, -alpha - 1, -alpha, move_reduct>0);

				if (score > alpha && move_reduct > 0) {
					score = -pvs<~Us>(p, (depth - 1), -alpha - 1, -alpha, reduced);
				}

				if (score > alpha && score < beta) {
					score = -pvs<~Us>(p, (depth - 1), -beta, -alpha,reduced);
				}
			}
			p.undo<Us>(move);
			if (score > alpha) {
				alpha = score;
				if (depth == m_max_depth) {
					m_selected_move = move;
					m_tt.move_scores[move.str_d()] = score;
					if (score == checkmate_score) {
						m_mate_found = true;
					}
				}
			}
			else {
				if (depth == m_max_depth) {
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
			entry.flag = tt_flag::UPPERBOUND;
		}
		else if (alpha >= beta) {
			entry.flag = tt_flag::LOWERBOUND;
		}
		else {
			entry.flag = tt_flag::EXACT;
		}
		m_tt.insert(p.get_hash(), entry);
		return alpha;
	}

};