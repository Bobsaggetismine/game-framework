#pragma once
#include "bq/core/item.h"
#include <vector>
#include "SFML/Graphics.hpp"

namespace bq {
	class inventory {

		unsigned index = -1;
	public:
		std::vector<std::unique_ptr<bq::item>> m_items;
		sf::Sprite m_sprite;
		inventory();
		void cycle_forward();
		void cycle_backward();
		void add_item(std::unique_ptr<bq::item>);
		void drop_item();
		bool empty();
		//pointers returned from here do not need to be cleaned up. 
		bq::item* get_selected();
		void render(sf::RenderWindow& window);
		void update_position(float,float);
	};
}