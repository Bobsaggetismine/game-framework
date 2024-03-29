
#include <bq.h>
#include <math.h>
#include <bq/graphics/sprite.h>
#include "buff_enemy.h"


buff_enemy::buff_enemy() {
	m_sprite.set_texture(bq::resource_holder::get().textures.get("angel.png"));
	m_pos = { 500,500 };
	m_size = { 27,30 };
	clock.restart();
	m_id = bq::handler::get().em()->register_id("BUFF_ENEMY");
	buff_team();
}
void buff_enemy::damage(float dmg) {
	health -= dmg;
	if (health <= 0) {
		debuff_team();
	}
}
bool buff_enemy::should_cull(const sf::View&) const {
	return health <= 0.f;
}
void buff_enemy::render(bq::window& window) {
	window.draw(m_sprite);
}
void buff_enemy::buff_team() {
	for (auto& e : bq::handler::get().em()->entities()) {
		if (e->id() != bq::handler::get().em()->get_id("PLAYER") && e->id() != bq::handler::get().em()->get_id("BUFF_ENEMY")) {
			bq::logger::warn(std::to_string(e->id()));
			e->buff({1.3f,1});
		}
	}
}
void buff_enemy::debuff_team() {
	for (auto& e : bq::handler::get().em()->entities()) {

		if (e->id() != bq::handler::get().em()->get_id("PLAYER") && e->id() != bq::handler::get().em()->get_id("BUFF_ENEMY")) {
			e->unbuff();
		}
	}
}
//this is some f tier AI for the enemy, which should get slightly improved over time if i learn how to make game ai better.
void buff_enemy::update() {



	if (moves_made > moves_until_movement_change_C || moves_made == 0) {
		if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
			if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
				movement.x = -move_speed;
			}
			else {
				movement.x = move_speed;
			}
		}
		else {
			if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
				movement.y = -move_speed;
			}
			else {
				movement.y = move_speed;
			}
		}
		moves_made = 0;
	}

	



	sf::FloatRect bounds = { m_pos.x + 2 + movement.x, m_pos.y + 2 + movement.y, m_size.x, m_size.y };
	bq::block_collision_effects bce = bq::handler::get().world()->get_collision_effects(bounds);
	if (!bce.m_collision) {
		move(movement);

	}
	else {
		moves_made = -1;
	}
	moves_made++;
	m_sprite.set_pos(m_pos.x,m_pos.y);
}

void buff_enemy::handle_event(bq::event& evt) {}

void buff_enemy::interact() {}