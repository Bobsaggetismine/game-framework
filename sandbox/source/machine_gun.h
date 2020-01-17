#pragma once

#include "gun.h"

class machine_gun : public bq::item
{
	bq::entity& m_target;
	sf::Clock m_timer;
	sf::Sound sound;
public:
	machine_gun(bq::entity& target);
	void action(std::optional<sf::Event>) override;
};

