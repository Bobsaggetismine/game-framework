
#include "bullet.h"



bullet::bullet(bq::v2f p, bq::v2f vel):sprite(bq::resource_holder::get().textures.get("bullet.png")), speed(vel) {
	pos = p;
}
void bullet::handleEvent(sf::Event& evt) {

}
void bullet::update() {
	move(speed);
	sprite.setPosition({pos.x,pos.y});
	
	sf::FloatRect bound = { pos.x,pos.y,size.x, size.y };
	if (bq::handler::get().m_world->get_collision_effects(bound).collides) {
		bq::handler::get().m_em->remove(shared_from_this());
	}
}

void bullet::render(sf::RenderWindow& window) {
	window.draw(sprite);
}
bool bullet::shouldCull(sf::View& view) {
	
	bq::v2f center = view.getCenter();

	bq::v2f size = view.getSize();

	sf::FloatRect viewPort = {center.x - (size.x/2), center.y - (size.y/2), size.x , size.y };

	return ! viewPort.contains({ pos.x, pos.y });

}