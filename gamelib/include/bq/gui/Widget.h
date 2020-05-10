#pragma once


namespace bq {
	namespace gui {
		class widget {
		public:
			virtual void handle_event(sf::Event& e) = 0;
			virtual void render(sf::RenderWindow& window) = 0;
			class Rectangle : public sf::RectangleShape {};
		};
	}
}