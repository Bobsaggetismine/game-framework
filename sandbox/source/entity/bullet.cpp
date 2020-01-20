
#include "bullet.h"
#include "bq/entity/particle.h"


bullet::bullet(bq::v2f p, bq::v2f vel):sprite(bq::resource_holder::get().textures.get("bullet.png")), speed(vel), sound(bq::resource_holder::get().sounds.get("hitmarker.wav")) {
	pos = p;
	size = {3,3};
	id = 3;
}
bool bullet::intersects(sf::FloatRect&)
{
	return false;
}
void bullet::handleEvent(sf::Event& evt) {

}

//if something damages us we dont care for now (might change for potential multiplayer)
void bullet::damage(float) {}


void bullet::update() {
	move(speed);
	sprite.setPosition({pos.x,pos.y});
	
	sf::FloatRect bound = { pos.x + 16,pos.y + 16,size.x, size.y };
	if (bq::handler::get().m_world->get_collision_effects(bound).collides) {
		bq::logger::debug("bullet colides");
		m_dead = true;
	}
	
	std::shared_ptr<bq::entity> enemy_hit = bq::handler::get().m_em->intersects(bound,id,false);

	if (enemy_hit) {
		if (enemy_hit->id != 1) {
				enemy_hit->damage(m_damage);
				sound.play();
				m_dead = true;
			
		}
	}


}

void bullet::render(sf::RenderWindow& window) {
	window.draw(sprite);
}
bool bullet::shouldCull(sf::View& view) {
	if (m_dead) {
		bq::logger::debug("bullet is dead");
		for (unsigned i = 0; i < 12; ++i) {
			bq::handler::get().m_em->markAdd(std::make_shared<bq::particle>(pos.x, pos.y, 0.5f));
		}
		return true;
	}
	bq::v2f center = view.getCenter();

	bq::v2f size = view.getSize();

	sf::FloatRect viewPort = {center.x - (size.x/2), center.y - (size.y/2), size.x , size.y };

	return ! viewPort.contains({ pos.x, pos.y });

}
void bullet::interact() {}