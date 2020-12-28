#pragma once


namespace bq {

	class entity;
	class quest;
	
	class entity_manager {
		std::vector<entity*> m_to_remove;
		std::vector<std::unique_ptr<bq::entity>> m_to_add;
		std::map<std::string, int> m_id_map;
		std::vector<std::unique_ptr<entity>> m_entities;
		bq::quest* m_quest = nullptr;
		
		void remove_marked();
		void add_marked();
		unsigned m_current_id = 0;

	public:
		
		entity_manager();
		void update();
		void render(sf::RenderWindow&);
		void add(std::unique_ptr<entity>);
		void remove(bq::entity*);
		void handleEvent(bq::event&);
		size_t register_id(const std::string&);
		void hook_quest(bq::quest*);
		void unhook_quest(bq::quest*);
		size_t get_id(const std::string&);
		const std::vector<std::unique_ptr<entity>>& entities() const;
		bq::entity* intersects(sf::FloatRect&, size_t, bool);
	};
}