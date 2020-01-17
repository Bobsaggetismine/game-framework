#pragma once
#include <bq.h>

class bullet : public bq::entity, std::enable_shared_from_this<bullet> {
	sf::Sprite sprite;
	bq::v2f speed;
	bool m_dead = false;
	sf::Sound sound;
	sf::Clock cooldown;
	float m_damage = 8.f;
public:
	void update() override;
	void render(sf::RenderWindow&)override;
	void handleEvent(sf::Event&) override;
	bool shouldCull(sf::View&);
	void damage(float) override;
	bullet(bq::v2f,bq::v2f);
};