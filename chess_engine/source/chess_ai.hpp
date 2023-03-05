#pragma once
#include "chess_state.hpp"
#include <random>
#include "enums.h"


#define ANALYTICS true
#define CHESS_DEBUG true
std::map<piece, int> piece_scores = { {piece::king,5},{piece::queen , 10},{piece::rook , 5},{piece::bishop, 3},{piece::knight , 3},{piece::pawn , 1},{piece::none, 0} };



struct negamax_ai_ab {

	const int checkmate_score = 1000;
	const int stalemate_score = 0;

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


    

    void order_moves(chess_state& gs, std::vector<chess_move>& nextMoves) {
        std::sort(nextMoves.begin(), nextMoves.end(), [](chess_move& lhs, chess_move& rhs) -> bool {
            piece_t lhs_take = lhs.piece_captured;
            piece_t rhs_take = rhs.piece_captured;
            return piece_scores[lhs_take.second] > piece_scores[rhs_take.second];
           });
    }

    

    int score_board(chess_state& gs) {

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

    int score_board_after_all_attacks(chess_state& gs, int depth,int alpha, int beta, int turn_multiplier) {


        auto moves = gs.get_valid_moves(true);
        

        if(moves->size() == 0 || depth == 5)
            return score_board(gs);
        #if CHESS_DEBUG
            for (auto move : *moves) {
                if (move.piece_captured == gs.empty_piece) {
                    if (move.piece_moved.second == piece::pawn) {
                        if (!move.is_enpassant) {
                            bq::logger::critical("generated invalid pawn move!");
                            bq::logger::critical(move.get_chess_notation_old());
                        }
                    }
                    else if (move.piece_moved.second == piece::bishop) {
                        bq::logger::critical("generated invalid bishop move!");
                    }
                    else if (move.piece_moved.second == piece::rook) {
                        bq::logger::critical("generated invalid rook move!");
                    }
                    else if (move.piece_moved.second == piece::knight) {
                        bq::logger::critical("generated invalid knight move!");
                    }
                    else if (move.piece_moved.second == piece::king) {
                        bq::logger::critical("generated invalid king move!");
                    }
                    else if (move.piece_moved.second == piece::queen) {
                        bq::logger::critical("generated invalid king move!");
                    }
                }
            }
        #endif

        //bq::logger::info(std::to_string(moves->size()));

        int bestScore =  -checkmate_score;

        for (auto move : *moves) {
            gs.make_move(move);
            #if ANALYTICS
                        nodes_searched++;
            #endif
            int score = -score_board_after_all_attacks(gs, depth+1,-beta,-alpha, -turn_multiplier);
            gs.undo_move();
            if (score > bestScore) {
                bestScore = score;
            }
            if (bestScore > alpha) {
                alpha = bestScore;
            }
            if (alpha >= beta) {
                break;
            }
        }
        return bestScore;
    }


    int get_best_move(chess_state& gs, std::vector<chess_move>& moves, int depth, int alpha, int beta, int turnMultiplier, bool depth_extension = false) {
        if (depth == 0) {
            return turnMultiplier * score_board(gs);
            return turnMultiplier * score_board_after_all_attacks(gs,0,alpha,beta,turnMultiplier);
        }
        int maxScore = -checkmate_score;
        for (auto& move : moves) {
            gs.make_move(move);
            #if ANALYTICS
                nodes_searched++;
            #endif
            auto nextMoves = gs.get_valid_moves(false);
            order_moves(gs, *nextMoves);

            int score = -get_best_move(gs, *nextMoves, depth - 1, -beta, -alpha, -turnMultiplier, depth_extension);
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