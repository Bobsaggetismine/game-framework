#pragma once

namespace bq {
	struct v2f;
	class entity;
	namespace gui {
		class widget; 
		class Rectangle;
		class health_bar : public bq::gui::widget {

			Rectangle m_back;
			Rectangle m_front;

		public:
			health_bar();
			void render(sf::RenderWindow& renderer) override;
			void update(float);
			void handle_event(bq::event& e) override;
			void update_pos(float, float);
		};
	}
}
