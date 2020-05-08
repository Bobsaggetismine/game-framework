#pragma once
#include <bq.h>

#include "../entity/player.h"
#include "../entity/meele_enemy.h"
#include "../entity/buff_enemy.h"
#include "../entity/george.h"

class game_state : public bq::state {
	bool paused = false;
	player* m_player;
public:
	game_state();
	void handleEvents (sf::Event&, sf::RenderWindow&) override;
	void update() override;
	void render(sf::RenderWindow&) override;
};