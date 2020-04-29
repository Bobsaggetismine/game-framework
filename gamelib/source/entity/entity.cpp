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

bq::v2f& bq::entity::pos()
{
	return m_pos;
}
bq::v2f& bq::entity::size()
{
	return m_size;
}
const int bq::entity::id()
{
	return m_id;
}
void bq::entity::buff(bq::buff){}
void bq::entity::unbuff(){}
bool bq::entity::should_cull(const sf::View&)
{
	return false;
}
bq::entity::~entity() {}
