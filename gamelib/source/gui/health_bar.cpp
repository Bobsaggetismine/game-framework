#include "bqpch.h"
#include <bq/entity/entity.h>
#include <bq/gui/Widget.h>
#include "bq/gui/health_bar.h"
#include <bq/event/event.h>
#include <bq/resource/resource_holder.h>
#include <bq/graphics/window.h>

bq::gui::health_bar::health_bar() {
	m_back.setFillColor(sf::Color::Red);
	m_front.setFillColor(sf::Color::White);
	m_back.setPosition(0, 0);
	m_front.setPosition(0, 0);
	m_back.setSize({100,10});
	m_front.setSize({100,10});
}

void bq::gui::health_bar::render(bq::window& window) {
	window.draw(m_back);
	window.draw(m_front);
}
void bq::gui::health_bar::update(float f) {
	m_front.setSize({f,10});
}
void bq::gui::health_bar::handle_event(bq::event& e) {

}
void bq::gui::health_bar::update_pos(float x, float y) {
	m_front.setPosition(x, y);
	m_back.setPosition(x, y);
}