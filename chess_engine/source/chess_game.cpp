#include <bq.h>
#include <future>
#include <chrono>
#include <thread>
#include "chess_state.hpp"
#include "chess_ai.hpp"
#include "enums.h"
#include <algorithm>
#include <random>

class chess_game : public bq::game {
public:

	static constexpr int BOARD_DIMENSIONS = 8;
	static constexpr int WINDOW_WIDTH = GAME_WIDTH;
	static constexpr int WINDOW_HEIGHT = GAME_HEIGHT;
	static constexpr int SQUARE_SIZE = WINDOW_HEIGHT / BOARD_DIMENSIONS;

	std::map<piece, std::string> piece_string_map = { {piece::rook, "R"},{piece::bishop,"B"},{piece::knight,"N"} ,{piece::queen,"Q"} ,{piece::king,"K"} ,{piece::pawn,"P"} };
	std::map<color, std::string> color_string_map = { {color::black,"b"},{color::white,"w"}};

	chess_state m_state;

	negamax_ai_ab ai_one,ai_two;

	bool player_one = false;
	bool player_two = false;

	bool one_played = false;
	bool two_played = false;

	bool player_one_turn = true;

	bool render_flag = true;

	std::future<void> ai_one_future, ai_two_future;

	std::unique_ptr<std::vector<chess_move>> valid_moves;

	std::vector<std::vector<piece_t>> m_board_copy;
	std::vector<chess_move> move_log_copy;

	bq::v2i selected_sq = { -1,-1 };
	std::vector<bq::v2i> player_clicks;
	
	chess_game(): bq::game(GAME_WIDTH, GAME_WIDTH, "Chess Game", 60.f)
	{
		m_board_copy = m_state.board;
		move_log_copy = m_state.move_log;

		valid_moves = m_state.get_valid_moves();
	}


	void draw_board()
	{
		std::vector<sf::Color> colors = { sf::Color::White, sf::Color::Color(182,146,0)};
		for(auto i =0; i < BOARD_DIMENSIONS; ++i)
			for (auto y = 0; y < BOARD_DIMENSIONS; ++y) {
				auto color = colors[(i + y) % 2];


				if (move_log_copy.size() > 0) {
					auto move = move_log_copy.back();
					if ((move.start_row == i && move.start_col == y) || (move.end_row == i && move.end_col == y))
						color = sf::Color(255, 114, 114);
				}

				if (i == selected_sq.x && y == selected_sq.y) {
					color = sf::Color::Magenta;
				}
				if (!(selected_sq == bq::v2i(-1,-1)))
					for (auto move : *valid_moves)
						if ((move.start_row == selected_sq.x && move.start_col == selected_sq.y) && (move.end_row == i && move.end_col == y))
							color = color = sf::Color::Red;
				
				sf::RectangleShape rs;
				rs.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
				rs.setPosition(sf::Vector2f(y*SQUARE_SIZE, i*SQUARE_SIZE));
				rs.setFillColor(color);
				m_window.draw(rs);
			}
	}
	void draw_pieces()
	{
		for (auto i = 0; i < BOARD_DIMENSIONS; ++i)
			for (auto y = 0; y < BOARD_DIMENSIONS; ++y) {
				auto p = m_board_copy[i][y];
				std::pair<color,piece> e = {color::none, piece::none};
				if (p != e) {
					bq::sprite sprite;
					sprite.set_pos(y * SQUARE_SIZE, i * SQUARE_SIZE);
					sprite.set_texture(bq::resource_holder::get().textures.get(color_string_map[p.first] + piece_string_map[p.second] + ".png"));
					m_window.draw(sprite);
				}
					
			}
	}

	void handle_player_move(bq::v2f click_pos)
	{
		if (!player_one && !player_one_turn) return;
		if (!player_two && player_one_turn) return;
		valid_moves = m_state.get_valid_moves();
		int col = int(click_pos.x / SQUARE_SIZE);
		int row = int(click_pos.y / SQUARE_SIZE);

		if (m_state.board[row][col] == std::make_pair<color, piece>(color::none, piece::none) && player_clicks.size() == 0)
			return;
		if (selected_sq == bq::v2i(row, col)) {
			selected_sq = { -1,-1 };
			player_clicks.clear();
		}
		else {
			selected_sq = { row, col };
			player_clicks.push_back(selected_sq);
		}
		if (player_clicks.size() == 2) {
			chess_move move = chess_move(player_clicks[0], player_clicks[1], m_state.board);
			for (int i = 0; i < valid_moves->size(); ++i)
			{
				if (move == (*valid_moves)[i])
				{
					m_state.make_move((*valid_moves)[i]);
					valid_moves = m_state.get_valid_moves();
					player_one_turn = !player_one_turn;
					break;
				}
				
			}
			selected_sq = { -1,-1 };
			player_clicks.clear();
		}

		if (m_state.checkmate && !player_one_turn) {
			bq::logger::critical("Checkmate, white wins!");
		}
		else if (m_state.checkmate && player_one_turn) {
			bq::logger::critical("Checkmate, black wins!");
		}

		move_log_copy = m_state.move_log;
		m_board_copy = m_state.board;
	}


	virtual void update() override
	{
		using namespace std::chrono_literals;
		

		if (m_state.white_to_move && !player_one && player_one_turn) {


			auto status = std::future_status::ready;
			if(one_played)
				status = ai_one_future.wait_for(0ms);

			if (status == std::future_status::ready || !one_played)
			{
				
				one_played = true;
				ai_one_future = std::async(std::launch::async, [this] {
					valid_moves = m_state.get_valid_moves();
					auto m = ai_one.find_best_move(m_state, *valid_moves);
					m_state.make_move(m);
					m_board_copy = m_state.board;
					move_log_copy = m_state.move_log;
					player_one_turn = false;
					if (m_state.checkmate) {
						bq::logger::critical("Checkmate, white wins!");
					}
				});
			}
			else {
				//bq::logger::info("ai_one nodes searched: " + std::to_string(ai_one.nodes_searched));
			}
		}
		if (!m_state.white_to_move && !player_two && !player_one_turn) {
			auto status = std::future_status::ready;
			if (two_played)
				status = ai_two_future.wait_for(0ms);
			if (status == std::future_status::ready || !two_played) {
				two_played = true;
				ai_two_future = std::async(std::launch::async, [this] {
					valid_moves = m_state.get_valid_moves();
					auto m = ai_two.find_best_move(m_state, *valid_moves);
					m_state.make_move(m);
					m_board_copy = m_state.board;
					move_log_copy = m_state.move_log;
					player_one_turn = true;
					if (m_state.checkmate) {
						bq::logger::critical("Checkmate, white wins!");
					}
				});
			}
			else {
				//bq::logger::info("ai_one nodes searched: " + std::to_string(ai_two.nodes_searched));
			}
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
			handle_player_move(evt.mouse_clicked_pos);
		}
		else if (evt.type == bq::event_type::KEYPRESSED) {
			if (evt.keycode == bq::keyboard::keycode::W) {
				m_state.undo_move();
				m_board_copy = m_state.board;
				move_log_copy = m_state.move_log;
				player_one_turn = !player_one_turn;
			}
		}
		else if (evt.type == bq::event_type::KEYPRESSED) {
			if (evt.keycode == bq::keyboard::keycode::S) {
				m_state.undo_move();
				m_state.undo_move();
				m_board_copy = m_state.board;
				move_log_copy = m_state.move_log;
				player_one_turn = !player_one_turn;
			}
		}
	}
	virtual int execute() override
	{
		bq::logger::log_to_file("log.txt", true);
		run();
		return EXIT_SUCCESS;
	}

} game;