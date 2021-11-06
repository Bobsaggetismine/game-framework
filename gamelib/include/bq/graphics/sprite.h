#pragma once



namespace bq {

	class sprite {
		sf::Sprite m_sprite;
		friend class window;
	public:
		void set_texture(const sf::Texture& texture);
		void set_pos(float x, float y);
		void set_texture_rect(int x, int y, int w, int h);
		bq::v2f get_pos();
	};
}