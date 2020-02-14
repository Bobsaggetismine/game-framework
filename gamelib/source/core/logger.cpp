#include <bq/core/logger.h>



bq::log_level bq::logger::m_level = bq::log_level::INFO;
bool bq::logger::m_file_logging = false;
std::string bq::logger::m_file = "";