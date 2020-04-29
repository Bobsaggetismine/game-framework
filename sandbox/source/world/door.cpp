#include "door.h"

door::door(std::string name, float x, float y, float w, float h) : animation(name, 0, 32, 2, 1),sound(bq::resource_holder::get().sounds.get("door_close.wav")) {
	m_pos.x = x;
	m_pos.y = y;
	m_size.x = w;
	m_size.y = h;
	animation.get().setPosition({ m_pos.x, m_pos.y });
	animation.update();
}
void door::render(sf::RenderWindow& window) {
	window.draw(animation.get());
}
void door::update() {}

bool door::intersects(sf::FloatRect& other) {
	if (open) return false;
	sf::FloatRect rect = { m_pos.x+14, m_pos.y, 3, m_size.y };
	return rect.intersects(other);
}
void door::interact() {
	sound.play();
	animation.update();
	open = !open;
}
