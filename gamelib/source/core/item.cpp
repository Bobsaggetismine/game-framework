#include "bq/core/item.h"
#include "bq/core/logger.h"
bq::item::~item(){}
int bq::item::uses()
{
	return this->m_uses;
}

void bq::item::add_uses(int toAdd)
{
	this->m_uses += toAdd;
}

void bq::item::remove_uses(int toRemove)
{
	this->m_uses -= toRemove;
}

void bq::item::render(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void bq::item::update_pos(float x, float y) {
	m_sprite.setPosition(x, y);
}
