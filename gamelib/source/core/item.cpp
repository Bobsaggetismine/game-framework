#include "bqpch.h"
#include <bq/graphics/window.h>
#include "bq/core/item.h"
bq::item::~item(){}
unsigned bq::item::uses() const
{
	return this->m_uses;
}

void bq::item::add_uses(unsigned toAdd)
{
	this->m_uses += toAdd;
}

void bq::item::remove_uses(unsigned toRemove)
{
	this->m_uses -= toRemove;
}

void bq::item::render(bq::window& window) {
	window.draw(m_sprite);
}

void bq::item::update_pos(float x, float y) {
	m_sprite.setPosition(x, y);
}
