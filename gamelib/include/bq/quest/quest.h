#pragma once
#include <string>
namespace bq {
	class quest {
	protected:
		bool m_completed = false;
		std::string m_desc;
	public:
		bool completed();
		virtual void update() = 0;
	};
}
