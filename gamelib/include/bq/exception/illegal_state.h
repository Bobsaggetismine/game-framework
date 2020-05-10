#pragma once


namespace bq {

	class illegal_state : public std::exception {
		std::string m_what;
	public:

		illegal_state(const std::string& what_arg);

		virtual const char* what() const override;
	};
};
