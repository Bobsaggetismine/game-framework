#pragma once
#include <bq/common.h>
#include <bq/resource/resource_holder.h>
namespace bq {
	class animation {

		sf::Sprite sprite;
		int startingy, spritesize, numsprites;
		int index = 0;
		int frames = 0;
		int frames_to_update = 0;
	public:
		animation(std::string, int, int, int, int);
		void update();
		sf::Sprite& get();
	};
}