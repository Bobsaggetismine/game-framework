#pragma once
#include <string>


namespace bq {

	enum class quest_tpye {
		COMBAT
	};

	struct quest_event {
		int m_count;
		int m_id;
		quest_tpye m_type;
		quest_event(const quest_tpye, const float, const int);
	};
}