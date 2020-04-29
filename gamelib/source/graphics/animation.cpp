#include <bq/graphics/animation.h>

sf::Sprite& bq::animation::get() {
	return m_sprite;
}
bq::animation::animation(std::string sheet, int starty, int spritewidth, int numSprites, int ftu):frames_to_update(ftu) ,startingy(starty), spritesize(spritewidth),numsprites(numSprites) {
	m_sprite.setTexture(bq::resource_holder::get().textures.get(sheet));
	m_sprite.setTextureRect(sf::IntRect(index * spritesize, startingy, spritesize, spritesize));
}
void bq::animation::update() {
	frames++;
	if (frames >= frames_to_update) {
		m_sprite.setTextureRect(sf::IntRect(index * spritesize, startingy, spritesize, spritesize));
		index++;
		if (index >= numsprites) index = 0;
		frames = 0;
	}
}