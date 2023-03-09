#pragma once
#include <bq.h>
#include <xutility>


class transposition_table {

	//std::vector<std::pair<uint64_t, bq::v2i>> m_table;
	std::unordered_map<uint64_t, bq::v2i> m_table;

public:

	int LOOKUP_FAILED = -2000000000;


	transposition_table() {

	}


	void save() {
		bq::logger::info("saving tt");
		FILE* f = fopen("t_table", "wb");
		for (auto& pair : m_table) {
			fwrite(&(pair.first), 8, 1, f);
			fwrite(&(pair.second.x), 4, 1, f);
			fwrite(&(pair.second.y), 4, 1, f);
		}
		fclose(f);
	}

	void load() {
		FILE* f = fopen("t_table", "rb");
		uint64_t key;
		int x, y;
		while (fread(&key, 8, 1, f)) {
			fread(&x, 4, 1, f);
			fread(&y, 4, 1, f);
			m_table[key] = {x,y};
		}
		fclose(f);
	}
	int lookup(uint64_t hash, int depth) {
		if (m_table.find(hash) != m_table.end()) {
			if (m_table[hash].x < depth) {
				return LOOKUP_FAILED;
			}
			return m_table[hash].y;
		}
		return LOOKUP_FAILED;
	}
	void insert(uint64_t hash, int depth, int score) {
		m_table[hash] = {depth, score};
	}
};