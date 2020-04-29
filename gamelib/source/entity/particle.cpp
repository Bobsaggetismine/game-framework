#include "bq/entity/particle.h"
#include "bq/resource/resource_holder.h"
#include <bq/core/handler.h>
void bq::particle::update() {
	move(m_movement);

	m_sprite.setPosition(m_pos);

	m_movement.x *= 0.894f;
	m_movement.y *= 0.894f;
}

void bq::particle::handle_event(sf::Event&)
{
}

void bq::particle::render(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

bq::particle::particle(float x, float y, float life) {
	m_sprite.setTexture(bq::resource_holder::get().textures.get("base_particle.png"));
	m_size = {1,1};
	m_pos = {x + bq::random::getRandom(-10.f,10.f),y + bq::random::getRandom(-10.f, 10.f) };
	m_life = life;
	m_life_timer.restart();
	m_movement = {bq::random::getRandom(-5.f,5.f),bq::random::getRandom(-5.f, 5.f) };

	m_id = 9;
	bq::handler::get().m_em->register_id("BASE_PARTICLE", m_id);
}
void bq::particle::damage(float f) {
	//particles dont need to worry about damage
}
bool bq::particle::should_cull(const sf::View& view) {
	return (m_life_timer.getElapsedTime().asSeconds() > m_life);
}
bool bq::particle::intersects(sf::FloatRect& other) {
	return false;
}
void bq::particle::interact() {

}