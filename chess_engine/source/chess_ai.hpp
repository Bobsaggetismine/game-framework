#pragma once
#include "surge/position.h"
#include "surge/types.h"
#include "chess_utils.h"




struct negamax_ai_ab {

	long long nodes_searched = 0;
	
	const int checkmate_score = 100000;
	const int stalemate_score = 0;
	const int max_depth = 8;

	Move nextMove;


	template <Color Us>
	void order_moves(MoveList<Us>& moves) {
		std::sort(moves.begin(), moves.end(),
			[](Move a, Move b) -> bool
			{
				return a.is_capture() && !b.is_capture();
		});
	}

	
	
	
	template <Color Us>
	int score_board(Position& pos) {

		int score = 0;
		int black_score = 0;
		int white_score = 0;
		for (int i = PAWN; i < NPIECE_TYPES - 1;++i) {
			white_score += pop_count(pos.bitboard_of(WHITE, PieceType(i))) * piece_scores[PieceType(i)];
			black_score += pop_count(pos.bitboard_of(BLACK, PieceType(i))) * piece_scores[PieceType(i)];
		}

		score += white_score;
		score -= black_score;

		GameProgress progress = get_progress(white_score, black_score);


		int ca = 0;
		if (progress == MIDGAME) {
			ca = (Us == WHITE) ? 15 : -15;
		}

		// Center control
		int cc = 0;
		if (pos.at(d5) != NO_PIECE) cc += (color_of(pos.at(d5)) == Us) ? 25 : -25;
		if (pos.at(e5) != NO_PIECE) cc += (color_of(pos.at(e5)) == Us) ? 25 : -25;
		if (pos.at(d4) != NO_PIECE) cc += (color_of(pos.at(d4)) == Us) ? 25 : -25;
		if (pos.at(e4) != NO_PIECE) cc += (color_of(pos.at(e4)) == Us) ? 25 : -25;

		// Knight placement
		const static Bitboard edges_mask = MASK_FILE[AFILE] | MASK_RANK[RANK1] | MASK_FILE[HFILE] | MASK_RANK[RANK8];
		int np = 0;
		np -= pop_count(pos.bitboard_of(Us, KNIGHT) & edges_mask) * 50;
		np += pop_count(pos.bitboard_of(~Us, KNIGHT) & edges_mask) * 50;

		// Bishop placement
		static constexpr Bitboard black_squares = 0xAA55AA55AA55AA55;
		int bp = 0;
		for (Color color = WHITE; (int)color < 2;){

			

			unsigned short white_square_count = 0;
			unsigned short black_square_count = 0;

			Bitboard bishops = pos.bitboard_of(color, BISHOP);
			while (bishops) {
				Square bishop = pop_lsb(&bishops);

				if ((black_squares >> bishop) & 1) {
					black_square_count++;
				}
				else {
					white_square_count++;
				}

				if (white_square_count && black_square_count) {
					bp += color == Us ? 50 : -50;
					break;
				}
			}
			color = (Color)(int(color) + 1);
		}
		
		// Rook placement
		int rp = 0;
		rp += pop_count(pos.bitboard_of(Us, ROOK) & MASK_RANK[Us == WHITE ? RANK7 : RANK2]) * 30;
		rp -= pop_count(pos.bitboard_of(~Us, ROOK) & MASK_RANK[~Us == WHITE ? RANK7 : RANK2]) * 30;


		static constexpr int king_pcsq_table[64] = { 71, 86, 76, 71, 71, 76, 86, 71, 86, 71, 58, 51, 51, 58, 71, 86, 76, 58, 42, 32, 32, 42, 58, 76, 71, 51, 32, 14, 14, 32, 51, 71, 71, 51, 32, 14, 14, 32, 51, 71, 76, 58, 42, 32, 32, 42, 58, 76, 86, 71, 58, 51, 51, 58, 71, 86, 71, 86, 76, 71, 71, 76, 86, 71 };
		int kp = 0;
		if (progress == MIDGAME) {
			kp += king_pcsq_table[bsf(pos.bitboard_of(Us, KING))];
			kp -= king_pcsq_table[bsf(pos.bitboard_of(~Us, KING))];
		}

		// Doubled pawns
		int dp = 0;
		for (File file = AFILE; file < File(8);) {
			
			dp -= std::max(pop_count(pos.bitboard_of(Us, PAWN) & MASK_FILE[file]) - 1, 0) * 75;
			dp += std::max(pop_count(pos.bitboard_of(~Us, PAWN) & MASK_FILE[file]) - 1, 0) * 75;
			file = File(int(file) + 1);
		}

		// Passed pawns
		int pp = 0;
		for (Color color = WHITE; color < 2;) {
			
			Bitboard pawns = pos.bitboard_of(color, PAWN);
			while (pawns) {
				Square sq = pop_lsb(&pawns);

				Bitboard pawns_ahead_mask = MASK_FILE[file_of(sq)];
				if (file_of(sq) > AFILE) {
					pawns_ahead_mask |= MASK_FILE[file_of(sq) - 1];
				}
				if (file_of(sq) < HFILE) {
					pawns_ahead_mask |= MASK_FILE[file_of(sq) + 1];
				}

				if (color == WHITE) {
					for (Rank rank = RANK1; rank <= rank_of(sq);) {
						rank = Rank((int)rank + 1);
						pawns_ahead_mask &= ~MASK_RANK[rank];
					}
				}
				else if (color == BLACK) {
					for (Rank rank = RANK8; rank >= rank_of(sq);) {
						pawns_ahead_mask &= ~MASK_RANK[rank];
						rank = (Rank)(rank - 1);
					}
				}

				if (!(pos.bitboard_of(~color, PAWN) & pawns_ahead_mask)) {
					if (progress == MIDGAME) {
						pp += color == Us ? 30 : -30;
					}
					else if (progress == ENDGAME) {
						int score = 0;
						if (color == WHITE) {
							score = (rank_of(sq) - RANK1) * 50;
						}
						else if (color == BLACK) {
							score = (RANK8 - rank_of(sq)) * 50;
						}
						else {
							throw std::logic_error("Invalid color");
						}
						pp += color == Us ? score : -score;
					}
				}
			}
			color = Color(int(color) + 1);
		}

		// Isolated pawns
		int ip = 0;
		if (progress == MIDGAME) {
			for (Color color = WHITE; color < 2;) {
				Bitboard pawns = pos.bitboard_of(color, PAWN);
				while (pawns) {
					Square sq = pop_lsb(&pawns);

					Bitboard buddies_mask = 0;
					if (file_of(sq) > AFILE) {
						buddies_mask |= MASK_FILE[file_of(sq) - 1];
					}
					if (file_of(sq) < HFILE) {
						buddies_mask |= MASK_FILE[file_of(sq) + 1];
					}

					if (!(pos.bitboard_of(color, PAWN) & buddies_mask)) {
						ip += color == Us ? -15 : 15;
					}
				}
				color = Color(int(color) + 1);
			}
		}

		// Open files
		int of = 0;
		for (Color color = WHITE; color < NCOLORS;) {
			Bitboard rooks = pos.bitboard_of(color, ROOK);
			while (rooks) {
				Square sq = pop_lsb(&rooks);
				File file = file_of(sq);

				Bitboard pawns[NCOLORS] = {
					pos.bitboard_of(WHITE_PAWN) & MASK_FILE[file],
					pos.bitboard_of(BLACK_PAWN) & MASK_FILE[file],
				};

				if (pawns[~color]) {
					of += color == Us ? -5 : 5; // File is half-open
					if (pawns[color]) {
						of += color == Us ? -5 : 5; // File is closed
					}
				}
			}
			color = Color(int(color) + 1);
		}

		// Check status
		int cs = 0;
		if (pos.in_check<Us>()) {
			cs = -20;
		}
		else if (pos.in_check<~Us>()) {
			cs = 20;
		}
		return score + ca + cc + np + bp + rp + kp + dp + pp + ip + of + cs;



	}

