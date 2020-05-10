#pragma once
#include <string>


namespace bq {

	enum class quest_tpye {
		COMBAT
	};

	struct quest_event {
		size_t m_count;
		size_t m_id;
		quest_tpye m_type;
		quest_event(quest_tpye, size_t, size_t);
	};
}