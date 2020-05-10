#pragma once


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
	player* m_player;
	sf::Sprite m_sprite;
	george(float x, float y, player* player);
	


	void render(sf::RenderWindow&) override;
	void update() override;
	void handle_event(sf::Event&) override;
	void damage(float) override;
	bool intersects(sf::FloatRect&) override;
	virtual void interact() override;

	void give_quest();
};

