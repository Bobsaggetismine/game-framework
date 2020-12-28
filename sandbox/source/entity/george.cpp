#include <bq.h>

#include "player.h"
#include "../quests/robot_quest.h"
#include "george.h"

constexpr size_t SHEET_SIZE = 64;

george::george(float x, float y, player* player) : m_player(player), upAnimation("george.png", 0 * SHEET_SIZE, SHEET_SIZE, 9, 10), downAnimation("george.png", 2 * SHEET_SIZE, SHEET_SIZE, 9, 10), leftAnimation("george.png", 1 * SHEET_SIZE, SHEET_SIZE, 9, 10), rightAnimation("george.png", 3 * SHEET_SIZE, SHEET_SIZE, 9, 10), m_sprite(bq::resource_holder::get().textures.get("george.png")), m_dialog({0,0}, {400,50},"Complete this quest for me: kill 30 robots",sf::Color::Cyan, sf::Color::Cyan, 15) {
	m_pos.x = x;
	m_pos.y = y;
	m_sprite.setTexture(bq::resource_holder::get().textures.get("george.png"));
	m_sprite.setTextureRect({ 0,128,64,64 });
	m_size.x = 32, m_size.y = 44;

	m_id = bq::handler::get().em()->register_id("GEORGE");
	m_dialog.setFunc([this]() -> void { this->give_quest(); });
}
void george::update() {


	upAnimation.update();
	downAnimation.update();
	leftAnimation.update();
	rightAnimation.update();

	upAnimation.get().setPosition({ m_pos.x,m_pos.y });
	downAnimation.get().setPosition({ m_pos.x,m_pos.y });
	leftAnimation.get().setPosition({ m_pos.x,m_pos.y });
	rightAnimation.get().setPosition({ m_pos.x,m_pos.y });

	

	if (bq::random::getRandom(0.f, movement_threashold) < .1f) {
		if (moves_made == 0) {
			float rng = bq::random::getRandom(0.f, 1.f);
			if (rng < 0.33) {
				movement.x = 1;
				m_sprite = rightAnimation.get();
			}
			else if( rng < 0.66) {
				movement.x = -1;
				m_sprite = leftAnimation.get();
			}
			rng = bq::random::getRandom(0.f, 1.f);
			if (rng < 0.33) {
				m_sprite = downAnimation.get();
				movement.y = 1;
			}
			else if (rng < 0.66) {
				m_sprite = upAnimation.get();
				movement.y = -1;
			}
		}
	}


	if (movement.x > 0.f) {
		m_sprite = rightAnimation.get();
	}
	else if (movement.x < 0.f) {
		m_sprite = leftAnimation.get();
	}
	if (movement.y > 0.f) {
		m_sprite = downAnimation.get();
	}
	else if (movement.y < 0.f) {
		m_sprite = upAnimation.get();
	}


	sf::FloatRect bounds = { m_pos.x + 16 + movement.x, m_pos.y + 15 + movement.y, m_size.x, m_size.y };
	bq::block_collision_effects bce = bq::handler::get().world()->get_collision_effects(bounds);
	if (!bce.m_collision) {
		
		float xabs = fabs(0.f - movement.x);
		float yabs = fabs(0.f - movement.y);
		if (xabs > 0.01f || yabs > 0.01f) {
			move(movement);
			moves_made++;
		}
		
		if (moves_made > moves_before_change) {
			moves_made = 0;
			movement = {0,0};
		}
		
	}
	else {
		moves_made = 0;
		movement = { 0,0 };
	}
	m_sprite.setPosition(m_pos);
	if (interacted) {
		m_dialog.update();
		
		m_dialog.setPos(m_pos);
	}
	if (dialog_timer.getElapsedTime().asSeconds() > 8) {
		interacted = false;
	}
	

}
void george::render(bq::window& window) {
	window.draw(m_sprite);

	if (interacted) {
		m_dialog.render(window);
	}

}
void george::handle_event(bq::event& evt) {
	m_dialog.handle_event(evt);
}
bool george::intersects(sf::FloatRect& other) {
	sf::FloatRect bounds = { m_pos.x + 16 + movement.x, m_pos.y + 15 + movement.y, m_size.x, m_size.y };
	return bounds.intersects(other);
}
void george::damage(float) {}

void george::interact() {
	dialog_timer.restart();
	interacted = true;
}
void george::give_quest() {
	if (interacted) {
		
		m_player->m_quest = new robot_quest(m_player);

		interacted = false;
	}
}