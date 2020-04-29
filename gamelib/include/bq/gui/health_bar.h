#pragma once

#include <bq/common.h>
#include <bq/gui/Widget.h>
#include <bq/resource/resource_holder.h>
#include <bq/util/vec.h>
#include <bq/entity/entity.h>
namespace bq {
	namespace gui {
		class health_bar : public bq::gui::widget {

			Rectangle m_back;
			Rectangle m_front;

		public:
			health_bar();
			void render(sf::RenderWindow& renderer) override;
			void update(float);
			void handle_event(sf::Event& e) override;
			void update_pos(float, float);
		};
	}
}
