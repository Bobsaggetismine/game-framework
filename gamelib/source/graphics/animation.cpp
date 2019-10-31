#include <bq/graphics/animation.h>


sf::Sprite& bq::animation::get() {
	return sprite;
}
bq::animation::animation(std::string sheet, int starty, int spritewidth, int numSprites, int ftu):frames_to_update(ftu) ,startingy(starty), spritesize(spritewidth),numsprites(numSprites) {
	sprite.setTexture(bq::resource_holder::get().textures.get(sheet));
	sprite.setTextureRect(sf::IntRect(index * spritesize, startingy, spritesize, spritesize));
}
void bq::animation::update() {
	frames++;
	if (frames >= frames_to_update) {
		sprite.setTextureRect(sf::IntRect(index * spritesize, startingy, spritesize, spritesize));

		index++;
		if (index >= numsprites) index = 0;
		frames = 0;
	}
	
}