#include "bqpch.h"
#include "bq/world/block.h"

size_t bq::block::damage() const
{
	return m_damage;
}

bool bq::block::solid() const
{
	return m_solid;
}

bq::v2f bq::block::pos() const
{
	return m_pos;
}

bq::v2f bq::block::size() const
{
	return m_size;
}
