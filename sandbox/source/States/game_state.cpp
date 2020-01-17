#include "game_state.h"
#include "../entity/meele_enemy.h"
#include "../entity/buff_enemy.h"
void game_state::render(sf::RenderWindow& window) {
	bq::handler::get().m_world->render(window);
	bq::handler::get().m_em->render(window);
	bq::handler::get().m_cam->render(window);
}
game_state::game_state(): _player(std::make_shared<player>())  {
	bq::handler::get().m_world = std::make_shared<pongworld>();
	bq::handler::get().m_cam = std::make_shared<bq::camera>(_player);
	bq::handler::get().m_em = std::make_shared<bq::entity_manager>();
	bq::handler::get().m_em->add(_player);
	for(unsigned i = 0; i < 150; ++i){ bq::handler::get().m_em->add(std::make_shared<meele_enemy>(_player)); }
	bq::handler::get().m_em->add(std::make_shared<buff_enemy>());

}
void game_state::update() {
	if (!paused) {
		bq::handler::get().m_world->update();
		bq::handler::get().m_cam->update();
		bq::handler::get().m_em->update();
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
}