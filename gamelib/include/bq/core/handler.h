#pragma once
#include <bq/entity/entity_manager.h>
#include <bq/state/state_manager.h>
#include <bq/world/world.h>
#include <bq/core/camera.h>
namespace bq {
	class handler {

		handler() {};

	public:
		std::unique_ptr<bq::world> m_world;
		std::unique_ptr<bq::entity_manager> m_em;
		std::unique_ptr<bq::state_manager> m_sm;
		std::unique_ptr<bq::camera> m_cam;
		
		inline static handler& get() {
			static handler h;
			return h;
		}
	};
}
