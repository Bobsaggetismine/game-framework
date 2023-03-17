#pragma once

#pragma once
#include "surge/surge.h"


constexpr int checkmate_score = 100000;
constexpr int stalemate_score = 0;



template <Color Us>
int score_board(Position& pos) {


    // Material value
    int mv = 0;
    int our_mv = 0;
    int their_mv = 0;
    for (PieceType i = PAWN; i < NPIECE_TYPES - 1; ++i) {
        our_mv += pop_count(pos.bitboard_of(Us, i)) * piece_scores[i];
        their_mv += pop_count(pos.bitboard_of(~Us, i)) * piece_scores[i];
    }
    mv += our_mv;
    mv -= their_mv;
    GameProgress progress = get_progress(our_mv, their_mv);

    // Color advantage
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
    for (Color color = WHITE; color < NCOLORS; ++color) {
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
    }

    // Rook placement
    int rp = 0;
    rp += pop_count(pos.bitboard_of(Us, ROOK) & MASK_RANK[Us == WHITE ? RANK7 : RANK2]) * 30;
    rp -= pop_count(pos.bitboard_of(~Us, ROOK) & MASK_RANK[~Us == WHITE ? RANK7 : RANK2]) * 30;

    // King placement
    /*
    function distance(x1, y1, x2, y2) {
        return Math.hypot(x2 - x1, y2 - y1);
    }
    let table = [];
    for (let y = 7; y > -1; y--) {
        for (let x = 0; x < 8; x++) {
            table.push(Math.round(distance(x, y, 3.5, 3.5) * 20));
        }
    }
    table[0] = Math.round(distance(1, 6, 3.5, 3.5) * 20);
    table[7] = Math.round(distance(6, 6, 3.5, 3.5) * 20);
    table[56] = Math.round(distance(1, 1, 3.5, 3.5) * 20);
    table[63] = Math.round(distance(6, 1, 3.5, 3.5) * 20);
    */
    static constexpr int king_pcsq_table[64] = { 71, 86, 76, 71, 71, 76, 86, 71, 86, 71, 58, 51, 51, 58, 71, 86, 76, 58, 42, 32, 32, 42, 58, 76, 71, 51, 32, 14, 14, 32, 51, 71, 71, 51, 32, 14, 14, 32, 51, 71, 76, 58, 42, 32, 32, 42, 58, 76, 86, 71, 58, 51, 51, 58, 71, 86, 71, 86, 76, 71, 71, 76, 86, 71 };
    int kp = 0;
    if (progress == MIDGAME) {
        kp += king_pcsq_table[bsf(pos.bitboard_of(Us, KING))];
        kp -= king_pcsq_table[bsf(pos.bitboard_of(~Us, KING))];
    }

    // Doubled pawns
    int dp = 0;
    for (File file = AFILE; file < NFILES; ++file) {
        dp -= std::max(pop_count(pos.bitboard_of(Us, PAWN) & MASK_FILE[file]) - 1, 0) * 75;
        dp += std::max(pop_count(pos.bitboard_of(~Us, PAWN) & MASK_FILE[file]) - 1, 0) * 75;
    }

    // Passed pawns
    int pp = 0;
    for (Color color = WHITE; color < NCOLORS; ++color) {
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
                for (Rank rank = RANK1; rank <= rank_of(sq); ++rank) {
                    pawns_ahead_mask &= ~MASK_RANK[rank];
                }
            }
            else if (color == BLACK) {
                for (Rank rank = RANK8; rank >= rank_of(sq); --rank) {
                    pawns_ahead_mask &= ~MASK_RANK[rank];
                }
            }
            else {
                throw std::logic_error("Invalid color");
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
                else {
                    throw std::logic_error("Invalid game progress");
                }
            }
        }
    }

    // Isolated pawns
    int ip = 0;
    if (progress == MIDGAME) {
        for (Color color = WHITE; color < NCOLORS; ++color) {
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
        }
    }

    // Open files
    int of = 0;
    for (Color color = WHITE; color < NCOLORS; ++color) {
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
    }

    // Check status
    int cs = 0;
    if (pos.in_check<Us>()) {
        cs = -20;
    }
    else if (pos.in_check<~Us>()) {
        cs = 20;
    }
	return mv + ca + cc + np + bp + rp + kp + pp + ip + of + cs;
}