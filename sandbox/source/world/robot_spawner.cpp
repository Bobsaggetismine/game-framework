#include "robot_spawner.h"

robot_spawner::robot_spawner(float x, float y, float w, float h) : animation("lava.png", 0, 32, 2, 60) {
	m_pos.x = x;
	m_pos.y = y;
	m_damage = 1;
	m_size.x = w;
	m_solid = false;
	m_size.y = h;
	animation.get().setPosition({ m_pos.x, m_pos.y });
	animation.update();
	for (int i = 0; i < (int)bq::random::getRandom(0, 1000); ++i) {
		animation.update();
	}

	
}
void robot_spawner::render(sf::RenderWindow& window) {
	window.draw(animation.get());
}
void robot_spawner::update() {

	if (!m_fetched) fetch_player();

	if(m_fetched)
	bq::handler::get().m_em->add(std::make_unique<meele_enemy>(m_player));


	animation.update();
	animation.get().setPosition({ m_pos.x, m_pos.y });
}
void robot_spawner::interact() {}

void robot_spawner::fetch_player()
{
	for (auto& entity : bq::handler::get().m_em->entities()) {
		if (entity->id() == bq::handler::get().m_em->get_id("PLAYER")) {
			m_player = entity.get();
			m_fetched = true;
		}
	}
	if (m_player == nullptr) {
		bq::logger::info("spawner cannot find player!");
	}
}
