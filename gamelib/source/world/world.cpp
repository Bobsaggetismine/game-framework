#include <bq/world/world.h>




bq::block_collision_effects bq::world::get_collision_effects(sf::FloatRect& rect) {
	bq::block_collision_effects dc;
	for (auto block : blocks) {
		if (block->intersects(rect)) {
			dc.collides = block->isSolid;
			dc.damage = block->damage;
			return dc;
		}
	}
	return dc;
}
void bq::world::render(sf::RenderWindow& window) {
	for (auto block : blocks) {
		block->render(window);
	}
}
void bq::world::update() {
	for (auto block : blocks) {
		block->update();
	}
}
void bq::world::interact(float x, float y) {
	for (auto block : blocks) {
		if (block->contains(x, y)) {
			block->interact();
		}
	}
}