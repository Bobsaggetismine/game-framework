#include <bq.h>
#include "States/menu_state.h"
#include <nlohmann/json.hpp>
class Pong : public bq::game {
	static constexpr unsigned WIDTH = 1920;
	static constexpr unsigned HEIGHT = 1080;
public:
	Pong() : bq::game(WIDTH, HEIGHT, "Pong", 120.f) {
		
		bq::v2f pos = { WIDTH / 2 - 100,HEIGHT / 2 - 50 };
		bq::v2f rect = { 200,100 };
		bq::handler::get().m_sm->push(std::make_unique<menu_state>(pos, rect), false);
	}

	void update() override {
		bq::handler::get().m_sm->update();
	}
	void render() override {
		bq::handler::get().m_sm->render(m_window);
	}
	void handleEvent(sf::Event& evt) override{
		if (evt.type == sf::Event::Closed) {
			m_window.close();
			exit(0);
		}
		else {
			bq::handler::get().m_sm->handle_events(evt, m_window);
		}
	}
	int execute() override {
		bq::logger::log_to_file("log.txt",true); 

		std::ifstream ifs{ "settings.json" };
		nlohmann:: json json_settings = nlohmann::json::parse(ifs);
		run();	

		return EXIT_SUCCESS;
	}
} game;
