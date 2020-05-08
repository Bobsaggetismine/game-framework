#include "robot_quest.h"

robot_quest::robot_quest() {
	m_desc = "Kill 10 robots";
	bq::handler::get().m_em->hook_quest(this);
}
void robot_quest::update() {

}

void robot_quest::handleQuestEvent(bq::quest_event& qe)
{
	if (qe.m_id == bq::handler::get().m_em->get_id("MEELE_ENEMY")) {
		m_remaining--;
		if (m_remaining == 0) {
			//quest completed
		}
	}
}

void robot_quest::render(sf::RenderWindow& window)
{
	sf::Text text;
	std::string txt = std::to_string(m_remaining) + "/10 robots remaining";
	
	text.setPosition(0, 0);
	text.setCharacterSize(20);
	text.setOutlineColor(sf::Color::White);
	text.setFillColor(sf::Color::White);
	text.setFont(bq::resource_holder::get().fonts.get("arial.ttf"));
	text.setString(txt);
	window.draw(text);
}
