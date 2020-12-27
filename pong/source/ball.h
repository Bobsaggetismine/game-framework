#pragma once
#include <bq.h>


class ball : public bq::entity {
	sf::RectangleShape m_shape;
	bq::v2f m_vel;
public:
	ball();
	void update() override;
	void render(sf::RenderWindow&) override;
	void handle_event(sf::Event&) override;
	void damage(float) override;
	void interact() override;
};