	Move find_best_move(Position& p) {
		

		#if ANALYTICS
				bq::logger::info("------------------------------------------");
		#endif
		get_best_move(p, max_depth, -checkmate_score, checkmate_score);
		
		#if ANALYTICS
				bq::logger::info("nodes searched : " + std::to_string(nodes_searched));
		
				bq::logger::info("------------------------------------------");
		#endif
		nodes_searched = 0;
		return nextMove;
	}

	

	


	int get_best_move(Position p, int depth, int alpha, int beta) {

		if (depth == 0) {
			return score_board<WHITE>(p);
		}

		if (p.turn() == WHITE) {

			int max_score = -checkmate_score;
			MoveList<WHITE> moves(p);
			order_moves<WHITE>(moves);
			for (Move move : moves) {
				p.play<WHITE>(move);
				nodes_searched++;
				int score = get_best_move(p, depth - 1, alpha, beta);
				p.undo<WHITE>(move);
				
				if (score > max_score) {
					max_score = score;
					if (depth == max_depth) {
						nextMove = move;
						bq::logger::info(move.str() + " : " + std::to_string(score) + " : " + std::to_string(nodes_searched));
					}
						
				}
				if (max_score > beta)
					break;
				alpha = std::max(alpha, max_score);
				
			}
			return max_score;
		}
		else if(p.turn() == BLACK){
			int min_score = checkmate_score;
			MoveList<BLACK> moves(p);
			order_moves<BLACK>(moves);
			for (Move move : moves) {
				p.play<BLACK>(move);
				nodes_searched++;
				int score = get_best_move(p, depth - 1, alpha, beta);
				p.undo<BLACK>(move);
				
				if (score < min_score) {
					min_score = score;
					if (depth == max_depth) {
						nextMove = move;
						bq::logger::info(move.str() + " : " + std::to_string(score) + " : " + std::to_string(nodes_searched));
					}
				}
				if (min_score < alpha)
					break;
				beta = std::min(beta, min_score);
				
				
			}
			return min_score;
		}
		return -9999999;
	}
	



};