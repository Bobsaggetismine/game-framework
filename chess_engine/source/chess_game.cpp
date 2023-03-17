#include "surge/surge.h"
#include "chess_ai.hpp"
#include "chess_utils.h"
#include <bq.h>
#include <future>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>


#define R2R(x,y) row_to_rank(x,y)
#define C2F(x,y) col_to_file(x,y)




class chess_game : public bq::game {
public:

	static constexpr float SQUARE_SIZE = GAME_HEIGHT / 8;
	bool PLAYER_ONE = true;
	bool PLAYER_TWO = false;

	bool flipped = false;
	bool checkmate = false;
	
	std::future<void> m_ai_future;
	std::string m_pgn;
	std::vector<bq::v2i> m_player_clicks;

	Position m_position;
	Move m_last_move;

	chess_ai m_ai;

	bq::v2i m_selected_square = { -1,-1 };

	sf::Sound m_move_sound;
	bq::gui::Button m_restart_button,m_flip_button;

	bq::gui::Button m_p1_button;
	bq::gui::Button m_p2_button;
	bq::gui::Button m_copy_fen_button;
	bq::gui::Button m_copy_pgn_button;
	bq::gui::Button m_paste_fen_button;

	//rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
	chess_game() : bq::game(GAME_WIDTH, GAME_HEIGHT, "Chess Game", 60.f), m_ai(11), m_position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), m_move_sound(bq::resource_holder::get().sounds.get("move.wav")), m_restart_button({SQUARE_SIZE*8 + 10,10}, {168,50},"Restart",sf::Color::Color(8553090), sf::Color::Color(8553090), 18),
		m_flip_button({ SQUARE_SIZE * 8 + 10,70 }, { 168,50 }, "Flip", sf::Color::Color(8553090), sf::Color::Color(8553090), 18),
		m_p1_button({ SQUARE_SIZE * 8 + 10,130 }, { 168,50 }, "Restart - p1", sf::Color::Color(8553090), sf::Color::Color(8553090), 18),
		m_p2_button({ SQUARE_SIZE * 8 + 10,190 }, { 168,50 }, "Restart - p2", sf::Color::Color(8553090), sf::Color::Color(8553090), 18),
		m_copy_fen_button({ SQUARE_SIZE * 8 + 10,250 }, { 168,50 }, "Copy Fen", sf::Color::Color(8553090), sf::Color::Color(8553090), 18),
		m_paste_fen_button({ SQUARE_SIZE * 8 + 10,310 }, { 168,50 }, "Paste Fen", sf::Color::Color(8553090), sf::Color::Color(8553090), 18),
		m_copy_pgn_button({ SQUARE_SIZE * 8 + 10,370 }, { 168,50 }, "Copy PGN", sf::Color::Color(8553090), sf::Color::Color(8553090), 18)
	{}


	void restart() {
		m_ai.signal_stop();
		m_ai_future.wait();
		checkmate = false;
		m_last_move = Move();
		m_selected_square = { -1,-1 };
		m_pgn = "";
		m_position = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	}
	void flip() {
		flipped = !flipped;
	}
	void restart_p1() {
		PLAYER_ONE = true;
		PLAYER_TWO = false;
		restart();
	}
	void restart_p2() {
		PLAYER_ONE = false;
		PLAYER_TWO = true;
		restart();
	}

	void copy_fen() {
		sf::Clipboard::setString(m_position.fen());
	}
	void copy_pgn() {
		sf::Clipboard::setString(m_pgn);
	}
	void paste_fen() {
		restart();
		m_position = Position(sf::Clipboard::getString());
	}


	void draw_ui() {
		m_restart_button.render(m_window);
		m_flip_button.render(m_window);
		m_p1_button.render(m_window);
		m_p2_button.render(m_window);
		m_copy_fen_button.render(m_window);
		m_copy_pgn_button.render(m_window);
		m_paste_fen_button.render(m_window);
	}
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

				if (create_square(C2F(y,flipped), R2R(i,flipped)) == m_last_move.to() || create_square(C2F(y,flipped), R2R(i,flipped)) == m_last_move.from()) {
					color = sf::Color::Green;
				}


				if (turn == WHITE && PLAYER_ONE) {
					MoveList<WHITE> list(m_position);
					for (auto move : list) {
						if (m_selected_square == bq::v2i{-1,-1}) continue;
						if (move.from() == create_square(C2F(m_selected_square.y,flipped), R2R(m_selected_square.x,flipped)) && move.to() == create_square(C2F(y,flipped), R2R(i,flipped))) {
							color = sf::Color::Red;
						}
					}
				}
				else if (turn == BLACK && PLAYER_TWO){
					MoveList<BLACK> list(m_position);
					for (auto move : list) {
						if (m_selected_square == bq::v2i{ -1,-1 }) continue;
						if (move.from() == create_square(C2F(m_selected_square.y,flipped), R2R(m_selected_square.x,flipped)) && move.to() == create_square(C2F(y,flipped), R2R(i,flipped))) {
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
				

				File f = C2F(int(y),flipped);
				Rank r = R2R(int(i),flipped);
				
				
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

		if (col >= 8) return;

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
			if (move.to() == create_square(C2F(m_player_clicks[1].y,flipped), R2R(m_player_clicks[1].x,flipped)) && move.from() == create_square(C2F(m_player_clicks[0].y,flipped), R2R(m_player_clicks[0].x,flipped))) {
				if (move.flags() == MoveFlags::PR_KNIGHT) continue;
				if (move.flags() == MoveFlags::PR_BISHOP) continue;
				if (move.flags() == MoveFlags::PR_ROOK) continue;

				

				if (Us == BLACK) {
					m_pgn += get_notation(m_position, move) + " ";
				}
				else {
					m_pgn += std::to_string(std::max(1, m_position.ply() + 1 / 2)) + ". " + get_notation(m_position, move) + " ";
				}
				m_position.play<Us>(move);
				m_move_sound.play();
				m_last_move = move;
				checkmate = detect_checkmate(m_position);
				break;
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
				auto m = m_ai.get_best_move(m_position);
				if (Us == BLACK) {
					m_pgn +=  get_notation(m_position, m) + " ";
				}
				else {
					m_pgn += std::to_string(std::max(1,m_position.ply()+1 / 2)) + ". " + get_notation(m_position, m) + " ";
				}
				m_position.play<Us>(m);
				m_move_sound.play();
				m_last_move = m;
				checkmate = detect_checkmate(m_position);
			});
		}
	}

	virtual void update() override
	{
		
		if (checkmate) return;

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
		draw_ui();
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
			if (evt.keycode == bq::keyboard::keycode::F) {
				bq::logger::info("fen: " + m_position.fen() + " 0 0");
			}
			if (evt.keycode == bq::keyboard::keycode::P) {
				bq::logger::info("pgn: " + m_pgn);
			}
		}
		m_restart_button.handle_event(evt);
		m_flip_button.handle_event(evt);
		m_p1_button.handle_event(evt);
		m_p2_button.handle_event(evt);
		m_copy_fen_button.handle_event(evt);
		m_paste_fen_button.handle_event(evt);
		m_copy_pgn_button.handle_event(evt);
	}
	
	
	
	virtual int execute() override
	{
		initialise_all_databases();
		zobrist::initialise_zobrist_keys();
		
		//run future initially with no processing being done, so we can cleanup the ai move function
		m_ai_future = std::async(std::launch::async, [this] {});

		std::function<void(void)> changeState = std::bind(&chess_game::restart, this);
		m_restart_button.setFunc(changeState);

		std::function<void(void)> flip_board = std::bind(&chess_game::flip, this);
		m_flip_button.setFunc(flip_board);

		std::function<void(void)> start_p1 = std::bind(&chess_game::restart_p1, this);
		m_p1_button.setFunc(start_p1);

		std::function<void(void)> start_p2 = std::bind(&chess_game::restart_p2, this);
		m_p2_button.setFunc(start_p2);

		std::function<void(void)> copyfen = std::bind(&chess_game::copy_fen, this);
		m_copy_fen_button.setFunc(copyfen);

		std::function<void(void)> pastefen = std::bind(&chess_game::paste_fen, this);
		m_paste_fen_button.setFunc(pastefen);

		std::function<void(void)> copypgn = std::bind(&chess_game::copy_pgn, this);
		m_copy_pgn_button.setFunc(copypgn);


		run();
		return EXIT_SUCCESS;
	}

} game;