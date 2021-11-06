#include "bqpch.h"
#include <bq/graphics/window.h>
#include <bq/world/block.h>
#include <bq/util/block_collision_effects.h>
#include <bq/core/astar.h>
#include <bq/world/world.h>


bq::block_collision_effects bq::world::get_collision_effects(sf::FloatRect& rect) {
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
	return dc;
}
void bq::world::render(bq::window& window) {
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