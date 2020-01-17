#pragma once
#include <bq/entity/entity.h>
#include <bq/resource/resource_holder.h>
#include <bq/util/random.h>
#include <bq/util/vec.h>
#include <bq/core/handler.h>
class meele_enemy : public bq::entity
{
	bq::v2f movement = { 0,0 };
	sf::Sprite m_sprite;
	float move_speed = 1.f;
	float health = 100;
	const int moves_until_movement_change_C = 60;
	sf::Sound sound;
	sf::Clock clock;
	int moves_made = 0;
	std::shared_ptr<bq::entity> m_player;
	bool locked_on = false;
	unsigned lockon_multiplier = 10;
public:
	meele_enemy(std::shared_ptr<bq::entity>);
	void update() override;
	void render(sf::RenderWindow& window) override;
	void handleEvent(sf::Event& evt) override;
	void damage(float) override;
	bool shouldCull(sf::View&) override;
};

