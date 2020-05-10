#pragma once


class robot_quest : public bq::quest {

	int m_remaining = 10;

public:
	robot_quest();
	virtual ~robot_quest() override;

	void update() override;
	void handleQuestEvent(bq::quest_event&) override;
	void render(sf::RenderWindow&) override;
};