#pragma once

#include <bq.h>

class paddle : public bq::entity
{
	sf::RectangleShape m_shape;

	sf::Keyboard::Key upKeybind, downKeybind;

	bq::v2f m_vel;
public:
	paddle(bq::v2f initial_position, sf::Keyboard::Key upBind, sf::Keyboard::Key downBind);
	void update() override;
	void render(sf::RenderWindow&) override;
	void handle_event(sf::Event&) override;
	void damage(float) override;
	void interact() override;
};

