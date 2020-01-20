#pragma once

#include <bq/entity/entity.h>
#include "player.h"
#include "bq/gui/button.h"
class george : public bq::entity
{
	
	bq::animation upAnimation;
	bq::animation downAnimation;
	bq::animation leftAnimation;
	bq::animation rightAnimation;
	int moves_before_change = 180;
	float movement_threashold = 50.f;
	int moves_made = 0;
	bq::v2f movement = { 0, 0 };
	bq::gui::Button m_dialog;
	sf::Clock dialog_timer;
	bool interacted = false;
public:
	std::shared_ptr<player> m_player;
	sf::Sprite m_sprite;
	george(float x, float y, std::shared_ptr<player> player);
	


	void render(sf::RenderWindow&) override;
	void update() override;
	void handleEvent(sf::Event&) override;
	void damage(float) override;
	bool intersects(sf::FloatRect&) override;
	virtual void interact() override;
};

