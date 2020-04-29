#pragma once
#include <bq/core/handler.h>
#include <bq/quest/quest.h>
#include <bq/core/logger.h>

class robot_quest : public bq::quest {

	int m_remaining = 10;

public:
	robot_quest();

	void update() override;
	void handleQuestEvent(bq::quest_event&) override;
	void render(sf::RenderWindow&) override;
};