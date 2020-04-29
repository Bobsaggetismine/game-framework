#pragma once
#include <bq/entity/entity.h>
#include <bq/resource/resource_holder.h>
#include <bq/util/random.h>
#include <bq/util/vec.h>
#include <bq/core/handler.h>
class meele_enemy : public bq::entity
{
	static constexpr int moves_until_movement_change_C = 60;

	float range = 10.f,health = 100.f, move_speed = 1.25f;;
	bool locked_on = false, blocked = false;
	unsigned lockon_multiplier = 50;
	int m_damage = 5, offset = 0, moves_made = 0;

	bq::entity* m_entity;
	bq::v2f movement = { 0,0 };
	sf::Sprite m_sprite;
	sf::Sound sound;
	sf::Clock clock;
	bq::buff m_buff;
public:
	meele_enemy(bq::entity*);
	virtual void update() override;
	virtual void render(sf::RenderWindow& window) override;
	virtual void handle_event(sf::Event& evt) override;
	virtual void damage(float) override;
	virtual bool should_cull(const sf::View&) override;
	virtual void buff(bq::buff) override;
	virtual void unbuff() override;
	virtual void interact() override;
};

