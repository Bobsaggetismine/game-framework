#pragma once

#include <chrono>

namespace bq {
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;
	class profiler {
		std::chrono::high_resolution_clock m_clock;
		std::chrono::time_point<std::chrono::steady_clock> m_point;

		std::string m_function_name;
		void start();
		void stop();
	public:
		profiler(const std::string&);
		~profiler();

		
	};
}