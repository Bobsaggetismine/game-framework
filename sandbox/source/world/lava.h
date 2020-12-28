#pragma once

class lava : public bq::block {
	bq::animation animation;
public:
	lava(float x, float y, float w, float h);
	void update() override;
	void render(bq::window&) override;
	void interact() override;
};