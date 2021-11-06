#pragma once
#include <bq/gui/Widget.h>


namespace bq {
	struct v2f;
	class window;
	namespace gui {
		class Button : public bq::gui::widget {

			Rectangle   m_button;
			sf::Text m_text;
			std::function<void(void)> m_function = [](){};
		public:
			Button(bq::v2f, bq::v2f,std::string, sf::Color, sf::Color, unsigned size_t);
			void setFunc(std::function<void(void)>);

			void handle_event(bq::event& e) override;
			void render(bq::window& renderer) override;
			void update();
			void setPos(bq::v2f);

		};
	}
}