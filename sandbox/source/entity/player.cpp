#include "player.h"


constexpr int SHEET_SIZE = 64;
player::player() : upAnimation("player.png", 0 * SHEET_SIZE, SHEET_SIZE, 9, 10), downAnimation("player.png", 2 * SHEET_SIZE, SHEET_SIZE, 9, 10), leftAnimation("player.png", 1 * SHEET_SIZE, SHEET_SIZE, 9, 10), rightAnimation("player.png", 3 * SHEET_SIZE, SHEET_SIZE, 9, 10), curSprite(bq::resource_holder::get().textures.get("player.png")){
	id = 1;
	pos.x = 100, pos.y = 100;
	size.x = 32, size.y = 44;
	curSprite.setTextureRect(sf::IntRect(0, 64 * 2, 64, 64));
	curSprite.setPosition({ pos.x,pos.y });
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
}
void player::input() {
	bq::v2f movement = { 0, 0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		curSprite = upAnimation.get();
		movement.y = -1;
		interactPoint = { pos.x + 15 + (size.x / 2), pos.y };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		curSprite = downAnimation.get();
		movement.y = 1;
		interactPoint = { pos.x + 15 + (size.x / 2), pos.y + 15 + size.y + 10 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		curSprite = leftAnimation.get();
		movement.x = -1;
		interactPoint = { pos.x + 5, pos.y + 15 + size.y / 2 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		curSprite = rightAnimation.get();
		movement.x = 1;
		interactPoint = { pos.x + 5 + size.x + 15, pos.y + 15 + size.y / 2 };
	}


	sf::FloatRect bounds = { pos.x + 16 + movement.x, pos.y + 15 + movement.y, size.x, size.y };
	bq::block_collision_effects bce = bq::handler::get().m_world->get_collision_effects(bounds);
	if (!bce.collides) {
		move(movement);
	}
	hp -= bce.damage;
	if (hp < 1) {
		bq::v2f pos = { 1920 / 2,1080 / 2 };
		bq::v2f rect = { 200,100 };
		bq::handler::get().m_sm->push(std::make_shared<menu_state>(pos, rect), true);
		return;
	}
}


void player::handleEvent(sf::Event& evt) {
	if (evt.type == sf::Event::KeyPressed) {
		if (evt.key.code == sf::Keyboard::Space) {
			bq::handler::get().m_world->interact(interactPoint.x, interactPoint.y);
		}
		if (evt.key.code == sf::Keyboard::Up) {
			bq::v2f v{ 0.f,-3.f };
			bq::v2f p{ pos.x + 16,pos.y };
			bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
		}
		else if (evt.key.code == sf::Keyboard::Down) {
			bq::v2f v{ 0.f,3.f };
			bq::v2f p{ pos.x + 16,pos.y + 36 };

			bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
		}
		else if (evt.key.code == sf::Keyboard::Left) {
			bq::v2f v{ -3.f,0.f };
			bq::v2f p{ pos.x,pos.y + 16 };

			bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
		}
		else if (evt.key.code == sf::Keyboard::Right) {
			bq::v2f v{ 3.f,0.f };
			bq::v2f p{ pos.x + 32,pos.y + 16 };
			bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
		}
	}
}
