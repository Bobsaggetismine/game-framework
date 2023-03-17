#pragma once
#include <bq.h>
#include <xutility>
#include <thread>

enum class TT_FLAG {
	EXACT,
	UPPERBOUND,
	LOWERBOUND
};

struct tt_entry {
	int depth;
	int score;
	TT_FLAG flag;
	bool valid;
};

class transposition_table {

	//std::vector<std::pair<uint64_t, bq::v2i>> m_table;
	std::unordered_map<uint64_t,tt_entry> m_table;
	Move m_selected_move;

	tt_entry tte;

public:
	std::unordered_map<std::string, int> move_scores;

	int LOOKUP_FAILED = -2000000000;

	uint64_t max_size = 10000000000;

	transposition_table() {
		tte.valid = false;
	}
	Move selected_move() {
		return m_selected_move;
	}
	void set_top_move(Move m) {
		m_selected_move = m;
	}

	tt_entry lookup(uint64_t hash, int depth) {
		if (m_table.find(hash) != m_table.end()) {
			return m_table[hash];
		}
		return tte;
	}
	void insert(uint64_t hash, tt_entry entry) {
		m_table[hash] = entry;
	}
	void clear() {
		m_table.clear();
	}
};