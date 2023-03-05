#pragma once
#include "chess_state.hpp"
#include <random>
#include "enums.h"


#define ANALYTICS true

std::map<piece, float> piece_scores = { {piece::king,5},{piece::queen , 10},{piece::rook , 5},{piece::bishop, 3},{piece::knight , 3},{piece::pawn , 1} };



struct negamax_ai_ab {

	const float checkmate_score = 1000;
	const float stalemate_score = 0;

    const int max_depth = 5;

    

    chess_move* nextMove;

    std::map<piece, std::vector<std::vector<int>>> white_pos_awareness_map, black_pos_awareness_map;

    int nodes_searched = 0;

    negamax_ai_ab()
    {
        setup_pos_awareness_maps();
    }

    void setup_white_pos_awareness_map() {

        white_pos_awareness_map[piece::knight] = {
            {1,1,1,1,1,1,1,1},
            {1,2,2,2,2,2,2,0},
            {1,2,3,3,3,3,2,0},
            {1,2,3,4,4,3,2,0},
            {1,2,3,4,4,3,2,0},
            {1,2,3,3,3,3,2,0},
            {1,2,2,2,2,2,2,0},
            {1,0,0,0,0,0,0,0},
        };
        white_pos_awareness_map[piece::queen] = {
            {1,1,1,3,1,1,1,1},
            {1,2,3,3,3,1,1,1},
            {1,4,3,3,3,4,2,1},
            {1,2,3,3,3,2,2,1},
            {1,2,3,3,3,2,2,1},
            {1,4,3,3,3,4,2,1},
            {1,1,2,3,3,1,1,1},
            {1,1,1,3,1,1,1,1},
        };
        white_pos_awareness_map[piece::rook] = {
            {4,3,4,4,4,4,3,4},
            {4,4,4,4,4,4,4,4},
            {1,1,2,3,3,2,1,1},
            {1,2,3,4,4,3,2,1},
            {1,2,3,4,4,3,2,1},
            {1,1,2,2,2,2,1,1},
            {4,4,4,4,4,4,4,4},
            {4,3,4,4,4,4,3,4},
        };
        white_pos_awareness_map[piece::pawn] = {
           {8,8,8,8,8,8,8,8},
           {8,8,8,8,8,8,8,8},
           {5,6,6,7,7,6,6,5},
           {2,3,3,5,5,3,3,2},
           {1,2,3,4,4,3,2,1},
           {1,1,2,3,3,2,1,1},
           {1,1,1,0,0,1,1,1},
           {0,0,0,0,0,0,0,0},
        };

        white_pos_awareness_map[piece::bishop] = {
            {4,3,2,1,1,2,3,4},
            {3,4,3,2,2,3,4,3},
            {2,3,4,3,3,4,3,2},
            {1,2,3,4,4,3,2,1},
            {1,2,3,4,4,3,2,1},
            {2,3,4,3,3,4,3,2},
            {3,4,3,2,2,3,4,3},
            {4,3,2,1,1,2,3,4},
        };
        


        white_pos_awareness_map[piece::king] = {
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
        };
        
       
        
    }
    void setup_black_pos_awareness_map() {
        black_pos_awareness_map[piece::pawn] = white_pos_awareness_map[piece::pawn];
        std::reverse(black_pos_awareness_map[piece::pawn].begin(), black_pos_awareness_map[piece::pawn].end());
        
        black_pos_awareness_map[piece::knight] = white_pos_awareness_map[piece::knight];
        std::reverse(black_pos_awareness_map[piece::knight].begin(), black_pos_awareness_map[piece::knight].end());

        black_pos_awareness_map[piece::bishop] = white_pos_awareness_map[piece::bishop];
        std::reverse(black_pos_awareness_map[piece::bishop].begin(), black_pos_awareness_map[piece::bishop].end());

        black_pos_awareness_map[piece::rook] = white_pos_awareness_map[piece::rook];
        std::reverse(black_pos_awareness_map[piece::rook].begin(), black_pos_awareness_map[piece::rook].end());

        black_pos_awareness_map[piece::queen] = white_pos_awareness_map[piece::queen];
        std::reverse(black_pos_awareness_map[piece::queen].begin(), black_pos_awareness_map[piece::queen].end());

        black_pos_awareness_map[piece::king] = white_pos_awareness_map[piece::king];
        std::reverse(black_pos_awareness_map[piece::king].begin(), black_pos_awareness_map[piece::king].end());
    }
    void setup_pos_awareness_maps() {
        setup_white_pos_awareness_map();
        setup_black_pos_awareness_map();
    }


    

