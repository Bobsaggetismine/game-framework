#include "bqpch.h"
#include <bq/event/event.h>
#include <bq/state/state.h>
#include <bq/exception/illegal_state.h>
#include <bq/state/state_manager.h>

bq::state_manager::state_manager(std::unique_ptr<state> initial) {
	m_states.push(std::move(initial));
}
bq::state_manager::state_manager() {}
void bq::state_manager::pop() {
#ifdef DEBUG
	if (m_states.size() == 0) {
		bq::logger::critical("popping empty state manager");
	}
#endif
	m_states.pop();
}

void bq::state_manager::push(std::unique_ptr<state> state, bool replacing) {
	if (replacing) {
		m_states.pop();
		m_states.push(std::move(state));
	}
	else {
		m_states.push(std::move(state));
	}
}

void bq::state_manager::update() {
	if (m_states.size() == 0) {
		throw bq::illegal_state("m_states empty on update");
	}
	m_states.top()->update();
}
void bq::state_manager::render(bq::window& window) const {
	if (m_states.size() == 0) {
		throw bq::illegal_state("m_states empty on render");
	}
	m_states.top()->render(window);
}
void bq::state_manager::handle_events(bq::event& evt, bq::window& window) {
	if (m_states.size() == 0) {
		throw bq::illegal_state("m_states empty on handleEvents");
	}
	m_states.top()->handleEvents(evt, window);
}

size_t bq::state_manager::get_num_states() {
	return m_states.size();
}
bq::state* bq::state_manager::get_current_state() {
	return m_states.top().get();
}