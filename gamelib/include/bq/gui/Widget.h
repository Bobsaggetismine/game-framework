#pragma once


namespace bq {
	class event;
	namespace gui {
		class widget {
		public:
			virtual void handle_event(bq::event& e) = 0;
			virtual void render(sf::RenderWindow& window) = 0;
			class Rectangle : public sf::RectangleShape {};
		};
	}
}