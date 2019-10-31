#include "rock.h"

rock::rock(float x, float y, float w, float h) : animation("rock.png", 0,32,2,1) {
	pos.x = x;
	pos.y = y;
	size.x = w;
	size.y = h;
	animation.get().setPosition({pos.x, pos.y});
	animation.update();
}
void rock::render(sf::RenderWindow& window) {
	window.draw(animation.get());
}
void rock::update() {
	//
}

bool rock::intersects(sf::FloatRect& other) {
	sf::FloatRect rect = {pos.x, pos.y, size.x, size.y};
	return rect.intersects(other);
}
void rock::interact() {
}
bool rock::contains(float x, float y) {
	sf::FloatRect rect = { pos.x, pos.y, size.x, size.y };

	return rect.contains({x,y});
}