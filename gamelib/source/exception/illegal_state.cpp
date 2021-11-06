#include "bqpch.h"

#include <bq/exception/illegal_state.h>

bq::illegal_state::illegal_state(const std::string& what_arg)
{
    m_what = what_arg;	
}

const char* bq::illegal_state::what() const noexcept
{
	return m_what.c_str();
}