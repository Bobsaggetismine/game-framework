#pragma once
#include <bq/common.h>
#include <bq/world/block.h>
#include <bq/util/block_collision_effects.h>
namespace bq {
	class world {
	protected:

		std::vector<std::shared_ptr<bq::block>> blocks;
	public:
		float h = 0.f, w = 0.f;
		void interact(float,float);
		void update();
		void render(sf::RenderWindow&);
		bq::block_collision_effects get_collision_effects(sf::FloatRect&);
	};
}