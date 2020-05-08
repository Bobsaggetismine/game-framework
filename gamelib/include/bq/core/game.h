#pragma once
#include <bq/common.h>
#include <bq/application/application.h>
namespace bq {
	class  game : public application {
		sf::Clock m_clock;
		sf::Time m_accumulator = sf::Time::Zero;
		sf::Time m_ups;
	protected:
		sf::RenderWindow m_window;
		
		game(unsigned,unsigned,std::string,float);

	public:
		
		void run();
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void handleEvent(sf::Event&) = 0;
		void init() override;
	};
}