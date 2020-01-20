#pragma once


#include "entity.h"

namespace bq {
	class particle : public bq::entity {
		sf::Clock m_life_timer;
		sf::Sprite m_sprite;
		float m_life = 0;
		bq::v2f movement = {2,2};
	public:
		void render(sf::RenderWindow&) override;
		void update() override;
		void handleEvent(sf::Event&) override;
		particle(float x, float y, float life);
		void damage(float) override;
		bool shouldCull(sf::View&) override;
		bool intersects(sf::FloatRect&) override;
		virtual void interact();
	};
}
