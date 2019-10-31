#include <bq/core/game.h>
#include <bq/util/random.h>
#include <bq/core/handler.h>
bq::game::game(unsigned w, unsigned h, std::string title, float ticks) : window({w,h},title, sf::Style::Fullscreen) {
	bq::handler::get().m_sm = std::make_shared<bq::state_manager>();
	ups = sf::seconds(1.f / ticks);
}
void bq::game::run() {
	
	bq::random::init();
	
	while (window.isOpen()) {
		sf::Event evt;
		while (window.pollEvent(evt)) {
			handleEvent(evt);
		}
		if (accumulator > ups) {
			accumulator -= ups;
			update();
		}
		window.clear(sf::Color::Black);
		render();
		window.display();
		accumulator += clock.restart();
	}
}