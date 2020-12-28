#include <bq.h>
#include "States/menu_state.h"

//testing out this json lib to see if i want a wrapper for my game engine. 
class Pong : public bq::game {
public:
	Pong() : bq::game(GAME_WIDTH, GAME_HEIGHT, "Pong", 120.f) {

		bq::v2f pos = { GAME_WIDTH / 2 - 100,GAME_HEIGHT / 2 - 50 };
		bq::v2f rect = { 200,100 };
		bq::handler::get().sm()->push(std::make_unique<menu_state>(pos, rect), false);
	}
	void update() override {
		bq::handler::get().sm()->update();
	}
	void render() override {
		bq::handler::get().sm()->render(m_window);
	}
	void handleEvent(bq::event& evt) override{
		if (evt.type == bq::event_type::CLOSE) {
			m_window.close();
			exit(0);
		}
		else {
			bq::handler::get().sm()->handle_events(evt, m_window);
		}
	}
	int execute() override {
		bq::logger::log_to_file("log.txt",true); 
		run();	

		return EXIT_SUCCESS;
	}
} game;
