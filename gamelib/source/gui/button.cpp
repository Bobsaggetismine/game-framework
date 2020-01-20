#include <bq/gui/button.h>

void bq::gui::Button::handleEvent(sf::Event& e, sf::RenderWindow& window) {
	auto pos = sf::Mouse::getPosition(window);
	
	switch (e.type) {
	case sf::Event::MouseButtonPressed:
		switch (e.mouseButton.button) {
		case sf::Mouse::Left:
			if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
				bq::logger::debug("Button pressed");
				m_function();
			}

		default:
			break;
		}

	default:
		break;
	}
}

void bq::gui::Button::render(sf::RenderWindow& window)
{
	auto pos = sf::Mouse::getPosition(window);
	if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
		m_button.setFillColor(sf::Color::Magenta);
	}
	else {
		m_button.setFillColor(sf::Color::Red);
	}


	window.draw(m_button);
	window.draw(m_text);
}

void bq::gui::Button::update()
{
}
void bq::gui::Button::setFunc(std::function<void(void)>func)
{
	m_function = func;
}

bq::gui::Button::Button(bq::v2f pos, bq::v2f size,std::string label, sf::Color outlineColor, sf::Color fillColor, int textSize) {

	m_button.setOutlineThickness(1);
	m_button.setOutlineColor(outlineColor);
	m_button.setFillColor(fillColor);
	m_button.setSize(size);
	m_button.setPosition(pos);
	
	
	m_text.setCharacterSize(20);
	m_text.setOutlineColor(sf::Color::White);
	m_text.setFillColor(sf::Color::White);
	m_text.setFont(bq::resource_holder::get().fonts.get("arial.ttf"));
	m_text.setCharacterSize(textSize);

	m_text.setPosition(pos);


	m_text.move(m_button.getGlobalBounds().width / 4.f,m_button.getGlobalBounds().height / 4.f);
	m_text.setString(label);
}
void bq::gui::Button::setPos(bq::v2f v) {
	m_text.setPosition({0,0});
	m_button.setPosition(v);

	m_text.setPosition({v.x + m_button.getSize().x / 4 , v.y + m_button.getSize().y / 4 });

}