#pragma once



namespace bq {

	class item;

	class inventory {

		size_t m_index = -1;
		std::vector<std::unique_ptr<bq::item>> m_items;
		sf::Sprite m_sprite;
	public:
		
		inventory();

		void cycle_forward();
		void cycle_backward();
		void add_item(std::unique_ptr<bq::item>);
		void drop_item();
		bool empty() const;
		void render(sf::RenderWindow& window) const;
		void update_position(float,float);
		bq::item* get_selected() const;
	};
}