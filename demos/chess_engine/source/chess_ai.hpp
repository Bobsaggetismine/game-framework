#pragma once
#include <bq.h>
#include "surge/surge.h"
#include "search.hpp"
#include "book.hpp"

class pvs_ai {

	static int constexpr DEFAULT_TURN_TIME = 5000;
	static int constexpr DEFAULT_DEPTH = 30;
	
	int m_depth;
	int m_turntime;
	bool waiting = true;

	book m_book;
	pvs_search m_search;

public:

	pvs_ai();

	void signal_stop();
	void notify_book(Move& move);
	void reset();
	void set_turntime(int ms);
	Move get_best_move(Position& p);
	
};