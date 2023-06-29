#pragma once


class robot_quest : public bq::quest {

	int m_remaining = 10;
	bq::entity* m_entity;
	sf::Text m_text;
public:
	robot_quest(bq::entity*);
	virtual ~robot_quest() override;

	void update() override;
	void handleQuestEvent(bq::quest_event&) override;
	void render(bq::window&) override;
};