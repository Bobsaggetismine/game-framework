#include "paddle.h"


paddle::paddle(bq::v2f initial_position, sf::Keyboard::Key upBind, sf::Keyboard::Key downBind) {
	upKeybind = upBind;
	downKeybind = downBind;
	m_pos = initial_position;
	m_size = { 10,100 };
	m_shape.setFillColor(sf::Color::Blue);
	m_shape.setPosition({ 0,0 });
	m_shape.setSize({ 0,0 });
	m_vel = { 0,0 };
}



void paddle::update()
{

	if ((m_pos + m_vel).y > 980) {
		if (m_vel.y < 0) {
			m_pos += m_vel;
		}
	}
	else if ((m_pos + m_vel).y < 0) {
		if (m_vel.y > 0) {
			m_pos += m_vel;
		}
	}
	else {
		m_pos += m_vel;
	}
	m_shape.setPosition(m_pos);
	m_shape.setSize(m_size);
}

void paddle::render(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void paddle::handle_event(sf::Event& evt)
{
	if (evt.type == sf::Event::KeyPressed) {
		if (evt.key.code == upKeybind) {
			m_vel.y = -1;
		}
		if (evt.key.code == downKeybind) {
			m_vel.y = 1;
		}
	}
	else if (evt.type == sf::Event::KeyReleased) {
		if (evt.key.code == upKeybind) {
			if(m_vel.y == -1.f)
			m_vel.y = 0;
		}
		if (evt.key.code == downKeybind) {
			if (m_vel.y == 1.f)
			m_vel.y = 0;
		}
	}
}

void paddle::damage(float)
{
}

void paddle::interact()
{
}
