#include <bq.h>
#include "States/menu_state.h"
class Pong : public bq::game {
public:
	Pong() : bq::game(1920, 1080, "Pong", 120.f) {
		
		bq::v2f pos = { 1920 / 2 - 100,1080 / 2 - 50 };
		bq::v2f rect = { 200,100 };
		bq::handler::get().m_sm->push(std::make_shared<menu_state>(pos, rect), false);
	}

	void update() override {
		bq::handler::get().m_sm->update();
	}
	void render() override {
		bq::handler::get().m_sm->render(window);
	}
	void handleEvent(sf::Event& evt) override{
		if (evt.type == sf::Event::Closed) {
			//we have to do it this way, because if we just let the textures get destructed at the end of their lifespan (not using raw ptr), thats after window.close() gets called and the OpenGL context is closed. This assures all resources are cleaned up before openGL is closed
			bq::resource_holder::get().close();
			window.close();
			exit(0);
		}
		else {
			bq::handler::get().m_sm->handleEvents(evt, window);
		}
	}
	int execute() override {
		//be careful here, any pre engine initialization code has not run yet, so for example bq::random will not work as expected.
		run();
		return EXIT_SUCCESS;
	}
} game;
