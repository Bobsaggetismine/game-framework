#pragma once
#include <bq.h>
class pongworld : public bq::world{
	sf::Sprite background;
public:
	pongworld();
	void render(sf::RenderWindow&) override;
};