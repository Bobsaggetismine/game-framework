#include "machine_gun.h"


void machine_gun::action(std::optional<sf::Event> evt) {
	if (evt.has_value()) {

		if (m_timer.getElapsedTime().asSeconds() > 0.1f) {
			if (evt.value().key.code == sf::Keyboard::Up) {
				bq::v2f v{ 0.f,-3.f };
				bq::v2f p{ m_target.pos.x + 16,m_target.pos.y + 15 };
				bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
				m_timer.restart();
			}
			else if (evt.value().key.code == sf::Keyboard::Down) {
				bq::v2f v{ 0.f,3.f };
				bq::v2f p{ m_target.pos.x + 16,m_target.pos.y + 15 };

				bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
				m_timer.restart();
			}
			else if (evt.value().key.code == sf::Keyboard::Left) {
				bq::v2f v{ -3.f,0.f };
				bq::v2f p{ m_target.pos.x + 20,m_target.pos.y + 15 };

				bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
				m_timer.restart();
			}
			else if (evt.value().key.code == sf::Keyboard::Right) {
				bq::v2f v{ 3.f,0.f };
				bq::v2f p{ m_target.pos.x + 16,m_target.pos.y + 15 };
				bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
				m_timer.restart();
			}
			sound.play();
		}
	}
	else {
		bq::logger::info("Event not passed to gun");
	}
}
machine_gun::machine_gun(bq::entity& target) : m_target(target), sound(bq::resource_holder::get().sounds.get("gunshot.wav"))
{
	m_sprite.setTexture(bq::resource_holder::get().textures.get("mg.png"));
	m_timer.restart();
}