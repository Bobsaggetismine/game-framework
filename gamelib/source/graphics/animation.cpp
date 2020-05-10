#include "bqpch.h"
#include <bq/resource/resource_holder.h>
#include <bq/graphics/animation.h>

sf::Sprite& bq::animation::get() {
	return m_sprite;
}
bq::animation::animation(std::string sheet, size_t starty, size_t spritewidth, size_t numSprites, size_t ftu): frames_to_update(ftu) ,startingy(starty), spritesize(spritewidth),numsprites(numSprites) {
	m_sprite.setTexture(bq::resource_holder::get().textures.get(sheet));
	m_sprite.setTextureRect(sf::IntRect((int)index * (int)spritesize, (int)startingy, (int)spritesize, (int)spritesize));
}
void bq::animation::update() {
	frames++;
	if (frames >= frames_to_update) {
		m_sprite.setTextureRect(sf::IntRect(static_cast<int>(index) * static_cast<int>(spritesize), static_cast<int>(startingy), static_cast<int>(spritesize), static_cast<int>(spritesize)));
		index++;
		if (index >= numsprites) index = 0;
		frames = 0;
	}
}