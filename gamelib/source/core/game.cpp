#include "bqpch.h"

#include <bq/graphics/window.h>
#include <bq/entity/entity.h>
#include <bq/application/application.h>
#include <bq/core/game.h>
#include <bq/core/handler.h>
#include <bq/state/state.h>
#include <bq/event/event.h>
bq::game::game(int w, int h, std::string title, float ticks) : m_window(w,h,title) {
	bq::handler::get().set_sm(std::move(std::make_unique<bq::state_manager>()));
	m_ups = sf::seconds(1.f / ticks);
}


void bq::game::run() {
	bq::logger::info("running game loop");
	
	while (m_window.open()) {
		
		auto evt = m_window.poll_event();
		while (evt.type != bq::event_type::NONE) {
				handleEvent(evt);
				evt = m_window.poll_event();
		}
		if (m_accumulator > m_ups) {
			m_accumulator -= m_ups;
			update();
			m_window.clear(bq::colour::BLACK);
			render();
			m_window.show();
		}
		
		m_accumulator += m_clock.restart();
	}
}
void bq::game::init() {
	bq::logger::info("initializing engine");
	//we dont actually have any init code yet, trying to avoid that but it could become required later.
}