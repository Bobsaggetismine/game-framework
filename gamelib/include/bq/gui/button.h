#pragma once
#include <bq/common.h>
#include <bq/gui/Widget.h>
#include <bq/resource/resource_holder.h>
#include <bq/util/vec.h>
namespace bq {
	namespace gui {
		class Button : public bq::gui::widget {

			Rectangle   m_button;
			sf::Text text;
			std::function<void(void)> m_function = []() {};
			
		public:
			Button(bq::v2f, bq::v2f,std::string, sf::Color, sf::Color);
			void setFunc(std::function<void(void)>);

			void handleEvent(sf::Event& e, sf::RenderWindow& window) override;
			void render(sf::RenderWindow& renderer) override;

		};
	}
}