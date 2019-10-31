#include <bq/gui/button.h>

void bq::gui::Button::handleEvent(sf::Event& e, sf::RenderWindow& window) {
	auto pos = sf::Mouse::getPosition(window);

	switch (e.type) {
	case sf::Event::MouseButtonPressed:
		switch (e.mouseButton.button) {
		case sf::Mouse::Left:
			if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
#ifdef _DEBUG
				bq::logger::info("Button pressed");
#endif
				m_function();
			}

		default:
			break;
		}

	default:
		break;
	}
}

void bq::gui::Button::render(sf::RenderWindow& window) {
	window.draw(m_button);
	window.draw(text);
}
void bq::gui::Button::setFunc(std::function<void(void)>func)
{
	m_function = func;
}

bq::gui::Button::Button(bq::v2f pos, bq::v2f size,std::string label, sf::Color outlineColor, sf::Color fillColor) {

	m_button.setOutlineThickness(1);
	m_button.setOutlineColor(outlineColor);
	m_button.setFillColor(fillColor);
	m_button.setSize(size);
	m_button.setPosition(pos);
	
	
	text.setCharacterSize(20);
	text.setOutlineColor(sf::Color::White);
	text.setFillColor(sf::Color::White);
	text.setFont(bq::resource_holder::get().fonts.get("arial.ttf"));

	text.setPosition(pos);


	text.move(m_button.getGlobalBounds().width / 4.f,m_button.getGlobalBounds().height / 4.f);
	text.setString(label);
}
