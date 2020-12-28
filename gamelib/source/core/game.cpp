#include "bqpch.h"


#include <bq/entity/entity.h>
#include <bq/application/application.h>
#include <bq/core/game.h>
#include <bq/core/handler.h>
#include <bq/state/state.h>
#include <bq/event/event.h>
bq::game::game(unsigned w, unsigned h, std::string title, float ticks) : m_window({ w,h }, title, sf::Style::Fullscreen) {
	bq::handler::get().set_sm(std::move(std::make_unique<bq::state_manager>()));
	m_ups = sf::seconds(1.f / ticks);
}

bq::v2f intl_get_mouse_pos(sf::Event& evt) {
	bq::v2f offset = { 0,0 };
	if (bq::handler::get().cam() != nullptr) {
		offset = { bq::handler::get().cam()->view().getCenter().x - (bq::handler::get().cam()->view().getSize().x / 2)   , bq::handler::get().cam()->view().getCenter().y - (bq::handler::get().cam()->view().getSize().y / 2) };
	}
	bq::v2f pos = { (float)evt.mouseButton.x + offset.x, (float)evt.mouseButton.y + offset.y };
	return pos;
}

bq::keyboard::keycode intl_convert_keycode(sf::Keyboard::Key key) {
	switch (key) {
		case sf::Keyboard::W:
			return bq::keyboard::keycode::W;
			break;
		case sf::Keyboard::A:
			return bq::keyboard::keycode::A;
			break;
		case sf::Keyboard::S:
			return bq::keyboard::keycode::S;
			break;
		case sf::Keyboard::D:
			return bq::keyboard::keycode::D;
			break;
		case sf::Keyboard::Up:
			return bq::keyboard::keycode::UP;
			break;
		case sf::Keyboard::Left:
			return bq::keyboard::keycode::LEFT;
			break;
		case sf::Keyboard::Down:
			return bq::keyboard::keycode::DOWN;
			break;
		case sf::Keyboard::Right:
			return bq::keyboard::keycode::RIGHT;
			break;
		case sf::Keyboard::Enter:
			return bq::keyboard::keycode::ENTER;
			break;
		case sf::Keyboard::P:
			return bq::keyboard::keycode::P;
			break;
		case sf::Keyboard::Tab:
			return bq::keyboard::keycode::TAB;
			break;
		case sf::Keyboard::Space:
			return bq::keyboard::keycode::SPACE;
			break;
		
		default:
			return bq::keyboard::keycode::NONE;
			break;
	}
}

void bq::game::run() {
	bq::logger::info("running game loop");
	
	while (m_window.isOpen()) {
		sf::Event evt;
		while (m_window.pollEvent(evt)) {
			bq::event* bqevt;

			switch (evt.type) {
			case sf::Event::Closed:
				bqevt = new bq::event(bq::event_type::CLOSE);
				break;
			case sf::Event::KeyPressed:
				bqevt = new bq::event(bq::event_type::KEYPRESSED, intl_convert_keycode(evt.key.code));
				break;
			case sf::Event::KeyReleased:
				bqevt = new bq::event(bq::event_type::KEYRELEASED, intl_convert_keycode(evt.key.code));
				break;
			case sf::Event::MouseButtonPressed:
				bqevt = new bq::event(bq::event_type::MOUSE, intl_get_mouse_pos(evt));
				break;
			default:
				bqevt = new bq::event(bq::event_type::NONE);
				break;
			}
			handleEvent(*bqevt);
			delete bqevt;
		}
		if (m_accumulator > m_ups) {
			m_accumulator -= m_ups;
			update();
		}
		m_window.clear(sf::Color::Black);
		render();
		m_window.display();
		m_accumulator += m_clock.restart();
	}
}
void bq::game::init() {
	bq::logger::info("initializing engine");
	//we dont actually have any init code yet, trying to avoid that but it could become required later.
}