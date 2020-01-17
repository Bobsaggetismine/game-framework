#pragma once
#include <bq/entity/entity.h>
#include <bq/resource/resource_holder.h>
#include <bq/util/random.h>
#include <bq/util/vec.h>
#include <bq/core/handler.h>
class buff_enemy : public bq::entity
{
	bq::v2f movement = { 0,0 };
	sf::Sprite m_sprite;
	float move_speed = 1.6f;
	float health = 250;
	const int moves_until_movement_change_C = 60;
	sf::Sound buff_sound, debuff_sound;
	sf::Clock clock;
	int moves_made = 0;
public:
	buff_enemy();
	void update() override;
	void buff_team();
	void debuff_team();
	void render(sf::RenderWindow& window) override;
	void handleEvent(sf::Event& evt) override;
	void damage(float) override;
	bool shouldCull(sf::View&) override;
};
