#include <bq/quest/quest_event.h>


namespace bq {
	quest_event::quest_event(const quest_tpye type, const float count, const int id) {
		m_type = type;
		m_count = count;
		m_id = id;
	}
}