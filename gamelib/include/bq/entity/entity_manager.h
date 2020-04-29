#pragma once
#include <bq/common.h>
#include <bq/entity/entity.h>
#include <bq/core/camera.h>
#include <bq/quest/quest.h>
namespace bq {
	class entity_manager {
		std::vector<entity*> m_to_remove;
		std::vector<std::unique_ptr<bq::entity>> m_to_add;
		std::map<std::string, int> m_id_map;
		std::vector<std::unique_ptr<entity>> m_entities;
		bq::quest* m_quest = nullptr;
		
		void remove_marked();
		void add_marked();

	public:
		
		entity_manager();
		void update();
		void render(sf::RenderWindow&);
		void add(std::unique_ptr<entity>);
		void remove(bq::entity*);
		void handleEvent(sf::Event&);
		void register_id(std::string, int);
		void hook_quest(bq::quest*);
		void unhook_quest(bq::quest*);
		int  get_id(std::string);
		const std::vector<std::unique_ptr<entity>>& entities();
		bq::entity* intersects(sf::FloatRect&, int, bool);
	};
}