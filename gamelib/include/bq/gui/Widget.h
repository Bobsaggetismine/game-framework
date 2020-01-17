#pragma once
#include <bq/Common.h>

namespace bq {
	namespace gui {
		class widget {
		public:
			virtual void handleEvent(sf::Event& e, sf::RenderWindow& window) = 0;

			virtual void render(sf::RenderWindow& window) = 0;
		
			class Rectangle : public sf::RectangleShape
			{
			public:
				bool isRolledOn(const sf::RenderWindow& window) const;
				bool isClicked(sf::Event, const sf::RenderWindow& window);
			};
		};
	}
}