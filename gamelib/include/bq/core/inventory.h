#pragma once
#include "bq/core/item.h"
#include <vector>
#include "SFML/Graphics.hpp"

namespace bq {
	class inventory {

		unsigned m_index = -1;
		std::vector<std::unique_ptr<bq::item>> m_items;
		sf::Sprite m_sprite;
	public:
		
		inventory();
		void cycle_forward();
		void cycle_backward();
		void add_item(std::unique_ptr<bq::item>);
		void drop_item();
		bool empty();
		void render(sf::RenderWindow& window);
		void update_position(float,float);
		bq::item* get_selected();
	};
}