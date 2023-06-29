#include <bq.h>
#include "../entity/bullet.h"
#include "machine_gun.h"


void machine_gun::action(std::optional<sf::Keyboard::Key> key, std::optional<bq::v2f> pos) {
	if (pos) {
		if (m_timer.getElapsedTime().asSeconds() > m_cooldown) {
			bq::v2f mouse = { float(sf::Mouse::getPosition().x) , float(sf::Mouse::getPosition().y) };
			bq::v2f origin = { float(GAME_WIDTH / 2.f) + 32.f, float(GAME_HEIGHT/ 2.f) + 32.f };
			bq::v2f movement_vector = { mouse.x - origin.x , mouse.y - origin.y };
			movement_vector.normalize();
			movement_vector.x *= 3;
			movement_vector.y *= 3;
			bq::v2f r = { pos.value().x + 16, pos.value().y + 16 };
			bq::handler::get().em()->add(std::make_unique<bullet>(r, movement_vector));
			sound.play();
			m_timer.restart();
		}
	}
}
machine_gun::machine_gun(bq::entity& target) : m_target(target), sound(bq::resource_holder::get().sounds.get("gunshot.wav"))
{
	m_sprite.set_texture(bq::resource_holder::get().textures.get("mg.png"));
	sound.setVolume(0.5);
	m_timer.restart();
}

machine_gun::~machine_gun()
{
	sound.resetBuffer();
}
