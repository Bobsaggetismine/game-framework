#include "bq/entity/entity.h"

bool bq::entity::intersects(sf::FloatRect& other)
{
	sf::FloatRect ourbound = {pos, size};
	return ourbound.intersects(other);
}

//buffs are optional on entities considering many things will be entities (bullets, ect). if you want to use buffs, overload these two functions and do what you want with them. 
void bq::entity::buff(bq::buff) {}
void bq::entity::unbuff() {}