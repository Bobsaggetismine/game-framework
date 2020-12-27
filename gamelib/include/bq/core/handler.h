#pragma once
#include <bq/entity/entity_manager.h>
#include <bq/state/state_manager.h>
#include <bq/world/world.h>
#include <bq/core/camera.h>
namespace bq {
	class handler {

		handler() {};
		std::unique_ptr<bq::world> m_world;
		std::unique_ptr<bq::entity_manager> m_em;
		std::unique_ptr<bq::state_manager> m_sm;
		std::unique_ptr<bq::camera> m_cam;
	public:
		
		void set_sm(std::unique_ptr<bq::state_manager> sm) {
			m_sm = std::move(sm);
		}
		void set_em(std::unique_ptr<bq::entity_manager> em) {
			m_em = std::move(em);
		}
		void set_cam(std::unique_ptr<bq::camera> cam) {
			m_cam = std::move(cam);
		}
		void set_world(std::unique_ptr<bq::world> world) {
			m_world = std::move(world);
		}
		bq::world* world() {
#ifdef DEBUG
			if (!m_world) {
				bq::logger::warn("m_world is null on access");
			}
#endif
			return m_world.get();
		}
		bq::entity_manager* em() {
#ifdef DEBUG
			if (!m_em) {
				bq::logger::warn("m_em is null on access");
			}
#endif
			return m_em.get();
		}
		bq::state_manager* sm() {
#ifdef DEBUG
			if (!m_sm) {
				bq::logger::warn("m_sm is null on access");
			}
#endif
			return m_sm.get();
		}
		bq::camera* cam() {
			return m_cam.get();
		}
		
		inline static handler& get() {
			static handler h;
			return h;
		}
	};
}
