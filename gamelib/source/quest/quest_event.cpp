#include "bqpch.h"
#include <bq/quest/quest_event.h>


namespace bq {
	quest_event::quest_event(quest_tpye type, size_t count, size_t id) {
		m_type = type;
		m_count = count;
		m_id = id;
	}
}