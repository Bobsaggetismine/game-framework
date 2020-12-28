#include <bq.h>
#include "../entity/player.h"
#include "../entity/meele_enemy.h"
#include "../entity/buff_enemy.h"
#include "../entity/george.h"
#include "../world/pongworld.h"
#include "game_state.h"


void game_state::render(bq::window& window) {
	bq::handler::get().world()->render(window);
	bq::handler::get().em()->render(window);
	bq::handler::get().cam()->render(window);
}
game_state::game_state() {
	
	bq::handler::get().set_world(std::make_unique<pongworld>());
	bq::handler::get().set_em(std::make_unique<bq::entity_manager>());
	std::unique_ptr<player> p = std::make_unique<player>();
	m_player = p.get();
	bq::handler::get().em()->add(std::move(p));
	bq::handler::get().set_cam(std::make_unique<bq::camera>(m_player));
	for(unsigned i = 0; i < 1; ++i){ bq::handler::get().em()->add(std::make_unique<meele_enemy>(m_player)); }
	//bq::handler::get().em()->add(std::make_unique<buff_enemy>());
	bq::handler::get().em()->add(std::make_unique<george>(200.f,200.f,m_player));
}
void game_state::update() {
	if (!paused) {
		
		bq::handler::get().em()->update();
		bq::handler::get().world()->update();
		bq::handler::get().cam()->update();
	}
}
void game_state::handleEvents(bq::event& evt, bq::window& window) {
	if (evt.type == bq::event_type::KEYPRESSED) {
		if (evt.keycode == bq::keyboard::keycode::P) {
			paused = !paused;
		}
		else {
			bq::handler::get().em()->handleEvent(evt);
		}
	}
	else {
		bq::handler::get().em()->handleEvent(evt);
	}
}