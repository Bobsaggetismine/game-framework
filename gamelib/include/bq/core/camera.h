#pragma once
#include <bq/common.h>
#include <bq/entity/entity.h>
#include <bq/world/world.h>

namespace bq {
	class camera {
		bq::entity* m_target;
		bq::v2f m_size;
		sf::View m_view;
	public:
		
		camera(bq::entity*);

		const sf::View& view();

		void update();
		void render(sf::RenderWindow&);
		void reset();
	};
}