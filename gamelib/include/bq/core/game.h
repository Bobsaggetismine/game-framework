#pragma once

class application;

#include <bq/graphics/window.h>

namespace bq {

	class event;
	class  game : public application {
		sf::Clock m_clock;
		sf::Time m_accumulator = sf::Time::Zero;
		sf::Time m_ups;
	protected:
		bq::window m_window;
		
		game(int,int,std::string,float);

	public:
		
		void run();
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void handleEvent(bq::event&) = 0;
		void init() override;
	};
}