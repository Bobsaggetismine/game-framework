#pragma once
enum class color {
	white,
	black,
	none
};
enum class piece {
	pawn,
	bishop,
	rook,
	knight,
	queen,
	king,
	none
};
using piece_t = std::pair<color, piece>;