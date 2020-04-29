#pragma once
// Setup DBG environment

#ifdef PLATFORM_WINDOWS
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif

#include <bq/common.h>
class application {

	static application* m_app;

	std::vector<std::string> m_args;

	friend int main(int argc, char* argv[]);
	int main(int argc, char* argv[]);

protected:
	application();
	virtual int execute() = 0;
	virtual void init() = 0;
	const std::vector<std::string>& get_args() const { return m_args; }
};
