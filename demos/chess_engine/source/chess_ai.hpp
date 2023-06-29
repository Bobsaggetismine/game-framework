#pragma once
#include "surge/surge.h"
#include "search.h"
#include "book.h"


struct chess_ai {

	const int m_depth,m_sel_depth;
	
	search m_search;


	chess_ai(int depth, int sel_depth): m_depth(depth), m_sel_depth(sel_depth), m_search(depth, sel_depth) {}

	void signal_stop() noexcept {
		m_search.signal_stop();
	}

	void notify_book(Move move) {
		book::add_move(move);
	}
	void reset() {
		book::reset();
	}
	Move get_best_move(Position& p) {

		if (p.turn() == WHITE) {
			Move bookMove = book::get_book_move<WHITE>(p);
			if (bookMove.str() != "a1a1") {
				bq::logger::info("------------------------------------------");
				bq::logger::info("Book selection - " + bookMove.str_d());
				bq::logger::info("------------------------------------------");
				book::add_move(bookMove);
				return bookMove;
			}
		}
		else {
			Move bookMove = book::get_book_move<BLACK>(p);
			if (bookMove.str() != "a1a1") {
				book::add_move(bookMove);
				bq::logger::info("------------------------------------------");
				bq::logger::info("Book selection - " + bookMove.str_d());
				bq::logger::info("------------------------------------------");
				return bookMove;

			}
		}

		if (p.turn() == WHITE) {

			Move move = m_search.initiate_iterative_search<WHITE>(p, m_depth);
			book::add_move(move);
			return move;
		}
		else {
			Move move = m_search.initiate_iterative_search<BLACK>(p, m_depth);
			book::add_move(move);
			return move;
		}
	}
};