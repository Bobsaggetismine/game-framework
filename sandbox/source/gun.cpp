#include "gun.h"



gun::gun(bq::entity& target): m_target(target), sound(bq::resource_holder::get().sounds.get("gunshot.wav"))
{
	m_sprite.setTexture(bq::resource_holder::get().textures.get("handgun.png"));
	m_timer.restart();
	sound.setVolume(0.5);
	
}
void gun::action(std::optional<sf::Keyboard::Key> key)
{
	if (key) {
		if (m_timer.getElapsedTime().asSeconds() > m_cooldown) {
			if (key.value() == sf::Keyboard::Up) {
				bq::v2f v{ 0.f,-3.f };
				bq::v2f p{ m_target.pos.x + 16,m_target.pos.y + 15 };
				bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
				m_timer.restart();
			}
			else if (key.value() == sf::Keyboard::Down) {
				bq::v2f v{ 0.f,3.f };
				bq::v2f p{ m_target.pos.x + 16,m_target.pos.y + 15 };

				bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
				m_timer.restart();
			}
			else if (key.value() == sf::Keyboard::Left) {
				bq::v2f v{ -3.f,0.f };
				bq::v2f p{ m_target.pos.x + 20,m_target.pos.y + 15 };

				bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
				m_timer.restart();
			}
			else if (key.value() == sf::Keyboard::Right) {
				bq::v2f v{ 3.f,0.f };
				bq::v2f p{ m_target.pos.x + 16,m_target.pos.y + 15 };
				bq::handler::get().m_em->markAdd(std::make_shared<bullet>(p, v));
				m_timer.restart();
			}
			sound.play();
		}
	}
	else {
		bq::logger::debug("no key passed to ");
	}
	

}