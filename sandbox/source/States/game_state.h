#pragma once

class player;

class game_state : public bq::state {
	bool paused = false;
	player* m_player;
public:
	game_state();
	void handleEvents (bq::event&, sf::RenderWindow&) override;
	void update() override;
	void render(sf::RenderWindow&) override;
};