#pragma once


class player : public bq::entity {
	bq::animation upAnimation;
	bq::animation downAnimation;
	bq::animation leftAnimation;
	bq::animation rightAnimation;
	sf::Sprite curSprite;
	bq::gui::health_bar hb;
	bq::inventory m_inventory;
	float hp = 100;
	bq::v2f interactPoint = { -11, -11 };
public:
	bq::quest* m_quest = nullptr;

	player();
	virtual ~player();
	void update() override;
	void render(sf::RenderWindow&) override;
	void handle_event(sf::Event&)   override;
	void input();
	void damage(float) override;
	virtual void interact() override;
};