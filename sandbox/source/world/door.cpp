#include "door.h"

door::door(std::string name, float x, float y, float w, float h) : animation(name, 0, 32, 2, 1),sound(bq::resource_holder::get().sounds.get("door_close.wav")) {
	pos.x = x;
	pos.y = y;
	size.x = w;
	size.y = h;
	animation.get().setPosition({ pos.x, pos.y });
	animation.update();
}
void door::render(sf::RenderWindow& window) {
	window.draw(animation.get());
}
void door::update() {}

bool door::intersects(sf::FloatRect& other) {
	if (open) return false;
	sf::FloatRect rect = { pos.x+14, pos.y, 3, size.y };
	return rect.intersects(other);
}
void door::interact() {
	sound.play();
	animation.update();
	open = !open;
}
