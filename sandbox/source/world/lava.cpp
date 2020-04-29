#include "lava.h"

lava::lava(float x, float y, float w, float h) : animation("lava.png", 0, 32, 2, 60) {
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
void lava::render(sf::RenderWindow& window) {
	window.draw(animation.get());
}
void lava::update() {
	animation.update();
	animation.get().setPosition({ m_pos.x, m_pos.y });
}
void lava::interact() {}