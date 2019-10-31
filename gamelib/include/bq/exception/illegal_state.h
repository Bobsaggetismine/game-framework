#pragma once
#include <exception>
#include <string>

namespace bq {
	class illegal_state : public std::exception {
		std::string what_msg;
	public:

		illegal_state(const std::string& what_arg) {
			what_msg = what_arg;
		}

		virtual const char* what() const override
		{
			return what_msg.c_str();
		}
	};
};
