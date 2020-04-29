#include "bq/gui/health_bar.h"

bq::gui::health_bar::health_bar() {
	m_back.setFillColor(sf::Color::Red);
	m_front.setFillColor(sf::Color::White);
	m_back.setPosition(0, 0);
	m_front.setPosition(0, 0);
	m_back.setSize({100,10});
	m_front.setSize({100,10});
}

void bq::gui::health_bar::render(sf::RenderWindow& window) {
	window.draw(m_back);
	window.draw(m_front);
}
void bq::gui::health_bar::update(float f) {
	m_front.setSize({f,10});
}
void bq::gui::health_bar::handle_event(sf::Event& e) {

}
void bq::gui::health_bar::update_pos(float x, float y) {
	m_front.setPosition(x, y);
	m_back.setPosition(x, y);
}