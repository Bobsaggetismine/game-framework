#pragma once
#include <bq.h>
#include "../entity/bullet.h"

class gun : public bq::item
{
	sf::Sound sound;
	bq::entity& m_target;
	float m_cooldown = 0.5f;
	sf::Clock m_timer;
public:
	gun(bq::entity& target);
	virtual ~gun() override;
	void action(std::optional<sf::Keyboard::Key>,std::optional<bq::v2f>) override;
};