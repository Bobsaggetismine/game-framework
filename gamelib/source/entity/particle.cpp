#include "bq/entity/particle.h"
#include "bq/resource/resource_holder.h"

void bq::particle::update() {
	move(movement);

	m_sprite.setPosition(pos);

	movement.x *= 0.894;
	movement.y *= 0.894;
}

void bq::particle::handleEvent(sf::Event&)
{
}

void bq::particle::render(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

bq::particle::particle(float x, float y, float life) {
	m_sprite.setTexture(bq::resource_holder::get().textures.get("base_particle.png"));
	size = {1,1};
	pos = {x + bq::random::getRandom(-10.f,10.f),y + bq::random::getRandom(-10.f, 10.f) };
	m_life = life;
	m_life_timer.restart();
	movement = {bq::random::getRandom(-5.f,5.f),bq::random::getRandom(-5.f, 5.f) };
}
void bq::particle::damage(float f) {
	//particles dont need to worry about damage
}
bool bq::particle::shouldCull(sf::View& view) {
	return (m_life_timer.getElapsedTime().asSeconds() > m_life);
}
bool bq::particle::intersects(sf::FloatRect& other) {
	return false;
}
void bq::particle::interact() {

}