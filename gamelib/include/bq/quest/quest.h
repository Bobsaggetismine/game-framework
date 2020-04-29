#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <bq/quest/quest_event.h>
namespace bq {
	class quest {
	protected:
		bool m_completed = false;
		std::string m_desc;
	public:
		bool completed();
		virtual void update() = 0;
		virtual void handleQuestEvent(quest_event&) = 0;
		virtual void render(sf::RenderWindow& window) = 0;
	};
}
