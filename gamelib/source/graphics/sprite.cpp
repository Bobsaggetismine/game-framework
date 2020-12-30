#include <bqpch.h>
#include <bq/graphics/sprite.h>



void bq::sprite::set_texture(const sf::Texture& texture) {
		m_sprite.setTexture(texture);
}
void bq::sprite::set_pos(float x, float y) {
	m_sprite.setPosition(x, y);
}
void bq::sprite::set_texture_rect(int x, int y, int w, int h) {
	m_sprite.setTextureRect({ x, y, w, h });
}
bq::v2f bq::sprite::get_pos() {
	return m_sprite.getPosition();
}
