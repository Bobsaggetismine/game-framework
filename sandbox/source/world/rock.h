#pragma once

class rock : public bq::block {
	bq::animation animation;
public:
	rock(float x, float y, float w, float h);
	void update() override;
	void render(sf::RenderWindow&) override;
	bool intersects(sf::FloatRect&);
	void interact() override;
	bool contains(float, float) override;
};