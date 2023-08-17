#include "book.hpp"

book::book()
{
    std::ifstream t("res/books/book2.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string file_contents = buffer.str();
    auto games = split(file_contents, "\n");
    
    int idx = 0;

    for (auto& game : games)
    {
        Position p("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        auto tokens = split(game, " ");
        std::vector<std::string> updated_tokens;
        for (auto& token : tokens) {
            if (p.turn() == WHITE) {
                MoveList<WHITE> moves(p);
                for (Move move : moves) {
                    if (get_notation(p, move) == token) {
                        updated_tokens.push_back(move.str());
                        p.play<WHITE>(move);
                    }
                }
            }
            else {
                MoveList<BLACK> moves(p);
                for (Move move : moves) {
                    if (get_notation(p, move) == token) {
                        updated_tokens.push_back(move.str());
                        p.play<BLACK>(move);
                    }
                }
            }
        }
        m_games.push_back(updated_tokens);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_games.begin(), m_games.end(),g);
    bq::logger::info("games loaded from book: " + std::to_string(m_games.size()));
}

void book::reset()
{
    m_move_history.clear();
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_games.begin(), m_games.end(),g);
}

void book::add_move(Move move)
{
    m_move_history.push_back(move);
}