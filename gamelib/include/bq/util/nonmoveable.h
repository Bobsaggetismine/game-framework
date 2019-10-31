#pragma once

namespace bq {
	struct nonmoveable {

		nonmoveable() = default;
		nonmoveable& operator= (nonmoveable&&) = delete;
		nonmoveable(nonmoveable&&) = delete;

	};
}

