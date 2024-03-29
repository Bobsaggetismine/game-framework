#pragma once


namespace bq {
	
	class animation {

		bq::sprite m_sprite;
		size_t startingy, spritesize, numsprites;
		size_t index = 0;
		size_t frames = 0;
		size_t frames_to_update = 0;
	public:
		animation(std::string, size_t, size_t, size_t, size_t);
		void update();
		bq::sprite& get();
	};
}