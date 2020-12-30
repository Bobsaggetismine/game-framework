#include <bq.h>
#include "rock.h"

rock::rock(float x, float y, float w, float h) : animation("rock.png", 0,32,2,1) {
	m_pos.x = x;
	m_pos.y = y;
	m_size.x = w;
	m_size.y = h;
	animation.get().set_pos( m_pos.x, m_pos.y);
	animation.update();
}
void rock::render(bq::window& window) {
	window.draw(animation.get());
}
void rock::update() {}

bool rock::intersects(sf::FloatRect& other) {
	sf::FloatRect rect = { m_pos.x, m_pos.y, m_size.x, m_size.y};
	return rect.intersects(other);
}
void rock::interact() {
}
bool rock::contains(float x, float y) {
	sf::FloatRect rect = { m_pos.x, m_pos.y, m_size.x, m_size.y };
	return rect.contains({x,y});
}