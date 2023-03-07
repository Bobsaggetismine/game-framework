#include "surge/types.h"
#include "surge/tables.h"
#include "surge/position.h"
#include "chess_ai.hpp"
#include "chess_utils.h"
#include <bq.h>
#include <future>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>


class chess_game : public bq::game {
public:

	static constexpr float SQUARE_SIZE = GAME_HEIGHT / 8;
	static constexpr bool PLAYER_ONE = false;
	static constexpr bool PLAYER_TWO = false;

	
	Position m_position;
	negamax_ai_ab m_ai;

	std::future<void> m_ai_future;

	bq::v2i m_selected_square = { -1,-1 };
	std::vector<bq::v2i> m_player_clicks;

	chess_game(): bq::game(GAME_WIDTH, GAME_WIDTH, "Chess Game", 60.f) {}

	void draw_board()
	{
		std::vector<sf::Color> colors = { sf::Color::White, sf::Color::Color::Cyan};
		for(auto i =0; i < 8; ++i)
			for (auto y = 0; y < 8; ++y) {

				
				auto color = colors[(i + y) % 2];
				if (i == m_selected_square.x && y == m_selected_square.y) {
					color = sf::Color::Magenta;
				}
				sf::RectangleShape rs;

				auto turn = m_position.turn();
				if (turn == WHITE) {
					MoveList<WHITE> list(m_position);
					for (auto move : list) {
						if (move.from() == create_square(row_to_file(m_selected_square.y), col_to_rank(m_selected_square.x)) && move.to() == create_square(row_to_file(y), col_to_rank(i))) {
							color = sf::Color::Red;
						}
					}
				}
				else {
					MoveList<BLACK> list(m_position);
					for (auto move : list) {
						if (move.from() == create_square(row_to_file(m_selected_square.y), col_to_rank(m_selected_square.x)) && move.to() == create_square(row_to_file(y), col_to_rank(i))) {
							color = sf::Color::Red;
						}
					}
				}



				rs.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
				rs.setPosition(sf::Vector2f(y*SQUARE_SIZE, i*SQUARE_SIZE));
				rs.setFillColor(color);
				m_window.draw(rs);
			}
	}
	void draw_pieces()
	{
		//inefficient drawing (loading alot of sprites) but its ok because rendering isnt running on AI threads and is fast enough for chess.
		for (float i = 0; i < 8; ++i)
			for (float y = 0; y < 8; ++y) {
				

				File f = row_to_file(int(y));
				Rank r = col_to_rank(int(i));
				
				
				Piece piece = m_position.at(create_square(f,r));

				bq::sprite sprite;
				switch (piece) {
						case Piece::WHITE_PAWN: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("wP.png"));
							break;
						}
						case Piece::WHITE_KNIGHT: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("wN.png"));
							break;
						}
						case Piece::WHITE_BISHOP: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("wB.png"));
							break;
						}
						case Piece::WHITE_ROOK: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("wR.png"));
							break;
						}
						case Piece::WHITE_QUEEN: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("wQ.png"));
							break;
						}
						case Piece::WHITE_KING: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("wK.png"));
							break;
						}
						case Piece::BLACK_PAWN: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("bP.png"));
							break;
						}
						case Piece::BLACK_KNIGHT: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("bN.png"));
							break;
						}
						case Piece::BLACK_BISHOP: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("bB.png"));
							break;
						}
						case Piece::BLACK_ROOK: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("bR.png"));
							break;
						}
						case Piece::BLACK_QUEEN: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("bQ.png"));
							break;
						}
						case Piece::BLACK_KING: {
							sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
							sprite.set_texture(bq::resource_holder::get().textures.get("bK.png"));
							break;
						}
											  
				}
				m_window.draw(sprite);
			}
	}

	void handle_player_clicks(bq::v2f click_pos)
	{
		
		if (!PLAYER_ONE && m_position.turn() == WHITE) return;
		if (!PLAYER_TWO && m_position.turn() == BLACK) return;

		int col = int(click_pos.x / SQUARE_SIZE);
		int row = int(click_pos.y / SQUARE_SIZE);

		if (m_selected_square == bq::v2i(row, col)) {
			m_selected_square = { -1,-1 };
			m_player_clicks.clear();
		}
		else {
			m_selected_square = { row, col };
			m_player_clicks.push_back(m_selected_square);
		}
	}
	template <Color Us>
	void handle_player_move()
	{
		MoveList<Us> list(m_position);
		for (Move move : list) {
			if (move.to() == create_square(row_to_file(m_player_clicks[1].y), col_to_rank(m_player_clicks[1].x)) && move.from() == create_square(row_to_file(m_player_clicks[0].y), col_to_rank(m_player_clicks[0].x))) {
				if (move.flags() == MoveFlags::PROMOTIONS && move.flags() != MoveFlags::PC_QUEEN) continue;
				m_position.play<Us>(move);
			}
		}
	}
	template <Color Us>
	void handle_ai_move(std::future<void>& future) {
		using namespace std::chrono_literals;
		auto status = future.wait_for(0ms);

		if (status == std::future_status::ready)
		{
			future = std::async(std::launch::async, [this]
			{
				auto m = m_ai.find_best_move(m_position);
				m_position.play<Us>(m);
			});
		}
	}

	virtual void update() override
	{
		
		if (!PLAYER_ONE && m_position.turn() == WHITE) {
			handle_ai_move<WHITE>(m_ai_future);
		}

		if (!PLAYER_TWO && m_position.turn() == BLACK) {
			handle_ai_move<BLACK>(m_ai_future);
		}


		if (m_player_clicks.size() == 2) {
			if (m_position.turn() == WHITE) {
				handle_player_move<WHITE>();
			}
			else {
				handle_player_move<BLACK>();
			}
			m_selected_square = { -1,-1 };
			m_player_clicks.clear();
		}
	}
	virtual void render() override
	{
		draw_board();
		draw_pieces();		
	}
	virtual void handleEvent(bq::event& evt) override
	{
		if (evt.type == bq::event_type::CLOSE) {
			m_window.close();
			exit(0);
		}
		else if (evt.type == bq::event_type::MOUSE) {
			handle_player_clicks(evt.mouse_clicked_pos);
		}
		else if (evt.type == bq::event_type::KEYPRESSED) {
			if (evt.keycode == bq::keyboard::keycode::D) {
				bq::logger::info("ai_two nodes searched: " + std::to_string(m_ai.nodes_searched));
			}
		}

	}
	virtual int execute() override
	{
		initialise_all_databases();
		zobrist::initialise_zobrist_keys();
		Position::set("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -", m_position);

		//run future initially with no processing being done, so we can cleanup the ai move function
		m_ai_future = std::async(std::launch::async, [this] {});

		run();
		return EXIT_SUCCESS;
	}

} game;