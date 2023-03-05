#pragma once
#include <bq.h>
#include "enums.h"

struct chess_move {

	std::map<std::string, int> RANKS_TO_ROWS = { {"1",7},{"2",6},{"3",5},{"4",4},{"5",3},{"6",2},{"7",1},{"8",0} };
	std::map<int, std::string> ROWS_TO_RANKS;


	


	std::map<std::string, int> FILES_TO_COLS = { {"a",0},{"b",1},{"c",2},{"d",3},{"e",4},{"f",5},{"g",6},{"h",7} };
	std::map<int, std::string> COLS_TO_FILES;

	int start_row, start_col, end_row, end_col;

	piece_t piece_moved, piece_captured;

	bool is_pawn_promotion = false;
	bool is_enpassant,is_castle;

	int move_id = 0;

	chess_move(bq::v2i start, bq::v2i end, std::vector<std::vector<std::pair<color, piece>>>& board, bool is_enpassant_move = false, bool is_castle_move = false)
		:start_row(start.x), start_col(start.y),end_row(end.x), end_col(end.y), piece_moved(board[start.x][start.y]), piece_captured(board[end.x][end.y]),
		is_enpassant(is_enpassant_move), is_castle(is_castle_move)
	{
		for (const auto& pair : RANKS_TO_ROWS) {
			ROWS_TO_RANKS[pair.second] = pair.first;
		}
		for (const auto& pair : FILES_TO_COLS) {
			COLS_TO_FILES[pair.second] = pair.first;
		}

		is_pawn_promotion = ( (piece_moved == std::make_pair<color, piece>(color::white, piece::pawn) && end_row == 0) || (piece_moved == std::make_pair<color, piece>(color::black, piece::pawn) && end_row == 7) );
		if (is_enpassant)
		{
			if (piece_moved == std::make_pair<color, piece>(color::black, piece::pawn))
				piece_captured = std::make_pair<color, piece>(color::white, piece::pawn);
			else
				piece_captured = std::make_pair<color, piece>(color::black, piece::pawn);
		}
		move_id = start_row * 1000 + start_col * 100 + end_row * 10 + end_col;
	}
	std::string get_rank_file(int r, int c)
	{
		return (COLS_TO_FILES[c] + ROWS_TO_RANKS[r]);

	}
	std::string get_chess_notation_old()
	{
		return get_rank_file(start_row, start_col) + get_rank_file(end_row, end_col);
	}	
	bool operator==(chess_move& other) {
		return move_id == other.move_id;
	}
};