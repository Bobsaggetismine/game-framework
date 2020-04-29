#include <bq/core/game.h>
#include <bq/util/random.h>
#include <bq/core/handler.h>
bq::game::game(unsigned w, unsigned h, std::string title, float ticks) : m_window({w,h},title, sf::Style::Fullscreen) {
	bq::handler::get().m_sm = std::make_unique<bq::state_manager>();
	m_ups = sf::seconds(1.f / ticks);
}

void bq::game::run() {
	bq::logger::info("running game loop");
	
	while (m_window.isOpen()) {
		sf::Event evt;
		while (m_window.pollEvent(evt)) {
			handleEvent(evt);
		}
		if (m_accumulator > m_ups) {
			m_accumulator -= m_ups;
			update();
		}
		m_window.clear(sf::Color::Black);
		render();
		m_window.display();
		m_accumulator += m_clock.restart();
	}
}
void bq::game::init() {
	bq::logger::info("initializing engine");
	//we dont actually have any init code yet, trying to avoid that but it could become required later.
}