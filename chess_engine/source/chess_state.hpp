#pragma once
#include <bq.h>



#include "enums.h"
#include "chess_move.hpp"
#include "castle_rights.hpp"


struct check_pin_info {
	bool in_check;
	std::vector<bq::v4i> checks;
	std::vector<bq::v4i> pins;
};




struct chess_state {

	std::vector<std::vector<piece_t>> board = {
		{
			{color::black, piece::rook},{color::black, piece::knight},{color::black, piece::bishop},{color::black, piece::queen},{color::black, piece::king},{color::black, piece::bishop},{color::black, piece::knight},{color::black, piece::rook}
		},
		{
			{color::black, piece::pawn},{color::black, piece::pawn},{color::black, piece::pawn},{color::black, piece::pawn},{color::black, piece::pawn},{color::black, piece::pawn},{color::black, piece::pawn},{color::black, piece::pawn}
		},
		{
			{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none}
		},
		{
			{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none}
		},
		{
			{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none}
		},
		{
			{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none},{color::none, piece::none}
		},
		{
			{color::white, piece::pawn},{color::white, piece::pawn},{color::white, piece::pawn},{color::white, piece::pawn},{color::white, piece::pawn},{color::white, piece::pawn},{color::white, piece::pawn},{color::white, piece::pawn}
		},
		{
			{color::white, piece::rook},{color::white, piece::knight},{color::white, piece::bishop},{color::white, piece::queen},{color::white, piece::king},{color::white, piece::bishop},{color::white, piece::knight},{color::white, piece::rook}
		}
	};
	std::vector<chess_move> move_log;
	std::vector<castle_rights> castle_rights_log;

	std::map<piece, std::string> piece_string_map = { {piece::rook, "R"},{piece::bishop,"B"},{piece::knight,"N"} ,{piece::queen,"Q"} ,{piece::king,"K"} ,{piece::pawn,"P"} };
	std::map<color, std::string> color_string_map = { {color::black,"b"},{color::white,"w"} };

	bool white_to_move = true;
	bool in_check = false;
	bool checkmate = false;
	bool stalemate = false;




	bq::v2i enpassant_possible = { -1,-1 };
	bq::v2i white_king_pos = {7,4};
	bq::v2i black_king_pos = {0,4};

	std::vector<bq::v2i> white_rooks = { {7,0},{7,7} };
	std::vector<bq::v2i> black_rooks = { {0,0},{0,7} };

	std::vector<bq::v2i> white_bishops = { {7,2},{7,5} };
	std::vector<bq::v2i> black_bishops = { {0,2},{0,5} };

	std::vector<bq::v2i> white_knights = { {7,1},{7,6} };
	std::vector<bq::v2i> black_knights = { {0,1},{0,6} };

	std::vector<bq::v2i> white_queens = { {7,3} };
	std::vector<bq::v2i> black_queens = { {0,3} };



	check_pin_info check_pin_information = { false, {}, {} };
	castle_rights current_castling_rights = castle_rights(true, true, true, true);
	
	piece_t empty_piece = std::make_pair<color, piece>(color::none, piece::none);
	
	piece_t white_pawn = std::make_pair<color, piece>(color::white, piece::pawn);
	piece_t black_pawn = std::make_pair<color, piece>(color::black, piece::pawn);

	piece_t white_rook = std::make_pair<color, piece>(color::white, piece::rook);
	piece_t black_rook = std::make_pair<color, piece>(color::black, piece::rook);

	piece_t white_bishop = std::make_pair<color, piece>(color::white, piece::bishop);
	piece_t black_bishop = std::make_pair<color, piece>(color::black, piece::bishop);

	piece_t white_knight = std::make_pair<color, piece>(color::white, piece::knight);
	piece_t black_knight = std::make_pair<color, piece>(color::black, piece::knight);

	piece_t white_queen = std::make_pair<color, piece>(color::white, piece::queen);
	piece_t black_queen = std::make_pair<color, piece>(color::black, piece::queen);

	piece_t white_king = std::make_pair<color, piece>(color::white, piece::king);
	piece_t black_king = std::make_pair<color, piece>(color::black, piece::king);


