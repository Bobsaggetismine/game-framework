#pragma once
// Setup DBG environment

#ifdef PLATFORM_WINDOWS
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif

#include <bq/common.h>

class Application {
	using Args = std::vector<std::string>;

	static Application* thisApp_sm;

	Args args_m;

	friend int main(int argc, char* argv[]);
	int main(int argc, char* argv[]);

protected:
	Application();
	virtual int execute() = 0;
	Args const& get_args() const { return args_m; }
};
