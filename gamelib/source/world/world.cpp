#include <bq/world/world.h>




bq::block_collision_effects bq::world::get_collision_effects(sf::FloatRect& rect) {
	bool found_solid = false;
	bq::block_collision_effects dc;
	for (auto block : m_blocks) {
		if (block->intersects(rect)) {
			dc.m_collision = block->solid();
			dc.m_damage = block->damage();
			if (block->solid()) {
				return dc;
			}
		}
	}
	dc.m_collision = found_solid;
	return dc;
}
void bq::world::render(sf::RenderWindow& window) {
	for (auto block : m_blocks) {
		block->render(window);
	}
}
void bq::world::update() {
	for (auto block : m_blocks) {
		block->update();
	}
}
void bq::world::interact(float x, float y) {
	for (auto block : m_blocks) {
		if (block->contains(x, y)) {
			block->interact();
		}
	}
}