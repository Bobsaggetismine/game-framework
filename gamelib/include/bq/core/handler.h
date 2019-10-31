#pragma once
#include <bq/entity/entity_manager.h>
#include <bq/state/state_manager.h>
#include <bq/world/world.h>
namespace bq {
	class handler {

		handler() {};

	public:
		std::shared_ptr<bq::world> m_world;
		std::shared_ptr<bq::entity_manager> m_em;
		std::shared_ptr<bq::state_manager> m_sm;
		std::shared_ptr<bq::camera> m_cam;
		inline static handler& get() {
			static handler h;
			return h;
		}
	};
}
