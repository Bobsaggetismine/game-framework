#pragma once
#include <bq.h>

class bullet : public bq::entity, std::enable_shared_from_this<bullet> {
	sf::Sprite sprite;
	bq::v2f speed;
public:
	void update() override;
	void render(sf::RenderWindow&)override;
	void handleEvent(sf::Event&) override;
	bool shouldCull(sf::View&);
	bullet(bq::v2f,bq::v2f);
};