#pragma once


class menu_state : public bq::state {
	bq::gui::Button m_start_game;
public:
	void startGame();
	menu_state(bq::v2f, bq::v2f);
	void render(bq::window&) override;
	void update() override;
	void handleEvents(bq::event&, bq::window&) override;
};