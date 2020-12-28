#pragma once


class menu_state : public bq::state {
	bq::gui::Button m_start_game;
public:
	void startGame();
	menu_state(bq::v2f, bq::v2f);
	void render(sf::RenderWindow&) override;
	void update() override;
	void handleEvents(bq::event&, sf::RenderWindow&) override;
};