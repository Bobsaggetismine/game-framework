#include <bq/application/application.h>

	int main(int argc, char* argv[]) try
	{
#ifdef PLATFORM_WINDOWS
		//Windows memory leak detection
#ifdef _DEBUG
		int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
		dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
		dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
		_CrtSetDbgFlag(dbgFlags);
#endif

#endif
		return Application::thisApp_sm->main(argc, argv);
	}
	catch (char const * msg) {
		std::cerr << "exception string: " << msg << std::endl;
	}
	catch (std::exception const& e) {
		std::cerr << "std::exception: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Error: an exception has been caught..." << std::endl;
		return EXIT_FAILURE;
	}

	Application* Application::thisApp_sm = nullptr;


	int Application::main(int argc, char* argv[])
	{
		args_m.assign(argv, argv + argc);
		return execute();
	}


	Application::Application()
	{
		if (thisApp_sm)
		{
			std::cout << "Cannot have duplicate game instances!" << std::endl;
			std::terminate();
		}
		thisApp_sm = this;
	}

