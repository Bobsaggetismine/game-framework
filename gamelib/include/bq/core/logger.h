#pragma once

#include <iostream>
#include <fstream>
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif


namespace bq {
	constexpr int WHITE = 7;
	constexpr int INFO_COLOR = 5;
	constexpr int WARN_COLOR = 14;
	constexpr int DEBUG_COLOR = 6;
	constexpr int CRITICAL_COLOR = 12;
	enum class log_level {
		DBG,
		INFO,
		WARN,
		CRITICAL
	};
	/*
		TODO: add support to output colored 
	*/
	class logger {
		static std::string m_file;
		static log_level m_level;
		static bool m_file_logging;
	public:
		static void set_log_level(log_level level) {
			m_level = level;
		}

		static void log_to_file(const std::string& file) {
			m_file = file;
			m_file_logging = true;
		}
		static void debug(std::string message) {
#ifdef PLATFORM_WINDOWS
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, DEBUG_COLOR);
#endif
			if(m_level == log_level::DBG)
			std::cout << "DEBUG: " << message << std::endl;
#ifdef PLATFORM_WINDOWS
			SetConsoleTextAttribute(hConsole, WHITE);
#endif
			if (m_file_logging) {
				std::ofstream ofs;
				ofs.open(m_file, std::ofstream::out | std::ofstream::app);
				ofs << "DEBUG: " << message << std::endl;
				ofs.close();
			}
		}


		static void info(std::string message) {
#ifdef PLATFORM_WINDOWS
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, INFO_COLOR);
#endif
			std::cout << "INFO: " << message << std::endl;
#ifdef PLATFORM_WINDOWS
			SetConsoleTextAttribute(hConsole, WHITE);
#endif
			if (m_file_logging) {
				std::ofstream ofs;
				ofs.open(m_file, std::ofstream::out | std::ofstream::app);
				ofs << "INFO: " << message << std::endl;
				ofs.close();
			}
		}
		static void warn(std::string message) {
#ifdef PLATFORM_WINDOWS
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, WARN_COLOR);
#endif
			std::cout << "WARN: " << message << std::endl;
#ifdef PLATFORM_WINDOWS
			SetConsoleTextAttribute(hConsole, WHITE);
#endif
			if (m_file_logging) {
				std::ofstream ofs;
				ofs.open(m_file, std::ofstream::out | std::ofstream::app);
				ofs << "WARN: " << message << std::endl;
				ofs.close();
			}
		}
		static void critical(std::string message) {
#ifdef PLATFORM_WINDOWS
			HANDLE  hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CRITICAL_COLOR);
#endif
			std::cout << "CRITICAL: " << message << std::endl;
#ifdef PLATFORM_WINDOWS
			SetConsoleTextAttribute(hConsole, WHITE);
#endif
			if (m_file_logging) {
				std::ofstream ofs;
				ofs.open(m_file, std::ofstream::out | std::ofstream::app);
				ofs << "CRITICAL: "<< message << std::endl;
				ofs.close();
			}
		}
	};
}