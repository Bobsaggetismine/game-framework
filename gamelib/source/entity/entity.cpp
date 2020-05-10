#include "bqpch.h"


#include <bq/core/buff.h>
#include "bq/entity/entity.h"

void bq::entity::move(bq::v2f& other)
{
	m_pos += other;
}

bool bq::entity::intersects(sf::FloatRect& other)
{
	sf::FloatRect ourbound = {m_pos, m_size};
	return ourbound.intersects(other);
}

const bq::v2f& bq::entity::pos() const
{
	return m_pos;
}
const bq::v2f& bq::entity::size() const
{
	return m_size;
}
const size_t& bq::entity::id() const
{
	return m_id;
}
void bq::entity::buff(bq::buff){}
void bq::entity::unbuff(){}
bool bq::entity::should_cull(const sf::View&) const
{
	return false;
}
bq::entity::~entity() {}
