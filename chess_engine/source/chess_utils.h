#pragma once

#include "includes.h"
#include <bq.h>

#define ANALYTICS true


static std::map<PieceType, int> piece_scores = { {PieceType::KING,5000},{PieceType::QUEEN , 900},{PieceType::ROOK , 500},{PieceType::BISHOP, 300},{PieceType::KNIGHT , 300},{PieceType::PAWN , 100} };



static constexpr int piece_values[NPIECE_TYPES] = {
	100,    // PAWN
	300,    // KNIGHT
	305,    // BISHOP
	500,    // ROOK
	900,    // QUEEN
	2000000 // KING
};


static File col_to_file(int row, bool reversed) {
	if (reversed) {
		File f = AFILE;
		switch (row) {
		case 7: f = File::AFILE; break;
		case 6: f = File::BFILE; break;
		case 5: f = File::CFILE; break;
		case 4: f = File::DFILE; break;
		case 3: f = File::EFILE; break;
		case 2: f = File::FFILE; break;
		case 1: f = File::GFILE; break;
		case 0: f = File::HFILE; break;
		}
		return f;
	}
	File f = AFILE;
	switch (row) {
		case 0: f = File::AFILE; break;
		case 1: f = File::BFILE; break;
		case 2: f = File::CFILE; break;
		case 3: f = File::DFILE; break;
		case 4: f = File::EFILE; break;
		case 5: f = File::FFILE; break;
		case 6: f = File::GFILE; break;
		case 7: f = File::HFILE; break;
	}
	return f;
}

static Rank row_to_rank(int col, bool reversed) {
	if (reversed) {
		Rank r = RANK8;
		switch (col) {
		case 7: r = Rank::RANK8; break;
		case 6: r = Rank::RANK7; break;
		case 5: r = Rank::RANK6; break;
		case 4: r = Rank::RANK5; break;
		case 3: r = Rank::RANK4; break;
		case 2: r = Rank::RANK3; break;
		case 1: r = Rank::RANK2; break;
		case 0: r = Rank::RANK1; break;
		}
		return r;
	}
	Rank r = RANK8;
	switch (col) {
	case 0: r = Rank::RANK8; break;
	case 1: r = Rank::RANK7; break;
	case 2: r = Rank::RANK6; break;
	case 3: r = Rank::RANK5; break;
	case 4: r = Rank::RANK4; break;
	case 5: r = Rank::RANK3; break;
	case 6: r = Rank::RANK2; break;
	case 7: r = Rank::RANK1; break;
	}
	return r;
}

enum GameProgress {
	MIDGAME,
	ENDGAME
};
static GameProgress get_progress(int mv1, int mv2) {
	return (mv1 <= 1300 && mv2 <= 1300) ? ENDGAME : MIDGAME;
}


static std::string get_notation(Position& p, Move& move) {
	if (move.is_promotion()) {
		return  move.str().substr(2,3) + "Q";
	}
	
	if (move.is_castling())
		if (move.to() == h1 || move.to() == h8)
			return "0-0";
		else
			return "0-0-0";
	if (move.flags() == MoveFlags::EN_PASSANT) {
		return move.str().substr(0,1) + "x" + move.str().substr(2, 3) + " e.p.";
	}
	if (move.is_capture())
		if (p.at(move.from()) == Piece::BLACK_PAWN || p.at(move.from()) == Piece::WHITE_PAWN) {
			return  move.str().substr(0, 1) + "x" + move.str().substr(2, 3);
		}
		else {
			auto piece = p.at(move.from());
			std::string piece_letter = "";
			switch (piece) {
				case WHITE_BISHOP: piece_letter = "B"; break;
				case BLACK_BISHOP: piece_letter = "B"; break;
				case WHITE_ROOK: piece_letter = "R"; break;
				case BLACK_ROOK: piece_letter = "R"; break;
				case WHITE_KNIGHT: piece_letter = "N"; break;
				case BLACK_KNIGHT: piece_letter = "N"; break;
				case WHITE_QUEEN: piece_letter = "Q"; break;
				case BLACK_QUEEN: piece_letter = "Q"; break;
				case WHITE_KING: piece_letter = "K"; break;
				case BLACK_KING: piece_letter = "K"; break;
			}
			return piece_letter + "x" + move.str().substr(2, 3);
		}
	else {
		if (p.at(move.from()) == Piece::BLACK_PAWN || p.at(move.from()) == Piece::WHITE_PAWN) {
			return move.str().substr(2,3);
		}
		
		else {
			auto piece = p.at(move.from());
			std::string piece_letter = "";
			switch (piece) {
				case WHITE_BISHOP: piece_letter = "B"; break;
				case BLACK_BISHOP: piece_letter = "B"; break;
				case WHITE_ROOK: piece_letter = "R"; break;
				case BLACK_ROOK: piece_letter = "R"; break;
				case WHITE_KNIGHT: piece_letter = "N"; break;
				case BLACK_KNIGHT: piece_letter = "N"; break;
				case WHITE_QUEEN: piece_letter = "Q"; break;
				case BLACK_QUEEN: piece_letter = "Q"; break;
				case WHITE_KING: piece_letter = "K"; break;
				case BLACK_KING: piece_letter = "K"; break;
			}
			return piece_letter + move.str().substr(2, 3);
		}
		
	}
}

static bool detect_checkmate(Position& p) {

	if (p.turn() == WHITE) {
		MoveList<WHITE> moves(p);
		if (moves.size() == 0) {
			if (p.in_check<WHITE>())
				bq::logger::info("checkmate, black wins!");
			else
				bq::logger::info("stalemate!");
			return true;
		}
		return false;
	}
	else {
		MoveList<BLACK> moves(p);
		if (moves.size() == 0) {
			if (p.in_check<BLACK>())
				bq::logger::info("checkmate, white wins!");
			else
				bq::logger::info("stalemate!");
			return true;
		}
		return false;
	}
}