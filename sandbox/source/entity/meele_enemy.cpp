#include "meele_enemy.h"
#include <math.h>

meele_enemy::meele_enemy(std::shared_ptr<bq::entity> player): m_player(player), sound(bq::resource_holder::get().sounds.get("sword.wav")) {
	m_sprite.setTexture(bq::resource_holder::get().textures.get("robot.png"));
	pos = {500,500};
	size = {27,30};
	clock.restart();
	id = 2;
}
void meele_enemy::damage(float dmg) {
	health -= dmg;
}
bool meele_enemy::shouldCull(sf::View&) {
	return health <= 0.f;
}
void meele_enemy::render(sf::RenderWindow& window) {
#ifdef DEBUG
	bq::v2f new_pos = { pos.x - (size.x * lockon_multiplier / 2) + (size.x/2), pos.y - (size.y * lockon_multiplier / 2) + (size.y / 2) };
	bq::v2f new_size = { size.x * lockon_multiplier, size.y * lockon_multiplier };
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
	

	sf::FloatRect player_square(m_player->pos, m_player->size);

	if (!locked_on) {
		bq::v2f new_pos = { pos.x - (size.x * lockon_multiplier / 2) + (size.x / 2), pos.y - (size.y * lockon_multiplier / 2) + (size.y / 2) };
		bq::v2f new_size = { size.x * lockon_multiplier, size.y * lockon_multiplier };
		sf::FloatRect this_square(new_pos, new_size);

		if (this_square.intersects(player_square)) {
			locked_on = true;
		}

	}
	
	//if we're not locked onto the target(player) yet, well randomly move around
	if (!locked_on || clock.getElapsedTime().asSeconds() < 0.8f)
	{
		if (moves_made > moves_until_movement_change_C || moves_made == 0) {
			if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
				if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
					movement.x = -move_speed*m_buff.speed_multiplier;
				}
				else {
					movement.x = move_speed * m_buff.speed_multiplier;
				}
			}
			else {
				if (bq::random::getRandom(0.f, 1.f) > 0.5f) {
					movement.y = -move_speed * m_buff.speed_multiplier;
				}
				else {
					movement.y = move_speed * m_buff.speed_multiplier;
				}
			}
			moves_made = 0;
		}
	}
	else {
		if (m_player->pos.x + (m_player->size.x / 2)+16 > pos.x + (size.x/2)+2 ) {
			movement.x = move_speed * m_buff.speed_multiplier;
		}
		else if(m_player->pos.x + (m_player->size.x / 2)+16 < pos.x + (size.x / 2)+2){
			movement.x = -move_speed * m_buff.speed_multiplier;
		}
		if (m_player->pos.y + (m_player->size.y / 2) + 15 > pos.y + (size.y / 2) + 2) {
			movement.y = move_speed * m_buff.speed_multiplier;
		}
		else if(m_player->pos.y + (m_player->size.y / 2)+15 < pos.y + (size.y / 2)+2){
			movement.y = -move_speed * m_buff.speed_multiplier;
		}
		float x_diff = (m_player->pos.x + (m_player->size.x / 2) + 16) - (pos.x + (size.x / 2) + 2);
		float y_diff = (m_player->pos.y + (m_player->size.y / 2) + 15) - (pos.y + (size.y / 2) + 2);

		if (abs(x_diff) <range && abs(y_diff) < range) {
			bq::logger::debug("damaging player");
			if(clock.getElapsedTime().asSeconds() > 0.8f){
				m_player->damage(m_damage*m_buff.damage_multiplier);
				sound.play();
				clock.restart();
			}
		}
	}
	
	
	
	sf::FloatRect bounds = { pos.x + 2 + movement.x, pos.y + 2 + movement.y, size.x, size.y };
	bq::block_collision_effects bce = bq::handler::get().m_world->get_collision_effects(bounds);
	if (!bce.collides) {
		move(movement);

	}
	else {
		moves_made = -1;
		locked_on = false;
	}
	moves_made++;
	m_sprite.setPosition(pos);
}

void meele_enemy::handleEvent(sf::Event& evt) {

}
void meele_enemy::buff(bq::buff b) {
	if (b.damage_multiplier > m_buff.damage_multiplier) {
		m_buff.damage_multiplier = b.damage_multiplier;
	}
	if (b.speed_multiplier > m_buff.speed_multiplier) {
		m_buff.speed_multiplier = b.speed_multiplier;
	}
}
void meele_enemy::unbuff() {
	//lazy
	m_buff = { 1,1 };
}
void meele_enemy::interact() {

}