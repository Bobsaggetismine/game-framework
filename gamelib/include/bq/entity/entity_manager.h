#pragma once
#include <bq/common.h>
#include <bq/entity/entity.h>
#include <bq/core/camera.h>
namespace bq {
	class entity_manager {
		std::vector<std::shared_ptr<entity>> marked_to_remove;
		std::vector<std::shared_ptr<entity>> marked_to_add;

		void remove_marked();
		void add_marked();

	public:
		std::vector<std::shared_ptr<entity>> entities;

		entity_manager();

		void update();
		void render(sf::RenderWindow&);
		void add(std::shared_ptr<entity>);
		void markAdd(std::shared_ptr<entity>);
		void remove(std::shared_ptr<entity>);
		void handleEvent(sf::Event&);
		
	};
}