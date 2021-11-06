#include "bqpch.h"

#include <bq/quest/quest_event.h>

#include "bq/quest/quest.h"


bq::quest::~quest()
{
}

bool bq::quest::completed() {
	return m_completed;
}
