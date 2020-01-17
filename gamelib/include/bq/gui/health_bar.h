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
			bq::entity& target;

		public:
			health_bar(bq::entity&);
			void render(sf::RenderWindow& renderer) override;
			void update(float);
			void handleEvent(sf::Event& e, sf::RenderWindow& window) override;
			void update_pos(float, float);
		};
	}
}
