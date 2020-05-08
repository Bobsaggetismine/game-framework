#include "game_state.h"

void game_state::render(sf::RenderWindow& window) {
	bq::handler::get().m_world->render(window);
	bq::handler::get().m_em->render(window);
	bq::handler::get().m_cam->render(window);
}
game_state::game_state() {
	
	bq::handler::get().m_world = std::make_unique<pongworld>();
	
	bq::handler::get().m_em = std::make_unique<bq::entity_manager>();
	std::unique_ptr<player> p = std::make_unique<player>();
	m_player = p.get();
	bq::handler::get().m_em->add(std::move(p));
	bq::handler::get().m_cam = std::make_unique<bq::camera>(m_player);
	for(unsigned i = 0; i < 1; ++i){ bq::handler::get().m_em->add(std::make_unique<meele_enemy>(m_player)); }
	bq::handler::get().m_em->add(std::make_unique<buff_enemy>());
	bq::handler::get().m_em->add(std::make_unique<george>(200.f,200.f,m_player));
}
void game_state::update() {
	if (!paused) {
		
		bq::handler::get().m_em->update();
		bq::handler::get().m_world->update();
		bq::handler::get().m_cam->update();
	}
}
void game_state::handleEvents(sf::Event& evt, sf::RenderWindow& window) {
	if (evt.type == sf::Event::KeyPressed) {
		if (evt.key.code == sf::Keyboard::P) {
			paused = !paused;
		}
		else {
			bq::handler::get().m_em->handleEvent(evt);
		}
	}
	else {
		bq::handler::get().m_em->handleEvent(evt);
	}
}