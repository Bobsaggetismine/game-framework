#pragma once

class player;

class game_state : public bq::state {
	bool paused = false;
	player* m_player;
public:
	game_state();
	void handleEvents (bq::event&, bq::window&) override;
	void update() override;
	void render(bq::window&) override;
};