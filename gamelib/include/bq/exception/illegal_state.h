#pragma once
#include <exception>
#include <string>

namespace bq {
	class illegal_state : public std::exception {
		std::string m_what;
	public:

		illegal_state(const std::string& what_arg) {
			m_what = what_arg;
		}

		virtual const char* what() const override
		{
			return m_what.c_str();
		}
	};
};
