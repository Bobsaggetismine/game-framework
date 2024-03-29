#pragma once

namespace bq {
	
	class state;
	class event;
	class window;

	class state_manager {
		std::stack<std::unique_ptr<state>> m_states;
		
	public:
		state_manager(std::unique_ptr<state>);
		state_manager();
		void push(std::unique_ptr<state>,bool = true);
		void pop();
		void update();
		void render(bq::window&) const;
		void handle_events(bq::event&, bq::window&);
		size_t get_num_states();
		bq::state* get_current_state();
	};
}