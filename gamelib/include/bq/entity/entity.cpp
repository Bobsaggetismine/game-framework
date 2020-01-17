#include "entity.h"

bool bq::entity::intersects(sf::FloatRect& other)
{
	sf::FloatRect ourbound = {pos, size};
	return ourbound.intersects(other);
}
