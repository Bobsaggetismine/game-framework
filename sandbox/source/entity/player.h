#pragma once

#include <bq.h>
#include "../world/pongworld.h"
#include "../States/menu_state.h"

#include "bullet.h"
#include "../machine_gun.h"
#include <bq/gui/health_bar.h>

class player : public bq::entity {
	bq::animation upAnimation;
	bq::animation downAnimation;
	bq::animation leftAnimation;
	bq::animation rightAnimation;
	sf::Sprite curSprite;
	bq::gui::health_bar hb;
	bq::inventory m_inventory;
	int hp = 100;
	bq::v2f interactPoint = { -11, -11 };
public:
	player();
	void update() override;
	void render(sf::RenderWindow&) override;
	void handleEvent(sf::Event&)   override;
	void input();
	void damage(float) override;
	virtual void interact() override;
};