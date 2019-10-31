#pragma once
#include <bq/common.h>
#include <bq/util/vec.h>

namespace bq {
	class entity {
	public:
		bq::v2f pos;
		bq::v2f size;
		int id;

		virtual void update() = 0;
		virtual void render(sf::RenderWindow&) = 0;
		virtual void handleEvent(sf::Event&) = 0;
		virtual bool shouldCull(sf::View&) { return false; }
		void move(bq::v2f& other) { pos += other; }
	};
}