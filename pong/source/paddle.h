#pragma once

#include <bq.h>

class paddle : public bq::entity
{
	sf::RectangleShape m_shape;

	bq::keyboard::keycode upKeybind, downKeybind;

	bq::v2f m_vel;
public:
	paddle(bq::v2f initial_position, bq::keyboard::keycode upBind, bq::keyboard::keycode downBind);
	void update() override;
	void render(sf::RenderWindow&) override;
	void handle_event(bq::event&) override;
	void damage(float) override;
	void interact() override;
};

