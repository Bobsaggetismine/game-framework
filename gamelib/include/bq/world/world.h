#pragma once
#include <bq/common.h>
#include <bq/world/block.h>
#include <bq/util/block_collision_effects.h>
#include <bq/core/AStar.hpp>
namespace bq {
	class world {
	protected:

		std::vector<std::shared_ptr<bq::block>> m_blocks;
	public:
		float h = 0.f, w = 0.f;
		void interact(float,float);
		virtual void update();
		//if overriding this, take the default behavior into account, this renders the vector<block> for you by default.
		virtual void render(sf::RenderWindow&);
		virtual std::unique_ptr<std::vector<bq::v2i>> get_path(bq::v2i, bq::v2i) = 0;

		bq::block_collision_effects get_collision_effects(sf::FloatRect&);
	};
}