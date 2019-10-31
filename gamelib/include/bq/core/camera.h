#pragma once
#include <bq/common.h>
#include <bq/entity/entity.h>
#include <bq/world/world.h>

namespace bq {
	class camera {

		std::shared_ptr<bq::entity> target;
		bq::v2f m_size;
	public:
		sf::View view;
		camera(std::shared_ptr<bq::entity>);
		void update();
		void render(sf::RenderWindow&);
	};
}