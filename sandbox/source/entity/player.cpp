#include "player.h"


constexpr int SHEET_SIZE = 64;
player::player() : upAnimation("player.png", 0 * SHEET_SIZE, SHEET_SIZE, 9, 10), downAnimation("player.png", 2 * SHEET_SIZE, SHEET_SIZE, 9, 10), leftAnimation("player.png", 1 * SHEET_SIZE, SHEET_SIZE, 9, 10), rightAnimation("player.png", 3 * SHEET_SIZE, SHEET_SIZE, 9, 10), curSprite(bq::resource_holder::get().textures.get("player.png")),hb(*this) {
	id = 1;
	pos.x = 100, pos.y = 100;
	size.x = 32, size.y = 44;
	curSprite.setTextureRect(sf::IntRect(0, 64 * 2, 64, 64));
	curSprite.setPosition({ pos.x,pos.y });
	m_inventory.add_item(std::make_unique<machine_gun>(*this));
	m_inventory.add_item(std::make_unique<gun>(*this));
}

void player::update() {
	
	upAnimation.update();
	downAnimation.update();
	leftAnimation.update();
	rightAnimation.update();

	upAnimation.get().setPosition({ pos.x,pos.y });
	downAnimation.get().setPosition({ pos.x,pos.y });
	leftAnimation.get().setPosition({ pos.x,pos.y });
	rightAnimation.get().setPosition({ pos.x,pos.y });

	input();
}


void player::render(sf::RenderWindow& window) {
	window.draw(curSprite);
	m_inventory.render(window);
	hb.render(window);
}
void player::input() {


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		bq::v2f mouse = { float(sf::Mouse::getPosition().x) , float(sf::Mouse::getPosition().y) };
		if (!m_inventory.empty()) m_inventory.get_selected()->action(std::make_optional<sf::Keyboard::Key>(), std::make_optional<bq::v2f>(pos));
	}

	bq::v2f movement = { 0, 0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		curSprite = upAnimation.get();
		movement.y = -1;
		interactPoint = { pos.x + 15 + (size.x / 2), pos.y };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		curSprite = downAnimation.get();
		movement.y = 1;
		interactPoint = { pos.x + 15 + (size.x / 2), pos.y + 15 + size.y + 10 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		curSprite = leftAnimation.get();
		movement.x = -1;
		interactPoint = { pos.x + 5, pos.y + 15 + size.y / 2 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		curSprite = rightAnimation.get();
		movement.x = 1;
		interactPoint = { pos.x + 5 + size.x + 15, pos.y + 15 + size.y / 2 };
	}
	
	sf::FloatRect bounds = { pos.x + 16 + movement.x, pos.y + 15 + movement.y, size.x, size.y };
	bq::block_collision_effects bce = bq::handler::get().m_world->get_collision_effects(bounds);
	if (!bce.collides) {
		move(movement);
	}
	damage((float)bce.damage);
	m_inventory.update_position(pos.x - 120, pos.y +500);
	hb.update_pos(pos.x - 50, pos.y - 500);
	if (hp < 1) {
		bq::v2f pos = { 1920 / 2 - 100 ,1080 / 2 - 50 };
		bq::v2f rect = { 200,100 };

		bq::handler::get().m_cam->reset();

		bq::handler::get().m_sm->push(std::make_shared<menu_state>(pos, rect), true);
		return;
	}
}


void player::handleEvent(sf::Event& evt) {
	if (evt.type == sf::Event::KeyPressed) {
		if (evt.key.code == sf::Keyboard::Space) {
			bq::handler::get().m_world->interact(interactPoint.x, interactPoint.y);

			sf::FloatRect slightly_larger_bounds = { pos.x , pos.y , size.x + 30, size.y + 32 };

			std::shared_ptr<bq::entity> e =  bq::handler::get().m_em->intersects(slightly_larger_bounds, id, false);
			if (e) e->interact();

		}
		
		if (evt.key.code == sf::Keyboard::LShift) {
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