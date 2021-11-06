#pragma once


namespace bq {
	class window;
	class state {
	public:
		virtual void update() = 0;
		virtual void render(bq::window& window) = 0;
		virtual void handleEvents(bq::event& evt, bq::window& window) = 0;
	};
}


