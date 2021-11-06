#include <bqpch.h>
#include <bq/core/profiler.h>


bq::profiler::profiler(const std::string& function_name): m_function_name(function_name) {
	start();
}
bq::profiler::~profiler() {
	stop();
}
void bq::profiler::start() {
	m_point = std::chrono::steady_clock::now();
}
void bq::profiler::stop() {
	auto endTimepoint = std::chrono::steady_clock::now();
	auto highResStart = FloatingPointMicroseconds{ m_point.time_since_epoch() };
	auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_point).time_since_epoch();
	bq::logger::info(m_function_name + ": " + std::to_string(elapsedTime.count()));
}
