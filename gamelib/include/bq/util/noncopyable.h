#pragma once

namespace bq{
	struct noncopyable {

		noncopyable() = default;
		noncopyable(const noncopyable&) = delete;
		noncopyable& operator= (const noncopyable&) = delete;

	};
}
