#pragma once
#include <bq.h>
class door : public bq::block {
	bq::animation animation;
	bool open = false;
	sf::Sound sound;
public:
	door(std::string name, float x, float y, float w, float h);
	void update() override;
	void render(sf::RenderWindow&) override;
	bool intersects(sf::FloatRect&);
	void interact() override;
};
