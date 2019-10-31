#include <bq/state/state_manager.h>

bq::state_manager::state_manager(bq::state_t initial) {
	m_states.push(initial);
}
bq::state_manager::state_manager() {}
void bq::state_manager::pop() {
	m_states.pop();
}

void bq::state_manager::push(bq::state_t state, bool replacing) {
	if (replacing) {
		m_states.pop();
		m_states.push(state);
	}
	else {
		m_states.push(state);
	}
}

void bq::state_manager::update() {
	if (m_states.size() == 0) {
		throw bq::illegal_state("m_states empty on update");
	}
	m_states.top()->update();
}
void bq::state_manager::render(sf::RenderWindow& window) {
	if (m_states.size() == 0) {
		throw bq::illegal_state("m_states empty on render");
	}
	m_states.top()->render(window);
}
void bq::state_manager::handleEvents(sf::Event& evt, sf::RenderWindow& window) {
	if (m_states.size() == 0) {
		throw bq::illegal_state("m_states empty on handleEvents");
	}
	m_states.top()->handleEvents(evt, window);
}

unsigned bq::state_manager::get_num_states() {
	return m_states.size();
}
std::shared_ptr<bq::state> bq::state_manager::get_current_state() {
	return m_states.top();
}