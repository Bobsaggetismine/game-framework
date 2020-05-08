#pragma once
#include <bq/common.h>
#include <bq/state/state.h>
#include <bq/exception/illegal_state.h>
namespace bq {

	class state_manager {
		std::stack<std::unique_ptr<state>> m_states;
		
	public:
		state_manager(std::unique_ptr<state>);
		state_manager();
		void push(std::unique_ptr<state>,bool = true);
		void pop();
		void update();
		void render(sf::RenderWindow&) const;
		void handle_events(sf::Event&, sf::RenderWindow&);

		unsigned get_num_states();
		bq::state* get_current_state();
	};
}