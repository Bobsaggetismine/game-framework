#include <bq.h>
#include "robot_quest.h"

robot_quest::robot_quest(bq::entity* e): m_entity(e) {
	m_desc = "Kill 10 robots";
	bq::handler::get().em()->hook_quest(this);
	m_text.setCharacterSize(20);
	m_text.setOutlineColor(sf::Color::White);
	m_text.setFillColor(sf::Color::White);
	m_text.setFont(bq::resource_holder::get().fonts.get("arial.ttf"));
}
robot_quest::~robot_quest()
{
}
void robot_quest::update() {

}

void robot_quest::handleQuestEvent(bq::quest_event& qe)
{
	if (qe.m_id == bq::handler::get().em()->get_id("MEELE_ENEMY")) {
		m_remaining--;
		if (m_remaining == 0) {
			//quest completed
		}
	}
}

void robot_quest::render(bq::window& window)
{
	sf::RectangleShape outline;
	outline.setPosition({ m_entity->pos().x - (GAME_WIDTH/2)+1, m_entity->pos().y - (GAME_HEIGHT/2)+1 });
	outline.setSize({150,150});
	outline.setOutlineColor(sf::Color::Yellow);
	outline.setFillColor(sf::Color::Blue);
	outline.setOutlineThickness(1);
	window.draw(outline);



	std::string txt = "QUEST:\n\n" + std::to_string(m_remaining) + "/10 \nrobots \nremaining";
	m_text.setPosition({ m_entity->pos().x - (GAME_WIDTH / 2) + 20, m_entity->pos().y - (GAME_HEIGHT / 2) + 20 });
	m_text.setString(txt);
	window.draw(m_text);
}
