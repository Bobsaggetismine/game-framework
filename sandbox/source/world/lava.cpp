#include "lava.h"

lava::lava(float x, float y, float w, float h) : animation("lava.png", 0, 32, 2, 60) {
	pos.x = x;
	pos.y = y;
	damage = 1;
	size.x = w;
	isSolid = false;
	size.y = h;
	animation.get().setPosition({ pos.x, pos.y });
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
	animation.get().setPosition({ pos.x, pos.y });
}
void lava::interact() {}