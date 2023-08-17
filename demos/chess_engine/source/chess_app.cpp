
#include <bq.h>
#include "chess_ai.hpp"
#include "chess_game.hpp"


class chess_app : public bq::game {

	static constexpr float SQUARE_SIZE = GAME_HEIGHT / 8;
	bool m_rendering_flipped = false;
	
	chess_game m_game;

	bq::gui::Button m_restart_button;
	bq::gui::Button m_flip_button;
	bq::gui::Button m_p1_button;
	bq::gui::Button m_p2_button;
	bq::gui::Button m_copy_fen_button;
	bq::gui::Button m_copy_pgn_button;
	bq::gui::Button m_paste_fen_button;
	bq::gui::Button m_undo_button;
	bq::gui::Button m_wwins_button;
	bq::gui::Button m_wlosses_button;
	bq::gui::Button m_draws_button;

public:

	chess_app() : 
		m_game(SQUARE_SIZE, &m_rendering_flipped),
		bq::game(GAME_WIDTH, GAME_HEIGHT, "Chess Game", 60.f), 
	    m_restart_button({SQUARE_SIZE*8 + 10,10}, {168,50},"Restart",sf::Color(8553090), sf::Color(8553090), 18),
		m_flip_button({ SQUARE_SIZE * 8 + 10,70 }, { 168,50 }, "Flip", sf::Color(8553090), sf::Color(8553090), 18),
		m_p1_button({ SQUARE_SIZE * 8 + 10,130 }, { 168,50 }, "Restart - p1", sf::Color(8553090), sf::Color(8553090), 18),
		m_p2_button({ SQUARE_SIZE * 8 + 10,190 }, { 168,50 }, "Restart - p2", sf::Color(8553090), sf::Color(8553090), 18),
		m_copy_fen_button({ SQUARE_SIZE * 8 + 10,250 }, { 168,50 }, "Copy Fen", sf::Color(8553090), sf::Color(8553090), 18),
		m_paste_fen_button({ SQUARE_SIZE * 8 + 10,310 }, { 168,50 }, "Paste Fen", sf::Color(8553090), sf::Color(8553090), 18),
		m_copy_pgn_button({ SQUARE_SIZE * 8 + 10,370 }, { 168,50 }, "Copy PGN", sf::Color(8553090), sf::Color(8553090), 18),
		m_undo_button({ SQUARE_SIZE * 8 + 10,430 }, { 168,50 }, "Undo", sf::Color(8553090), sf::Color(8553090), 18),
		m_wwins_button({ SQUARE_SIZE * 8 + 200, 10}, { 180,50 }, "White Wins: ", sf::Color(8553090), sf::Color(8553090), 18),
		m_wlosses_button({ SQUARE_SIZE * 8 + 200,70 }, { 180,50 }, "White Losses: ", sf::Color(8553090), sf::Color(8553090), 18),
		m_draws_button({ SQUARE_SIZE * 8 + 200,130 }, { 180,50 }, "Draws: ", sf::Color(8553090), sf::Color(8553090), 18)
	{} 

