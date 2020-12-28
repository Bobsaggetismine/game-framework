#include <bq.h>
#include "meele_enemy.h"

meele_enemy::meele_enemy(bq::entity* player) : m_entity(player), sound(bq::resource_holder::get().sounds.get("sword.wav")) {
	m_sprite.setTexture(bq::resource_holder::get().textures.get("robot.png"));
	m_pos = { 500,500 };
	m_size = { 27,30 };
	clock.restart();
	m_id = bq::handler::get().em()->register_id("MEELE_ENEMY");
}
void meele_enemy::damage(float dmg) {
	health -= dmg;
}
bool meele_enemy::should_cull(const sf::View&) const {
	return health <= 0.f;
}
void meele_enemy::render(bq::window& window) {
#ifdef DEBUG
	bq::v2f new_pos = { m_pos.x - (m_size.x * lockon_multiplier / 2) + (m_size.x / 2), m_pos.y - (m_size.y * lockon_multiplier / 2) + (m_size.y / 2) };
	bq::v2f new_size = { m_size.x * lockon_multiplier, m_size.y * lockon_multiplier };
	sf::FloatRect this_square(new_pos, new_size);
	sf::RectangleShape bounds_test;
	bounds_test.setPosition(new_pos);
	bounds_test.setSize(new_size);
	bounds_test.setOutlineColor(sf::Color::Yellow);
	bounds_test.setFillColor(sf::Color::Transparent);
	bounds_test.setOutlineThickness(4);
	window.draw(bounds_test);
#endif
	window.draw(m_sprite);
}

//this is some f tier AI for the enemy, which should get slightly improved over time if i learn how to make game ai better.
void meele_enemy::update() {

	sf::FloatRect player_square(m_entity->pos(), m_entity->size());

	if (!locked_on) {
		bq::v2f new_pos = { m_pos.x - (m_size.x * lockon_multiplier / 2) + (m_size.x / 2), m_pos.y - (m_size.y * lockon_multiplier / 2) + (m_size.y / 2) };
		bq::v2f new_size = { m_size.x * lockon_multiplier, m_size.y * lockon_multiplier };
		sf::FloatRect this_square(new_pos, new_size);

		if (this_square.intersects(player_square)) {
			locked_on = true;
			movement = { 0,0 };
		}

	}

	//if we're not locked onto the target(player) yet, well randomly move around
	if (!locked_on || clock.getElapsedTime().asSeconds() < 0.8f)
	{
		if (moves_made > moves_until_movement_change_C || moves_made == 0) {
			if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
				if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
					movement.x = -move_speed * m_buff.m_speed_multiplier;
				}
				else {
					movement.x = move_speed * m_buff.m_speed_multiplier;
				}
			}
			else {
				if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
					movement.y = -move_speed * m_buff.m_speed_multiplier;
				}
				else {
					movement.y = move_speed * m_buff.m_speed_multiplier;
				}
			}
			moves_made = 0;
		}
	}
	else {

		
		if (m_cached_runs >= 10) {
			m_movements.release();
			m_movements = nullptr;
			if (offset == 0) {
				m_movements = bq::handler::get().world()->get_path({ (int)(std::ceil(m_pos.x / 32.f)) , (int)(std::ceil(m_pos.y / 32.f)) }, { (int)(std::ceil(m_entity->pos().x / 32.f)), (int)(std::ceil(m_entity->pos().y / 32.f)) });
			}
			else {
				m_movements = bq::handler::get().world()->get_path({ (int)(std::ceil(m_pos.x / 32.f)) , (int)(std::ceil(m_pos.y / 32.f)) }, { (int)(std::ceil(m_entity->pos().x / 32.f)), (int)(std::ceil(m_entity->pos().y / 32.f)) });
			}
			m_cached_runs = 0;
		}
		else {
			m_cached_runs++;
		}
		

		if (m_movements) {
			if (m_movements->size() > 1) {
				if (!blocked) {
					if ((*m_movements)[m_movements->size() - 2].y > (m_pos.y / 32.f)) {
						movement.y = move_speed * m_buff.m_speed_multiplier;
						offset = 1;
					}
					else if ((*m_movements)[m_movements->size() - 2].y < (m_pos.y / 32.f)) {
						movement.y = -move_speed * m_buff.m_speed_multiplier;
						offset = 0;
					}
					else if ((*m_movements)[m_movements->size() - 2].x > (m_pos.x / 32.f)) {
						movement.x = move_speed * m_buff.m_speed_multiplier;
						offset = -1;
					}
					else if ((*m_movements)[m_movements->size() - 2].x < (m_pos.x / 32.f)) {
						movement.x = -move_speed * m_buff.m_speed_multiplier;
						offset = 0;
					}
					blocked = true;
				}
				else {
					if ((*m_movements)[m_movements->size() - 2].x > (m_pos.x / 32.f)) {
						movement.x = move_speed * m_buff.m_speed_multiplier;
						offset = -1;
					}
					else if ((*m_movements)[m_movements->size() - 2].x < (m_pos.x / 32.f)) {
						movement.x = -move_speed * m_buff.m_speed_multiplier;
						offset = 0;
					}
					else if ((*m_movements)[m_movements->size() - 2].y > (m_pos.y / 32.f)) {
						movement.y = move_speed * m_buff.m_speed_multiplier;
						offset = 1;
					}
					else if ((*m_movements)[m_movements->size() - 2].y < (m_pos.y / 32.f)) {
						movement.y = -move_speed * m_buff.m_speed_multiplier;
						offset = 0;
					}
					blocked = false;
				}
			}
		}



		float x_diff = (m_entity->pos().x + (m_entity->size().x / 2) + 16) - (m_pos.x + (m_size.x / 2) + 2);
		float y_diff = (m_entity->pos().y + (m_entity->size().y / 2) + 15) - (m_pos.y + (m_size.y / 2) + 2);

		if (abs(x_diff) < range && abs(y_diff) < range) {
			bq::logger::debug("damaging player");
			if (clock.getElapsedTime().asSeconds() > 0.8f) {
				m_entity->damage(m_damage * m_buff.m_damage_multiplier);
				sound.play();
				clock.restart();
			}
		}
	}

	sf::FloatRect bounds = { m_pos.x + 2 + movement.x, m_pos.y + 2 + movement.y, m_size.x, m_size.y };
	bq::block_collision_effects bce = bq::handler::get().world()->get_collision_effects(bounds);
	if (!bce.m_collision) {
		move(movement);
	}
	else {
		moves_made = -1;
		locked_on = false;
	}
	moves_made++;
	m_sprite.setPosition(m_pos);

}

void meele_enemy::handle_event(bq::event& evt) {

}
void meele_enemy::buff(bq::buff b) {
	bq::logger::debug("meele enemy buffed");
	if (b.m_damage_multiplier > m_buff.m_damage_multiplier) {
		m_buff.m_damage_multiplier = b.m_damage_multiplier;
	}
	if (b.m_speed_multiplier > m_buff.m_speed_multiplier) {
		m_buff.m_speed_multiplier = b.m_speed_multiplier;
	}
}
void meele_enemy::unbuff() {
	//lazy
	bq::logger::debug("meele enemy unbuffed");
	m_buff = { 1,1 };
}
void meele_enemy::interact() {

}