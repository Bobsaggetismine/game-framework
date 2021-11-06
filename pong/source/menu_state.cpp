#include <bq.h>
#include "menu_state.h"
#include "game_state.h"

menu_state::menu_state(bq::v2f pos,bq::v2f size) :m_start_game(pos,size,"Start Game", sf::Color::Black, sf::Color::Red,20) {
	std::function<void(void)> changeState = std::bind(&menu_state::startGame,this);
	m_start_game.setFunc(changeState);
}
void menu_state::startGame() {
#ifdef _DEBUG
	if (!bq::handler::get().sm()) {
		bq::logger::critical("STATE MANAGER IS NULL - menu_state::startGame()");
		throw std::exception("");
	}
#endif
	bq::handler::get().sm()->push(std::make_unique<game_state>());
}

void menu_state::handleEvents(bq::event& evt, bq::window& window) {
	m_start_game.handle_event(evt);
}
void menu_state::render(bq::window& window) {
	sf::View view;
	view.reset(sf::FloatRect(0, 0, GAME_WIDTH, GAME_HEIGHT));
	window.set_view(view);
	m_start_game.render(window);
}
void menu_state::update() {

}    
