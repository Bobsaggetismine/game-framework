#pragma once

class door : public bq::block {
	bq::animation animation;
	bool open = false;
	sf::Sound sound;
public:
	door(std::string name, float x, float y, float w, float h);
	void update() override;
	void render(bq::window&) override;
	bool intersects(sf::FloatRect&);
	void interact() override;
};
