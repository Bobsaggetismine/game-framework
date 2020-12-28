
#include <bq.h>
#include "bullet.h"



bullet::bullet(bq::v2f p, bq::v2f vel):sprite(bq::resource_holder::get().textures.get("bullet.png")), speed(vel), sound(bq::resource_holder::get().sounds.get("hitmarker.wav")) {
	m_pos = p;
	m_size = {3,3};
	m_id = bq::handler::get().em()->register_id("BULLET");
}
bullet::~bullet()
{
	sound.resetBuffer();
}
bool bullet::intersects(sf::FloatRect&)
{
	return false;
}
void bullet::handle_event(bq::event& evt) {

}

//if something damages us we dont care for now (might change for potential multiplayer)
void bullet::damage(float) {}


void bullet::update() {
	move(speed);
	sprite.setPosition({m_pos.x,m_pos.y});
	
	sf::FloatRect bound = { m_pos.x + 16,m_pos.y + 16,m_size.x, m_size.y };
	if (bq::handler::get().world()->get_collision_effects(bound).m_collision) {
		m_dead = true;
	}
	
	bq::entity* enemy_hit = bq::handler::get().em()->intersects(bound,m_id,false);

	if (enemy_hit) {
		if (enemy_hit->id() != bq::handler::get().em()->get_id("PLAYER")) {
				enemy_hit->damage((float)m_damage);
				sound.play();
				m_dead = true;
		}
	}


}

void bullet::render(bq::window& window) {
	window.draw(sprite);
}
bool bullet::should_cull(const sf::View& view) const {
	if (m_dead) {
		for (unsigned i = 0; i < 12; ++i) {
			bq::handler::get().em()->add(std::make_unique<bq::particle>(m_pos.x, m_pos.y, 0.5f));
		}
		return true;
	}
	bq::v2f center = view.getCenter();
	bq::v2f size = view.getSize();
	sf::FloatRect viewPort = {center.x - (size.x/2), center.y - (size.y/2), size.x , size.y };
	return ! viewPort.contains({ m_pos.x, m_pos.y });
}
void bullet::interact() {}