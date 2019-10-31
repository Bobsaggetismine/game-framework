#pragma once

#include <bq/common.h>

namespace bq {
	class state {
	public:
		virtual void update() = 0;
		virtual void render(sf::RenderWindow& window) = 0;
		virtual void handleEvents(sf::Event& evt, sf::RenderWindow& window) = 0;
	};
}