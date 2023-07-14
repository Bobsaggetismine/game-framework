#pragma once
#include "surge/surge.h"
#include "search.h"
#include "book.h"



struct pvs_ai {

	const int m_depth;
	int m_turntime;
	
	pvs_search m_search;
	bool waiting = true;

	pvs_ai(int depth, int sel_depth, int turntime): m_turntime(turntime), m_depth(depth), m_search(sel_depth) {}

	void signal_stop() noexcept {
		m_search.signal_stop();
		waiting=false;
	}

	Move get_best_move(Position& p) {

		if (p.turn() == WHITE) {
			Move bookMove = book::get_book_move<WHITE>(p);
			if (bookMove.str() != "a1a1") {
#if ANALYTICS
				bq::logger::info("------------------------------------------");
				bq::logger::info("Book selection - " + bookMove.str_d());
				bq::logger::info("------------------------------------------");
#endif
				return bookMove;
			}
		}
		else {
			Move bookMove = book::get_book_move<BLACK>(p);
			if (bookMove.str() != "a1a1") {
#if ANALYTICS
				bq::logger::info("------------------------------------------");
				bq::logger::info("Book selection - " + bookMove.str_d());
				bq::logger::info("------------------------------------------");
#endif
				return bookMove;
			}
		}

		if (p.turn() == WHITE) {
			waiting = true;
			call_after( std::bind(&pvs_ai::signal_stop,this), m_turntime);
			Move move = m_search.initiate_iterative_search<WHITE>(p, m_depth);

			while(waiting) {
				std::cout << "waiting" << std::endl;
			}

			return move;
		}
		else {
			waiting = true;
			call_after( std::bind(&pvs_ai::signal_stop,this), m_turntime);
			Move move = m_search.initiate_iterative_search<BLACK>(p, m_depth);

			while(waiting){
				std::cout << "waiting" << std::endl;
			}

			return move;
		}
	}
};