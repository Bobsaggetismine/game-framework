#pragma once
#include <bq/common.h>
#include <bq/state/state.h>
#include <bq/exception/illegal_state.h>
namespace bq {

	using state_t = std::shared_ptr<state>;

	class state_manager {
		std::stack<state_t> m_states;
		
	public:
		state_manager(state_t);
		state_manager();
		void push(state_t,bool = true);
		void pop();
		void update();
		void render(sf::RenderWindow&);
		void handleEvents(sf::Event&, sf::RenderWindow&);

		unsigned get_num_states();
		state_t get_current_state();
	};
}