	check_pin_info calc_checks_and_pins()
	{
		std::vector<bq::v4i> pins;
		std::vector<bq::v4i> checks;
		bool in_check = false;
		color enemy_color, ally_color;
		int start_row, start_col;

		if (this->white_to_move) {
			enemy_color = color::black;
			ally_color = color::white;
			start_row = this->white_king_pos.x;
			start_col = this->white_king_pos.y;
		}
		else {
			enemy_color = color::white;
			ally_color = color::black;
			start_row = this->black_king_pos.x;
			start_col = this->black_king_pos.y;
		}

		std::vector<bq::v2i> directions = { {-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

		for (int j = 0; j < directions.size(); j++) {
			auto direction = directions[j];
			bq::v4i possible_pin = {0,0,0,0};
			for (int i = 1; i < 8; i++) {
				int end_row = start_row + direction.x * i;
				int end_col = start_col + direction.y * i;
				if (0 <= end_row && end_row <= 7 && 0 <= end_col && end_col <= 7) {
					auto end_piece = this->board[end_row][end_col];
					if (end_piece.first == ally_color && end_piece.second != piece::king) {
						if (possible_pin == bq::v4i(0, 0, 0, 0)) {
							possible_pin = bq::v4i(end_row, end_col, direction.x, direction.y);
						}
						else {
							break;
						}
					}
					else if (end_piece.first == enemy_color) {
						piece enemy_type = end_piece.second;
						if ((j >= 0 && j <= 3 && enemy_type == piece::rook) || (j >= 4 && j <= 7 && enemy_type == piece::bishop) || (i == 1 && enemy_type == piece::pawn && ((enemy_color == color::white && j >= 6 && j<=7) || (enemy_color == color::black && j <= 5 && j >=4))) || (enemy_type == piece::queen) || (i == 1 && enemy_type == piece::king)) {
							if (possible_pin == bq::v4i(0, 0, 0, 0)) {
								in_check = true;
								checks.push_back(bq::v4i(end_row, end_col, direction.x, direction.y));
								break;
							}
							else {
								pins.push_back(possible_pin);
								break;
							}
						}
						else {
							break;
						}
					}
					else {
						continue;
					}
				}
				else {
					break;
				}
			}
		}
		std::vector<bq::v2i> knight_moves = { {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, -1}, {2, 1}, {-1, -2}, {1, -2} };
		for (auto move : knight_moves) {
			int end_row = start_row + move.x;
			int end_col = start_col + move.y;
			if (end_row >= 0 && end_row < 8 && end_col >= 0 && end_col < 8) {
				auto end_piece = board[end_row][end_col];
				if (end_piece.first == enemy_color && end_piece.second == piece::knight) {
					in_check = true;
					checks.push_back({ end_row, end_col, move.x, move.y });
				}
			}
		}
		check_pin_info cpi = { in_check, checks, pins };
		return cpi;
	}

	void update_castling_rights(chess_move move)
	{
		if (move.piece_captured == white_rook) {
			if (move.end_col == 0) {
				this->current_castling_rights.wqs = false;
			}
			else if (move.end_col == 7) {
				this->current_castling_rights.wks = false;
			}
		}
		else if (move.piece_captured == black_rook) {
			if (move.end_col == 0) {
				this->current_castling_rights.bqs = false;
			}
			else if (move.end_col == 7) {
				this->current_castling_rights.bks = false;
			}
		}

		if (move.piece_moved == white_king) {
			this->current_castling_rights.wqs = false;
			this->current_castling_rights.wks = false;
		}
		else if (move.piece_moved == black_king) {
			this->current_castling_rights.bqs = false;
			this->current_castling_rights.bks = false;
		}
		else if (move.piece_moved == white_rook) {
			if (move.start_row == 7) {
				if (move.start_col == 0) {
					this->current_castling_rights.wqs = false;
				}
				else if (move.start_col == 7) {
					this->current_castling_rights.wks = false;
				}
			}
		}
		else if (move.piece_moved == black_rook) {
			if (move.start_row == 0) {
				if (move.start_col == 0) {
					this->current_castling_rights.bqs = false;
				}
				else if (move.start_col == 7) {
					this->current_castling_rights.bks = false;
				}
			}
		}
	}

	void update_piece_positions_on_move(chess_move& move,piece_t piece_captured,piece_t piece_moved, int start_row, int start_col, int end_row, int end_col) {
		
		//remembered pos updates
		if (move.piece_moved == white_king) {
			white_king_pos = bq::v2i(end_row, end_col);
		}
		else if (piece_moved == black_king) {
			black_king_pos = bq::v2i(end_row, end_col);
		}
		else if (piece_moved == white_rook) {
			for (auto& rook : white_rooks) {
				if (rook.x == start_row && rook.y == start_col) {
					rook.x = end_row;
					rook.y = end_col;
				}
			}
		}
		else if (piece_moved == black_rook) {
			for (auto& rook : black_rooks) {
				if (rook.x == start_row && rook.y == start_col) {
					rook.x = end_row;
					rook.y = end_col;
				}
			}
		}
		else if (piece_moved == white_bishop) {
			for (auto& bishop : white_bishops) {
				if (bishop.x == start_row && bishop.y == start_col) {
					bishop.x = end_row;
					bishop.y = end_col;
				}
			}
		}
		else if (piece_moved == black_bishop) {
			for (auto& bishop : black_bishops) {
				if (bishop.x == start_row && bishop.y == start_col) {
					bishop.x = end_row;
					bishop.y = end_col;
				}
			}
		}
		else if (piece_moved == white_queen) {
			for (auto& p : white_queens) {
				if (p.x == start_row && p.y == start_col) {
					p.x = end_row;
					p.y = end_col;
				}
			}
		}
		else if (piece_moved == black_queen) {
			for (auto& p : black_queens) {
				if (p.x == start_row && p.y == start_col) {
					p.x = end_row;
					p.y = end_col;
				}
			}
		}



		//dead rook rembered positions
		if (piece_captured == white_rook) {
			for (auto& rook : white_rooks) {
				if (rook.x == end_row && rook.y == end_col) {
					rook.x = -1;
					rook.y = -1;
				}
			}
		}
		else if (piece_captured == black_rook) {
			for (auto& rook : black_rooks) {
				if (rook.x == end_row && rook.y == end_col) {
					rook.x = -1;
					rook.y = -1;
				}
			}
		}
		//dead bishop rembered positions
		else if (piece_captured == white_bishop) {
			for (auto& bishop : white_bishops) {
				if (bishop.x == end_row && bishop.y == end_col) {
					bishop.x = -1;
					bishop.y = -1;
				}
			}
		}
		else if (piece_captured == black_bishop) {
			for (auto& bishop : black_bishops) {
				if (bishop.x == end_row && bishop.y == end_col) {
					bishop.x = -1;
					bishop.y = -1;
				}
			}
		}
		//dead queens
		else if (piece_captured == white_queen) {
			for (auto& bishop : white_queens) {
				if (bishop.x == end_row && bishop.y == end_col) {
					bishop.x = -1;
					bishop.y = -1;
				}
			}
		}
		else if (piece_captured == black_queen) {
			for (auto& bishop : black_queens) {
				if (bishop.x == end_row && bishop.y == end_col) {
					bishop.x = -1;
					bishop.y = -1;
				}
			}
		}
	}
	void update_piece_positions_on_undo(chess_move& move) {
		//rooks
		if (move.piece_moved == black_rook) {
			for (auto& rook : black_rooks) {
				if (rook.x == move.end_row && rook.y == move.end_col) {
					rook.x = move.start_row;
					rook.y = move.start_col;
				}
			}
		}
		else if (move.piece_moved == white_rook) {
			for (auto& rook : white_rooks) {
				if (rook.x == move.end_row && rook.y == move.end_col) {
					rook.x = move.start_row;
					rook.y = move.start_col;
				}
			}
		}
		//bishops
		else if (move.piece_moved == black_bishop) {
			for (auto& bishop : black_bishops) {
				if (bishop.x == move.end_row && bishop.y == move.end_col) {
					bishop.x = move.start_row;
					bishop.y = move.start_col;
				}
			}
		}
		else if (move.piece_moved == white_bishop) {
			for (auto& bishop : white_bishops) {
				if (bishop.x == move.end_row && bishop.y == move.end_col) {
					bishop.x = move.start_row;
					bishop.y = move.start_col;
				}
			}
		}
		//queens
		else if (move.piece_moved == black_queen) {
			for (auto& bishop : black_queens) {
				if (bishop.x == move.end_row && bishop.y == move.end_col) {
					bishop.x = move.start_row;
					bishop.y = move.start_col;
				}
			}
		}
		else if (move.piece_moved == white_queen) {
			for (auto& bishop : white_queens) {
				if (bishop.x == move.end_row && bishop.y == move.end_col) {
					bishop.x = move.start_row;
					bishop.y = move.start_col;
				}
			}
		}


		if (move.piece_captured == black_rook) {
			for (auto& rook : black_rooks) {
				if (rook.x == -1 && rook.y == -1) {
					rook.x = move.end_row;
					rook.y = move.end_col;
				}
			}
		}
		else if (move.piece_captured == white_rook) {
			for (auto& rook : white_rooks) {
				if (rook.x == -1 && rook.y == -1) {
					rook.x = move.end_row;
					rook.y = move.end_col;
				}
			}
		}
		else if (move.piece_captured == black_bishop) {
			for (auto& bishop : black_bishops) {
				if (bishop.x == -1 && bishop.y == -1) {
					bishop.x = move.end_row;
					bishop.y = move.end_col;
				}
			}
		}
		else if (move.piece_captured == white_bishop) {
			for (auto& bishop : white_bishops) {
				if (bishop.x == -1 && bishop.y == -1) {
					bishop.x = move.end_row;
					bishop.y = move.end_col;
				}
			}
		}
		else if (move.piece_captured == black_queen) {
			for (auto& bishop : black_queens) {
				if (bishop.x == -1 && bishop.y == -1) {
					bishop.x = move.end_row;
					bishop.y = move.end_col;
				}
			}
		}
		else if (move.piece_captured == white_queen) {
			for (auto& bishop : white_queens) {
				if (bishop.x == -1 && bishop.y == -1) {
					bishop.x = move.end_row;
					bishop.y = move.end_col;
				}
			}
		}
	}

	void make_move(chess_move move)
	{
		int start_row = move.start_row;
		int start_col = move.start_col;
		int end_row = move.end_row;
		int end_col = move.end_col;
		white_to_move = !white_to_move;
		auto piece_moved = board[start_row][start_col];
		auto piece_captured = board[end_row][end_col];

		board[start_row][start_col] = {color::none, piece::none};
		board[end_row][end_col] = piece_moved;

		update_piece_positions_on_move(move, piece_captured, piece_moved, start_row, start_col, end_row, end_col);

		if (move.is_enpassant) {
			board[start_row][end_col] = {color::none, piece::none};
		}
		else if (move.is_castle) {
			if (end_col - start_col == 2) {
				if (board[end_row][end_col + 1] == black_rook) {
					for (auto& rook : black_rooks) {
						if (rook.x == end_row && rook.y == end_col + 1) {
							rook.y = end_col - 1;
						}
					}
				}
				else if (board[end_row][end_col + 1] == white_rook) {
					for (auto& rook : white_rooks) {
						if (rook.x == end_row && rook.y == end_col + 1) {
							rook.y = end_col - 1;
						}
					}
				}
				board[end_row][end_col - 1] = board[end_row][end_col + 1];
				board[end_row][end_col + 1] = { color::none, piece::none };
			}
			else if (end_col - start_col == -2) {
				if (board[end_row][end_col + 1] == black_rook) {
					for (auto& rook : black_rooks) {
						if (rook.x == end_row && rook.y == end_col -2) {
							rook.y = end_col + 1;
						}
					}
				}
				else if (board[end_row][end_col + 1] == white_rook) {
					for (auto& rook : white_rooks) {
						if (rook.x == end_row && rook.y == end_col -2) {
							rook.y = end_col + 1;
						}
					}
				}
				board[end_row][end_col + 1] = board[end_row][end_col - 2];
				board[end_row][end_col - 2] = { color::none, piece::none };
			}
		}

		if (move.is_pawn_promotion) {
			board[end_row][end_col] = { move.piece_moved.first , piece::queen };
			if (!white_to_move) {
				white_queens.push_back({ end_row,end_col });
			}
			else {
				black_queens.push_back({ end_row,end_col });
			}
		}

		if (move.piece_moved.second == piece::pawn && abs(end_row - start_row) == 2) {
			enpassant_possible = bq::v2i((start_row + end_row) / 2, start_col);
		}
		else {
			enpassant_possible = bq::v2i(-1, -1);
		}

		

		move_log.push_back(move);

		update_castling_rights(move);

		castle_rights_log.push_back(current_castling_rights);
	}
	void undo_move()
	{
		if (move_log.size() != 0) {
			chess_move move = move_log.back();
			move_log.pop_back();
			board[move.start_row][move.start_col] = move.piece_moved;
			board[move.end_row][move.end_col] = move.piece_captured;
			white_to_move = !white_to_move;
			if (move.piece_moved == white_king) {
				white_king_pos = bq::v2i(move.start_row, move.start_col);
			}
			else if (move.piece_moved == black_king) {
				black_king_pos = bq::v2i(move.start_row, move.start_col);
			}
			if (move.is_enpassant) {
				board[move.end_row][move.end_col] = empty_piece;
				board[move.start_row][move.end_col] = move.piece_captured;
				enpassant_possible = bq::v2i(move.end_row, move.end_col);
			}
			if (move.piece_moved.second == piece::pawn && abs(move.start_row - move.end_row) == 2) {
				enpassant_possible = bq::v2i(-1, -1);
			}
			if (move.is_pawn_promotion) {
				if (!white_to_move) {
					for (int i = white_queens.size() - 1; i >= 0; --i) {
						if (white_queens[i].x == move.end_row && white_queens[i].y == move.end_col) {
							white_queens.erase(white_queens.begin() + i);
						}
					}
				}
				else {
					for (int i = black_queens.size() - 1; i >= 0; --i) {
						if (black_queens[i].x == move.end_row && black_queens[i].y == move.end_col) {
							black_queens.erase(black_queens.begin() + i);
						}
					}
				}
			}
			

			castle_rights_log.pop_back();
			current_castling_rights = castle_rights_log.back();

			update_piece_positions_on_undo(move);

			if (move.is_castle) {
				if (move.end_col - move.start_col == 2) {

					//need to update un-castled rook into remembered piece locations!
					if (board[move.end_row][move.end_col - 1] == black_rook) {
						for (auto& rook : black_rooks) {
							if (rook.x == move.end_row && rook.y == move.end_col - 1) {
								rook.y = move.end_col + 1;
							}
						}
					}
					else if (board[move.end_row][move.end_col - 1] == white_rook) {
						for (auto& rook : white_rooks) {
							if (rook.x == move.end_row && rook.y == move.end_col - 1) {
								rook.y = move.end_col + 1;
							}
						}
					}
					board[move.end_row][move.end_col + 1] = board[move.end_row][move.end_col - 1];
					board[move.end_row][move.end_col - 1] = empty_piece;
				}
				else {
					//need to update un-castled rook into remembered piece locations!
					if (board[move.end_row][move.end_col + 1] == black_rook) {
						for (auto& rook : black_rooks) {
							if (rook.x == move.end_row && rook.y == move.end_col -2) {
								rook.y = move.end_col -2;
							}
						}
					}
					else if (board[move.end_row][move.end_col + 1] == white_rook) {
						for (auto& rook : white_rooks) {
							if (rook.x == move.end_row && rook.y == move.end_col -2 ) {
								rook.y = move.end_col -2;
							}
						}
					}
					board[move.end_row][move.end_col - 2] = board[move.end_row][move.end_col + 1];
					board[move.end_row][move.end_col + 1] = empty_piece;
				}
			}
			checkmate = false;
			stalemate = false;
		}
	}

	bool is_square_under_attack(int row, int col)
	{
		this->white_to_move = !this->white_to_move;
		auto oponent_moves = this->get_possible_moves();
		this->white_to_move = !this->white_to_move;
		for (auto move : *oponent_moves) {
			if (move.end_row == row && move.end_col == col) {
				return true;
			}
		}
		return false;
	}

	

	std::unique_ptr<std::vector<chess_move>> get_valid_moves()
	{
		auto temp_castle_rights = castle_rights(current_castling_rights.wks, current_castling_rights.bks,
			current_castling_rights.wqs, current_castling_rights.bqs);
		std::unique_ptr<std::vector<chess_move>> moves = std::make_unique<std::vector<chess_move>>();
		check_pin_information = calc_checks_and_pins();

		int king_row;
		int king_col;
		if (white_to_move) {
			king_row = white_king_pos.x;
			king_col = white_king_pos.y;
		}
		else {
			king_row = black_king_pos.x;
			king_col = black_king_pos.y;
		}

		if (check_pin_information.in_check) {
			if (check_pin_information.checks.size() == 1) {
				moves = get_possible_moves();
				bq::v4i check = check_pin_information.checks[0];
				int check_row = check.x;
				int check_col = check.y;
				auto piece_checking = board[check_row][check_col];
				std::vector<bq::v2i> valid_squares;
				chess_move* enpassant_breaks_check = nullptr;

				if (enpassant_possible.x != -1 && enpassant_possible.y != -1) {
					for (auto& move : *moves) {
						if (move.is_enpassant) {
							make_move(move);
							get_valid_moves();

							if (white_to_move) {
								if (!is_square_under_attack(black_king_pos.x, black_king_pos.y)) {
									enpassant_breaks_check = &move;
								}
							}
							else {
								if (!is_square_under_attack(white_king_pos.x, white_king_pos.y)) {
									enpassant_breaks_check = &move;
								}
							}
							undo_move();
						}
					}
				}

				if (piece_checking.second == piece::knight) {
					valid_squares = { bq::v2i(check_row, check_col) };
				}
				else {
					for (int i = 1; i < 8; i++) {
						bq::v2i valid_square(king_row + check.z * i, king_col + check.t * i);
						valid_squares.push_back(valid_square);
						if (valid_square.x == check_row && valid_square.y == check_col) {
							break;
						}
					}
				}

				for (int i = moves->size() - 1; i >= 0; i--) {
					if ((*moves)[i].piece_moved.second != piece::king) {
						if (std::find(valid_squares.begin(), valid_squares.end(), bq::v2i((*moves)[i].end_row, (*moves)[i].end_col)) == valid_squares.end()) {
							moves->erase(moves->begin() + i);
						}
						if (enpassant_breaks_check != nullptr) {
							moves->push_back(*enpassant_breaks_check);
						}
					}
				}
			}
			else {
				add_king_moves(king_row, king_col, (*moves));
			}
		}
		else {
			moves = get_possible_moves();
			if (white_to_move) {
				add_castle_moves(white_king_pos.x, white_king_pos.y, (*moves));
			}
			else {
				add_castle_moves(black_king_pos.x, black_king_pos.y, (*moves));
			}
		}
		if ((*moves).empty()) {
			if (check_pin_information.in_check){
				checkmate = true;
			}
			else {
				stalemate = true;
			}
		}
		else {
			checkmate = false;
			stalemate = false;
		}

		current_castling_rights = temp_castle_rights;
		return moves;

	}
	std::unique_ptr<std::vector<chess_move>> get_possible_moves() {
		std::unique_ptr<std::vector<chess_move>> moves = std::make_unique<std::vector<chess_move>>();
		for (int row = 0; row < board.size(); row++) {
			for (int col = 0; col < board[row].size(); col++) {
				color turn = board[row][col].first;
				if ((turn == color::white && white_to_move) || (turn == color::black && !white_to_move)) {
					piece piece = board[row][col].second;
					if (piece == piece::pawn) add_pawn_moves(row, col, (*moves));
					else if (piece == piece::king) add_king_moves(row, col, (*moves));
					else if (piece == piece::knight) add_knight_moves(row, col, (*moves));
				}
			}
		}
		
		if (white_to_move)
		{
			for (auto pos : white_rooks) {
				if (pos.x == -1 || pos.y == -1) continue;
				add_rook_moves(pos.x, pos.y, (*moves));
			}
			for (auto pos : white_bishops) {
				if (pos.x == -1 || pos.y == -1) continue;
				add_bishop_moves(pos.x, pos.y, (*moves));
			}
			for (auto pos : white_queens) {
				if (pos.x == -1 || pos.y == -1) continue;
				add_queen_moves(pos.x, pos.y, (*moves));
			}
		}
		else {
			for (auto pos : black_rooks) {
				if (pos.x == -1 || pos.y == -1) continue;
				add_rook_moves(pos.x, pos.y, (*moves));
			}
			for (auto pos : black_bishops) {
				if (pos.x == -1 || pos.y == -1) continue;
				add_bishop_moves(pos.x, pos.y, (*moves));
			}
			for (auto pos : black_queens) {
				if (pos.x == -1 || pos.y == -1) continue;
				add_queen_moves(pos.x, pos.y, (*moves));
			}
		}
		
		


		return moves;
	}
	
	void add_knight_moves(int row, int col, std::vector<chess_move>& moves) {
		bool piece_pinned = false;
		for (int i = check_pin_information.pins.size() - 1; i >= 0; i--) {
			if (check_pin_information.pins[i].x == row && check_pin_information.pins[i].y == col) {
				piece_pinned = true;
				check_pin_information.pins.erase(check_pin_information.pins.begin() + i);
				break;
			}
		}

		std::vector<bq::v2i> knight_moves = { bq::v2i(-2, -1), bq::v2i(-2, 1), bq::v2i(-1, 2), bq::v2i(1, 2), bq::v2i(2, -1), bq::v2i(2, 1), bq::v2i(-1, -2), bq::v2i(1, -2) };
		color ally_color = (white_to_move ? color::white : color::black);
		for (auto move : knight_moves) {
			int end_row = row + move.x;
			int end_col = col + move.y;
			if (end_row >= 0 && end_row <= 7 && end_col >= 0 && end_col <= 7) {
				if (!piece_pinned) {
					auto end_piece = board[end_row][end_col];
					if (end_piece.first != ally_color) {
						moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(end_row, end_col), board));
					}
				}
			}
		}
	}
	void add_pawn_moves(int row, int col, std::vector<chess_move>& moves)
	{
		bool piece_pinned = false;
		bq::v2i pin_direction(0, 0);

		for (int i = check_pin_information.pins.size() - 1; i >= 0; i--) {
			if (check_pin_information.pins[i].x == row && check_pin_information.pins[i].y == col) {
				piece_pinned = true;
				pin_direction = bq::v2i(check_pin_information.pins[i].z, check_pin_information.pins[i].t);
				check_pin_information.pins.erase(check_pin_information.pins.begin() + i);
				break;
			}
		}

		if (white_to_move) {
			if (board[row - 1][col] == empty_piece) {
				if (!piece_pinned || pin_direction == bq::v2i(-1, 0)) {
					moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row - 1, col), board));
					if (row == 6 && board[row - 2][col] == empty_piece) {
						moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row - 2, col), board));
					}
				}
			}
			if (col - 1 >= 0) {
				if (board[row - 1][col - 1].first == color::black) {
					if (!piece_pinned || pin_direction == bq::v2i(-1, -1)) {
						moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row - 1, col - 1), board));
					}
				}
				else if (bq::v2i(row - 1, col - 1) == enpassant_possible) {
					if (!piece_pinned || pin_direction == bq::v2i(-1, -1)) {
						bool attacking_piece=false, blocking_piece = false;

						if (row == white_king_pos.x) {
							std::vector<int> inside_range;
							std::vector<int> outside_range;
							if (white_king_pos.y < col) {
								for (int i = white_king_pos.y+1; i < col - 1; i++)
									inside_range.push_back(i);
								
								for (int i = col + 1; i < 8; i++)
									outside_range.push_back(i);

							}
							else {
								for (int i = white_king_pos.y - 1; i > col; i--)
									inside_range.push_back(i);
								for (int i = col - 2; i > 0; i--)
									outside_range.push_back(i);
							}
							for (auto i : inside_range) {
								if (board[row][i] != empty_piece) {
									blocking_piece = true;
								}
							}
							for (auto i : outside_range) {
								piece_t t = board[row][i];
								if (t.first == color::black && (t.second == piece::rook || t.second == piece::queen)) {
									attacking_piece = true;
								}
								else if (t != empty_piece) {
									blocking_piece = true;
								}
							}
						}
						if(!attacking_piece || blocking_piece)
							moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row - 1, col - 1), board, true,false));
					}
				}
			}
			if (col + 1 <= 7) {
				if (board[row - 1][col + 1].first == color::black) {
					if (!piece_pinned || pin_direction == bq::v2i(-1, 1)) {
						moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row - 1, col + 1), board));
					}
				}
				else if (bq::v2i(row - 1, col + 1) == enpassant_possible) {
					if (!piece_pinned || pin_direction == bq::v2i(-1, 1)) {
						bool attacking_piece=false, blocking_piece = false;

						if (row == white_king_pos.x) {
							std::vector<int> inside_range;
							std::vector<int> outside_range;
							if (white_king_pos.y < col) {

								for (int i = white_king_pos.y + 1; i < col ; i++)
									inside_range.push_back(i);

								for (int i = col + 2; i < 8; i++)
									outside_range.push_back(i);

							}
							else {
								for (int i = white_king_pos.y - 1; i > col+1; i--)
									inside_range.push_back(i);
								for (int i = col - 1; i > -1; i--)
									outside_range.push_back(i);
							}
							for (auto i : inside_range) {
								if (board[row][i] != empty_piece) {
									blocking_piece = true;
								}
							}
							for (auto i : outside_range) {
								piece_t t = board[row][i];
								if (t.first == color::black && (t.second == piece::rook || t.second == piece::queen)) {
									attacking_piece = true;
								}
								else if (t != empty_piece) {
									blocking_piece = true;
								}
							}
						}
						if (!attacking_piece || blocking_piece)
							moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row - 1, col + 1), board, true,false));
					}
				}
			}
		}
		else {
			if (board[row + 1][col] == empty_piece) {
				if (!piece_pinned || pin_direction == bq::v2i(1, 0)) {
					moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row + 1, col), board));
					if (row == 1 && board[row + 2][col] == empty_piece) {
						moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row + 2, col), board));
					}
				}
			}
			if (col - 1 >= 0) {
				if (board[row + 1][col - 1].first == color::white) {
					if (!piece_pinned || pin_direction == bq::v2i(1, -1)) {
						moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row + 1, col - 1), board));
					}
				}
				else if (bq::v2i(row + 1, col - 1) == enpassant_possible) {
					if (!piece_pinned || pin_direction == bq::v2i(1, -1)) {
						bool attacking_piece=false, blocking_piece = false;

						if (row == black_king_pos.x) {
							std::vector<int> inside_range;
							std::vector<int> outside_range;
							if (black_king_pos.y < col) {

								for (int i = black_king_pos.y + 1; i < col - 1; i++)
									inside_range.push_back(i);

								for (int i = col + 1; i < 8; i++)
									outside_range.push_back(i);

							}
							else {
								for (int i = black_king_pos.y - 1; i > col; i--)
									inside_range.push_back(i);
								for (int i = col - 2; i > 0; i--)
									outside_range.push_back(i);
							}
							for (auto i : inside_range) {
								if (board[row][i] != empty_piece) {
									blocking_piece = true;
								}
							}
							for (auto i : outside_range) {
								piece_t t = board[row][i];
								if (t.first == color::white && (t.second == piece::rook || t.second == piece::queen)) {
									attacking_piece = true;
								}
								else if (t != empty_piece) {
									blocking_piece = true;
								}
							}
						}
						if (!attacking_piece || blocking_piece)
							moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row + 1, col - 1), board, true));
					}
				}
			}

			if (col + 1 <= 7) {
				if (board[row + 1][col + 1].first == color::white) {
					if (!piece_pinned || pin_direction == bq::v2i(1, 1)) {
						moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row + 1, col + 1), board));
					}
				}
				else if (bq::v2i(row + 1, col + 1) == enpassant_possible) {
					if (!piece_pinned || pin_direction == bq::v2i(1, 1)) {
						bool attacking_piece=false, blocking_piece = false;

						if (row == black_king_pos.x) {
							std::vector<int> inside_range;
							std::vector<int> outside_range;
							if (black_king_pos.y < col) {

								for (int i = white_king_pos.y + 1; i < col; i++)
									inside_range.push_back(i);

								for (int i = col + 2; i < 8; i++)
									outside_range.push_back(i);

							}
							else {
								for (int i = white_king_pos.y - 1; i > col + 1; i--)
									inside_range.push_back(i);
								for (int i = col - 1; i > -1; i--)
									outside_range.push_back(i);
							}
							for (auto i : inside_range) {
								if (board[row][i] != empty_piece) {
									blocking_piece = true;
								}
							}
							for (auto i : outside_range) {
								piece_t t = board[row][i];
								if (t.first == color::white && (t.second == piece::rook || t.second == piece::queen)) {
									attacking_piece = true;
								}
								else if (t != empty_piece) {
									blocking_piece = true;
								}
							}
						}
						if (!attacking_piece || blocking_piece)
							moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row + 1, col + 1), board, true));
					}
				}
			}
			
		}
	}
	void add_rook_moves(int row, int col, std::vector<chess_move>& moves)
	{
		bool piece_pinned = false;
		bq::v2i pin_direction = {};
		for (int i = check_pin_information.pins.size() - 1; i >= 0; --i) {
			if (check_pin_information.pins[i].x == row && check_pin_information.pins[i].y == col)
			{
				piece_pinned = true;
				pin_direction = bq::v2i(check_pin_information.pins[i].z, check_pin_information.pins[i].t);
				if (board[row][col].second != piece::queen)
					check_pin_information.pins.erase(check_pin_information.pins.begin() + i);
				break;
			}
		}
		std::vector<bq::v2i> directions = { bq::v2i(-1, 0), bq::v2i(0, -1), bq::v2i(1, 0), bq::v2i(0,1) };
		color enemy_color = color::white;
		if (white_to_move)
			enemy_color = color::black;
		for (auto direction : directions)
		{
			for (int i = 1; i < 8; ++i)
			{
				int end_row = row + direction.x * i;
				int end_col = col + direction.y * i;
				if ( (0 <= end_row && end_row <= 7) && (0 <= end_col && end_col <= 7))
				{
					if (!piece_pinned || pin_direction == direction || pin_direction == bq::v2i(-direction.x, -direction.y))
					{
						auto end_piece = board[end_row][end_col];
						if (end_piece == empty_piece)
						{
							moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(end_row, end_col), board));
						}
						else if (end_piece.first == enemy_color)
						{
							moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(end_row, end_col), board));
							break;
						}
						else
							break;
					}
				}
				else
					break;
			}
		}
	}
	void add_bishop_moves(int row, int col, std::vector<chess_move>& moves)
	{
		bool piece_pinned = false;
		bq::v2i pin_direction = {};
		for (int i = check_pin_information.pins.size()-1; i  >= 0; --i) {
			if (check_pin_information.pins[i].x == row && check_pin_information.pins[i].y == col)
			{
				piece_pinned = true;
				pin_direction = bq::v2i(check_pin_information.pins[i].z, check_pin_information.pins[i].t);
				check_pin_information.pins.erase(check_pin_information.pins.begin() + i);
				break;
			}
		}
		std::vector<bq::v2i> directions = { bq::v2i(-1, -1), bq::v2i(-1, 1), bq::v2i(1, 1), bq::v2i(1, -1) };
		color enemy_color = color::white;
		if (white_to_move)
			enemy_color = color::black;
		for (auto direction : directions)
		{
			for (int i = 1; i < 8; ++i)
			{
				int end_row = row + direction.x * i;
				int end_col = col + direction.y * i;
				if ((0 <= end_row && end_row <= 7) && (0 <= end_col && end_col <= 7))
				{
					if ( !piece_pinned || pin_direction == direction || pin_direction == bq::v2i(-direction.x, -direction.y))
					{
						auto end_piece = board[end_row][end_col];
						if (end_piece == empty_piece)
						{
							moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(end_row, end_col), board));
						}
						else if (end_piece.first == enemy_color)
						{
							moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(end_row, end_col), board));
							break;
						}
						else {
							break;
						}
							
					}
				}
				else {
					break;
				}
			}
		}
		
	}
	void add_queen_moves(int row, int col, std::vector<chess_move>& moves)
	{
		add_bishop_moves(row, col, moves);
		add_rook_moves(row, col, moves);
	}
	void add_king_moves(int row, int col, std::vector<chess_move>& moves)
	{
		std::vector<bq::v2i> king_moves = { bq::v2i(-1, -1), bq::v2i(-1, 0), bq::v2i(-1, 1), bq::v2i(0, -1), bq::v2i(0, 1), bq::v2i(1, -1), bq::v2i(1, 0), bq::v2i(1, 1) };
		color ally_color = color::black;
		if (white_to_move)
			ally_color = color::white;

		for (int i = 0; i < 8; ++i) {
			int end_row = row + king_moves[i].x;
			int end_col = col + king_moves[i].y;
			if ((0 <= end_row && end_row <= 7) && (0 <= end_col && end_col <= 7))
			{
				auto end_piece = board[end_row][end_col];
				if (end_piece.first != ally_color)
				{
					
					if (ally_color == color::white)
					{
						white_king_pos = bq::v2i(end_row, end_col);
					}
					else
					{
						black_king_pos = bq::v2i(end_row, end_col);
					}
					check_pin_info info = calc_checks_and_pins();
					if (!info.in_check)
					{
						moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(end_row, end_col), board));
					}
					if (ally_color == color::white)
					{
						white_king_pos = bq::v2i(row, col);
					}
					else
					{
						black_king_pos = bq::v2i(row, col);
					}
				}
			}
		}
	}

	void add_castle_moves(int row, int col, std::vector<chess_move>& moves)
	{
		if (is_square_under_attack(row, col)) {
			return;
		}
            
		if ((white_to_move && current_castling_rights.wks) || (!white_to_move && current_castling_rights.bks))
		{
			add_kingside_castle_moves(row, col, moves);
		}
            
		if ((white_to_move && current_castling_rights.wqs) || (!white_to_move && current_castling_rights.bqs))
		{
			add_queenside_castle_moves(row, col, moves);
		}
	}
	void add_kingside_castle_moves(int row, int col, std::vector<chess_move>& moves)
	{
		if (board[row][col+1] == empty_piece && board[row][col+2] == empty_piece)
		{
			if (!is_square_under_attack(row, col + 1) && !is_square_under_attack(row, col + 2))
			{
				moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row, col + 2), board, false, true));
			}
		}
	}
	void add_queenside_castle_moves(int row, int col, std::vector<chess_move>& moves)
	{
		if (board[row][col - 1] == empty_piece && board[row][col - 2] == empty_piece && board[row][col - 3] == empty_piece)
		{
			if (!is_square_under_attack(row, col - 1) && !is_square_under_attack(row, col - 2))
			{
				moves.push_back(chess_move(bq::v2i(row, col), bq::v2i(row, col - 2), board, false, true));
			}
		}
	}
    std::string get_fen() {
		std::string fen = "";
		int empties = 0;
        for (auto row : board) {
            for (auto square : row) {
				if (square == empty_piece)
					empties += 1;
				else if (square.first == color::black) {
					if (empties > 0) {
						fen += std::to_string(empties);
						empties = 0;
					}
					auto lower = piece_string_map[square.second];
					std::transform(lower.begin(), lower.end(), lower.begin(),
						[](unsigned char c) { return std::tolower(c); });
					fen += lower;
				}
				else {
					if (empties > 0) {
						fen += std::to_string(empties);
						empties = 0;
						fen += piece_string_map[square.second];
					}
				}
            }
			if (empties > 0) {
				fen += std::to_string(empties);
				empties = 0;
				fen += '/';
			}
        }
		fen.pop_back();
		if (white_to_move)
			fen += " w ";
		else
			fen += " b ";

		bool any_castle_available = false;
		if (current_castling_rights.wks)
		{
			any_castle_available = true;
			fen += "K";
		}	
		if (current_castling_rights.wqs) {
			any_castle_available = true;
			fen += "Q";
		}
		if (current_castling_rights.bks) {
			any_castle_available = true;
			fen += "k";
		}
		if (current_castling_rights.bqs) {
			any_castle_available = true;
			fen += "q";
		};
            
		if (!any_castle_available)
			fen += "-";
		fen += " ";
		if (!(enpassant_possible == bq::v2i(-1, -1)))
			fen += "-";
		else {
			auto tempMove = chess_move(enpassant_possible, bq::v2i(0,0), board);
			fen += tempMove.get_chess_notation_old()[0];
			fen += tempMove.get_chess_notation_old()[1];
		}
		fen += " 0 0";
		return fen;
    }
    std::string get_pgn() {
		std::string pgn = "";
		for (unsigned i = 0; i < move_log.size(); ++i) {
			pgn += std::to_string(i + 1);
			pgn += ". ";
			pgn += move_log[i].get_chess_notation_old();
			pgn += " ";
		}
		return pgn;
	}
	chess_state() {}
	~chess_state() {}
};