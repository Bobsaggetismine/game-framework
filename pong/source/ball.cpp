#include "ball.h"

ball::ball() {
	m_pos = { GAME_WIDTH / 2, GAME_HEIGHT / 2 };
	m_size = { 10,10 };
	m_shape.setFillColor(sf::Color::Blue);
	m_shape.setPosition({0,0});
	m_shape.setSize({0,0});
	m_vel = { 1,1 };
}

void ball::update()
{
	m_pos += m_vel;

	if (m_pos.x + m_size.x > GAME_WIDTH) {
		m_vel.x *= -1;
	}
	else if (m_pos.x < 0) {
		m_vel.x *= -1;
	}
	if (m_pos.y + m_size.y > GAME_HEIGHT) {
		m_vel.y *= -1;
	}
	else if (m_pos.y < 0) {
		m_vel.y *= -1;
	}


	m_shape.setPosition(m_pos);
	m_shape.setSize(m_size);
}

void ball::render(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void ball::handle_event(sf::Event&)
{
}

void ball::damage(float)
{
}

void ball::interact()
{
}