	void flip() noexcept
	{
		m_rendering_flipped = !m_rendering_flipped;
	}	
	void copy_fen() 
	{
		sf::Clipboard::setString(m_game.fen());
	}
	void copy_pgn() 
	{
		sf::Clipboard::setString(m_game.pgn());
	}
	void paste_fen() 
	{
		m_game.restart_pos(sf::Clipboard::getString());
	}
	virtual void update() override
	{
		m_game.update();
		m_wwins_button.set_text("White wins: " + std::to_string(m_game.stats().white_wins));
		m_wlosses_button.set_text("White losses: " + std::to_string(m_game.stats().black_wins));
		m_draws_button.set_text("Draws: " + std::to_string(m_game.stats().draws));
	}
	//rendering functions
	void draw_ui() 
	{
		m_restart_button.render(m_window);
		m_flip_button.render(m_window);
		m_p1_button.render(m_window);
		m_p2_button.render(m_window);
		m_copy_fen_button.render(m_window);
		m_copy_pgn_button.render(m_window);
		m_paste_fen_button.render(m_window);
		m_undo_button.render(m_window);
		m_wwins_button.render(m_window);
		m_wlosses_button.render(m_window);
		m_draws_button.render(m_window);
	}
	void draw_board()
	{
		std::vector<sf::Color> colors = { sf::Color::White, sf::Color::Cyan};
		for(auto i =0; i < 8; ++i)
			for (auto y = 0; y < 8; ++y) {

				
				auto color = colors[(i + y) % 2];
				if (bq::v2i(i,y) == m_game.selected_square()) {
					color = sf::Color::Magenta;
				}
				sf::RectangleShape rs;

				auto turn = m_game.pos().turn();

				if (create_square(col_to_file(y,m_rendering_flipped), row_to_rank(i,m_rendering_flipped)) == m_game.last_move().to() || create_square(col_to_file(y,m_rendering_flipped), row_to_rank(i,m_rendering_flipped)) == m_game.last_move().from()) {
					color = sf::Color::Green;
				}

				if (turn == WHITE && m_game.player_one()) {
					Position pos = m_game.pos();
					MoveList<WHITE> list(pos);
					for (auto move : list) {
						if (m_game.selected_square() == bq::v2i{-1,-1}) continue;
						if (move.from() == create_square(col_to_file(m_game.selected_square().y,m_rendering_flipped), row_to_rank(m_game.selected_square().x,m_rendering_flipped)) && move.to() == create_square(col_to_file(y,m_rendering_flipped), row_to_rank(i,m_rendering_flipped))) {
							color = sf::Color::Red;
						}
					}
				}
				else if (turn == BLACK && m_game.player_two()){
					Position pos = m_game.pos();
					MoveList<BLACK> list(pos);
					for (auto move : list) {
						if (m_game.selected_square() == bq::v2i{ -1,-1 }) continue;
						if (move.from() == create_square(col_to_file(m_game.selected_square().y,m_rendering_flipped), row_to_rank(m_game.selected_square().x,m_rendering_flipped)) && move.to() == create_square(col_to_file(y,m_rendering_flipped), row_to_rank(i,m_rendering_flipped))) {
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
		for (float i = 0; i < 8; ++i)
			for (float y = 0; y < 8; ++y) {
				

				File f = col_to_file(int(y),m_rendering_flipped);
				Rank r = row_to_rank(int(i),m_rendering_flipped);
				
				
				Piece piece = m_game.pos().at(create_square(f,r));

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
		m_game.handle_event(evt);
		m_restart_button.handle_event(evt);
		m_flip_button.handle_event(evt);
		m_p1_button.handle_event(evt);
		m_p2_button.handle_event(evt);
		m_copy_fen_button.handle_event(evt);
		m_paste_fen_button.handle_event(evt);
		m_copy_pgn_button.handle_event(evt);
		m_undo_button.handle_event(evt);
	}
	void init_gui()
	{
		std::function<void(void)> restart_fun =   std::bind(&chess_game::restart, &m_game);
		m_restart_button.setFunc(restart_fun);

		std::function<void(void)> start_p1 =    std::bind(&chess_game::restart_p1, &m_game);
		m_p1_button.setFunc(start_p1);

		std::function<void(void)> start_p2 =    std::bind(&chess_game::restart_p2, &m_game);
		m_p2_button.setFunc(start_p2);

		std::function<void(void)> undof = 	 	std::bind(&chess_game::undo, &m_game);
		m_undo_button.setFunc(undof);


		std::function<void(void)> flip_board =  std::bind(&chess_app::flip, this);
		m_flip_button.setFunc(flip_board);

		std::function<void(void)> copyfen = 	std::bind(&chess_app::copy_fen, this);
		m_copy_fen_button.setFunc(copyfen);

		std::function<void(void)> pastefen = 	std::bind(&chess_app::paste_fen, this);
		m_paste_fen_button.setFunc(pastefen);

		std::function<void(void)> copypgn = 	std::bind(&chess_app::copy_pgn, this);
		m_copy_pgn_button.setFunc(copypgn);

		
	}
	virtual int execute() override
	{
		initialise_all_databases();
		zobrist::initialise_zobrist_keys();
		init_gui();
		run();
		return EXIT_SUCCESS;
	}

} game;