    void order_moves(chess_state& gs, std::vector<chess_move>& moves) {
        std::sort(moves.begin(), moves.end(), [gs](chess_move& lhs, chess_move& rhs) mutable -> bool {
            return lhs.piece_captured.first != color::none;
        });
    }

    

    int score_board(chess_state& gs, const std::vector<chess_move>& moves) {

        if (gs.checkmate) {
            if (gs.white_to_move) {
                return -checkmate_score;
            }
            else {
                return checkmate_score;
            }
        }
        else if (gs.stalemate) {
            if (gs.white_to_move) {
                return -checkmate_score;
            }
            else {
                return checkmate_score;
            }
        }

        int score = 0;
        score += (moves.size() * 0.001);

        

        for (int i = 0; i < gs.board.size(); i++) {
            for (int j = 0; j < gs.board[i].size(); j++) {
                piece_t piece = gs.board[i][j];
                if (piece.first == color::white) {
                    score += (piece_scores[piece.second] + white_pos_awareness_map[piece.second][i][j]);
                }
                else if (piece.first == color::black) {
                    score -= (piece_scores[piece.second] + black_pos_awareness_map[piece.second][i][j]);
                }
            }
        }
        return score;
    }

    chess_move find_best_move(chess_state& gs, std::vector<chess_move>& moves) {

        #if ANALYTICS
            bq::logger::info("------------------------------------------");
        #endif

        nextMove = &moves[0];
        auto rng = std::default_random_engine{};
        order_moves(gs,moves);
        get_best_move(gs, moves, max_depth, -checkmate_score, checkmate_score, gs.white_to_move ? 1 : -1);
        nodes_searched = 0;
        return (*nextMove);
    }
    
    
    int searchCaptures(chess_state& gs, std::vector<chess_move>& moves, int turnMultiplier) {

        
        

        if (moves.size() == 0) return score_board(gs,moves);

        for (auto move : moves) {
            gs.make_move(move);
            auto valid_moves = gs.get_valid_moves();
            int score = -searchCaptures(gs, *valid_moves, -turnMultiplier);
            gs.undo_move();
        }
    }

    


    int get_best_move(chess_state& gs, std::vector<chess_move>& moves, int depth, int alpha, int beta, int turnMultiplier, bool depth_already_extended = false) {
        if (depth == 0) {

            if (depth_already_extended) return turnMultiplier * score_board(gs, moves);

            auto v_moves = moves;


            for (int i = v_moves.size() - 1; i >= 0; --i) {
                if (gs.board[v_moves[i].end_row][v_moves[i].end_col] == gs.empty_piece || gs.board[v_moves[i].end_row][v_moves[i].end_col] == gs.white_pawn || gs.board[v_moves[i].end_row][v_moves[i].end_col] == gs.black_pawn) {
                    v_moves.erase(v_moves.begin() + i);
                }
            }
            if (v_moves.size() > 0 ) {
                return -get_best_move(gs, v_moves, 1, -beta, -alpha, -turnMultiplier, true);
            }
            else {
                return turnMultiplier * score_board(gs, moves);
            }
        }
        int maxScore = -checkmate_score;
        for (auto& move : moves) {
            gs.make_move(move);
            #if ANALYTICS
                nodes_searched++;
            #endif
            auto nextMoves = gs.get_valid_moves();
            order_moves(gs, *nextMoves);
            int score = -get_best_move(gs, *nextMoves, depth - 1, -beta, -alpha, -turnMultiplier, depth_already_extended);
            if (score > maxScore) {
                maxScore = score;
                if (depth == max_depth) {
                    nextMove = &move;
                    #if ANALYTICS
                        bq::logger::info(nextMove->get_chess_notation_old() + " : " + std::to_string(score) + " : " + std::to_string(nodes_searched));
                    #endif
                }
            }
            gs.undo_move();
            if (maxScore > alpha) {
                alpha = maxScore;
            }
            if (alpha >= beta) {
                break;
            }
        }
        return maxScore;
    }



};