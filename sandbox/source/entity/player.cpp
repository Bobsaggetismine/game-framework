#include <bq.h>

#include "../world/pongworld.h"
#include "../States/menu_state.h"
#include "bullet.h"
#include "../items/machine_gun.h"
#include "../items/gun.h"
#include "player.h"

constexpr size_t SHEET_SIZE = 64;
player::player() : upAnimation("player.png", 0 * SHEET_SIZE, SHEET_SIZE, 9, 10), downAnimation("player.png", 2 * SHEET_SIZE, SHEET_SIZE, 9, 10), leftAnimation("player.png", 1 * SHEET_SIZE, SHEET_SIZE, 9, 10), rightAnimation("player.png", 3 * SHEET_SIZE, SHEET_SIZE, 9, 10), curSprite(bq::resource_holder::get().textures.get("player.png")) {
	m_pos.x = 100, m_pos.y = 100;
	m_size.x = 32, m_size.y = 44;
	curSprite.setTextureRect(sf::IntRect(0, 64 * 2, 64, 64));
	curSprite.setPosition({ m_pos.x,m_pos.y });
	m_inventory.add_item(std::make_unique<machine_gun>(*this));
	m_inventory.add_item(std::make_unique<gun>(*this));
	m_id = bq::handler::get().em()->register_id("PLAYER");
}

player::~player()
{
	if (m_quest != nullptr) {

		bq::handler::get().em()->unhook_quest(m_quest);

		delete m_quest;
	}
}

void player::update() {
	
	upAnimation.update();
	downAnimation.update();
	leftAnimation.update();
	rightAnimation.update();

	upAnimation.get().setPosition({ m_pos.x,m_pos.y });
	downAnimation.get().setPosition({ m_pos.x,m_pos.y });
	leftAnimation.get().setPosition({ m_pos.x,m_pos.y });
	rightAnimation.get().setPosition({ m_pos.x,m_pos.y });

	input();
	if (m_quest != nullptr) {
		m_quest->update();
		
	}
}


void player::render(sf::RenderWindow& window) {
	window.draw(curSprite);
	m_inventory.render(window);
	hb.render(window);
	if (m_quest != nullptr) {
		m_quest->render(window);
	}
}
void player::input() {


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		bq::v2f mouse = { float(sf::Mouse::getPosition().x) , float(sf::Mouse::getPosition().y) };
		if (!m_inventory.empty()) m_inventory.get_selected()->action(std::make_optional<sf::Keyboard::Key>(), std::make_optional<bq::v2f>(m_pos));
	}

	bq::v2f movement = { 0, 0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		curSprite = upAnimation.get();
		movement.y = -1;
		interactPoint = { m_pos.x + 15 + (m_size.x / 2), m_pos.y };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		curSprite = downAnimation.get();
		movement.y = 1;
		interactPoint = { m_pos.x + 15 + (m_size.x / 2), m_pos.y + 15 + m_size.y + 10 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		curSprite = leftAnimation.get();
		movement.x = -1;
		interactPoint = { m_pos.x + 5, m_pos.y + 15 + m_size.y / 2 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		curSprite = rightAnimation.get();
		movement.x = 1;
		interactPoint = { m_pos.x + 5 + m_size.x + 15, m_pos.y + 15 + m_size.y / 2 };
	}
	
	sf::FloatRect bounds = { m_pos.x + 16 + movement.x, m_pos.y + 15 + movement.y, m_size.x, m_size.y };
	bq::block_collision_effects bce = bq::handler::get().world()->get_collision_effects(bounds);
	if (!bce.m_collision) {
		move(movement);
	}
	damage((float)bce.m_damage);
	m_inventory.update_position(m_pos.x - 120, m_pos.y +500);
	hb.update_pos(m_pos.x - 50, m_pos.y - 500);
	if (hp < 1) {
		bq::v2f pos = { GAME_WIDTH / 2 - 100 ,GAME_HEIGHT / 2 - 50 };
		bq::v2f rect = { 200,100 };

		bq::handler::get().cam()->reset();

		bq::handler::get().sm()->push(std::make_unique<menu_state>(pos, rect), true);
		return;
	}
}


void player::handle_event(bq::event& evt) {
	if (evt.type == bq::event_type::KEYPRESSED) {
		if (evt.keycode == bq::keyboard::keycode::SPACE) {
			bq::handler::get().world()->interact(interactPoint.x, interactPoint.y);

			sf::FloatRect slightly_larger_bounds = { m_pos.x , m_pos.y , m_size.x + 30, m_size.y + 32 };
			bq::entity* e =  bq::handler::get().em()->intersects(slightly_larger_bounds, m_id, false);
			if (e) e->interact();
		}
		if (evt.keycode == bq::keyboard::keycode::TAB) {
			m_inventory.cycle_forward();
		}
	}
}
void player::damage(float dmg) {
	hp -= dmg;
	hb.update(hp);
}
void player::interact() {

}