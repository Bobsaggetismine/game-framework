#pragma once

#include <bq.h>
#include "../entity/bullet.h"

class machine_gun : public bq::item
{
	bq::entity& m_target;
	sf::Clock m_timer;
	sf::Sound sound;
	float m_cooldown = 0.1f;
public:
	machine_gun(bq::entity& target);
	virtual ~machine_gun() override;
	void action(std::optional<sf::Keyboard::Key>, std::optional<bq::v2f>) override;
};

