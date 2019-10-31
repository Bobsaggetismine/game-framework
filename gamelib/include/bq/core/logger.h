#pragma once

#include <iostream>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif


namespace bq {
	constexpr int WHITE = 7;
	constexpr int INFO_COLOR = 5;
	constexpr int WARN_COLOR = 14;
	constexpr int CRITICAL_COLOR = 12;
	enum class log_level {
		INFO,
		WARN,
		CRITICAL
	};
	/*
		TODO: add support to output colored 
	*/
	class logger {

		static log_level m_level;
	public:
		static void set_log_level(log_level level) {
			m_level = level;
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

		}
	};
}