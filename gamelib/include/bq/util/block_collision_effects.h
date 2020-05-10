#pragma once

namespace bq {
	struct block_collision_effects {
		bool m_collision = false;
		size_t m_damage = 0;
		float m_slow = 0.f;
	};
}