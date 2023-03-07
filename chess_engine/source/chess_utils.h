#pragma once

#include "surge/types.h"
#include "surge/tables.h"
#include "surge/position.h"
#include <bq.h>

#define ANALYTICS true
#define CHESS_DEBUG false


std::map<PieceType, int> piece_scores = { {PieceType::KING,5000},{PieceType::QUEEN , 900},{PieceType::ROOK , 500},{PieceType::BISHOP, 300},{PieceType::KNIGHT , 300},{PieceType::PAWN , 100} };

File row_to_file(int row) {
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
Rank col_to_rank(int col) {
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
GameProgress get_progress(int mv1, int mv2) {
	return (mv1 <= 1300 && mv2 <= 1300) ? ENDGAME : MIDGAME;
}