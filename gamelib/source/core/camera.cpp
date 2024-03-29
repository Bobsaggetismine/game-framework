#include "bqpch.h"
#include <bq/entity/entity.h>
#include <bq/entity/entity_manager.h>
#include <bq/state/state_manager.h>
#include <bq/exception/illegal_state.h>
#include <bq/graphics/window.h>
#include <bq/core/camera.h>
#include <bq/state/state.h>
#include <bq/world/world.h>
#include <bq/core/handler.h>
void bq::camera::render(bq::window& window) const {
	window.set_view(m_view);
}

void bq::camera::update() {
	m_view.setCenter( m_target->pos() );
}

bq::camera::camera(bq::entity* e): m_target(e) {
	m_view.setSize(INTL_WIDTH, INTL_HEIGHT);
}
const sf::View& bq::camera::view() const
{
	return m_view;
}
void bq::camera::reset() {
	m_view.setCenter({ INTL_WIDTH / 2,INTL_HEIGHT / 2 });
}
