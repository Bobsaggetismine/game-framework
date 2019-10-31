#pragma once
#include <bq/common.h>
#include <bq/application/application.h>
namespace bq {
	class  game : public Application {
		sf::Clock clock;
		sf::Time accumulator = sf::Time::Zero;
		sf::Time ups;
	protected:
		sf::RenderWindow window;
		game(unsigned,unsigned,std::string,float);
	public:
		void run();
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void handleEvent(sf::Event&) = 0;
	};
}