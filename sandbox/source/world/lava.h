#pragma once
#include <bq.h>
class lava : public bq::block {
	bq::animation animation;
public:
	lava(float x, float y, float w, float h);
	void update() override;
	void render(sf::RenderWindow&) override;
	void interact() override;
};