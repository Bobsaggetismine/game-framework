#include "menu_state.h"
#include "game_state.h"
menu_state::menu_state(bq::v2f pos,bq::v2f size) :m_start_game(pos,size,"Start Game", sf::Color::Black, sf::Color::Red) {
	std::function<void(void)> changeState = std::bind(&menu_state::startGame,this);
	m_start_game.setFunc(changeState);
}
void menu_state::startGame() {
#ifdef _DEBUG
	if (!bq::handler::get().m_sm) {
		bq::logger::critical("STATE MANAGER IS NULL - menu_state::startGame()");
		throw std::exception("");
	}
#endif
	bq::handler::get().m_sm->push(std::make_shared<game_state>());
}

void menu_state::handleEvents(sf::Event& evt, sf::RenderWindow& window) {
	m_start_game.handleEvent(evt, window);
}
void menu_state::render(sf::RenderWindow& window) {
	m_start_game.render(window);
}
void menu_state::update() {}
