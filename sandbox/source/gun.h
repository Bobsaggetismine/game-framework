#pragma once
#include <bq/core/item.h>
#include "entity/bullet.h"
#include <bq/util/vec.h>
#include <bq/core/handler.h>

class gun : public bq::item
{
	sf::Sound sound;
	bq::entity& m_target;
	float m_cooldown = 0.5f;
	sf::Clock m_timer;
public:
	gun(bq::entity& target);
	void action(std::optional<sf::Keyboard::Key>) override;
};