#pragma once


namespace bq {
	class event;
	class window;
	namespace gui {
		class widget {
		public:
			virtual void handle_event(bq::event& e) = 0;
			virtual void render(bq::window& window) = 0;
			class Rectangle : public sf::RectangleShape {};
		};
	}
}