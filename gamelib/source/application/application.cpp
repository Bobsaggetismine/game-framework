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
		bq::logger::critical(msg);
	}
	catch (std::exception const& e) {
		bq::logger::critical(e.what());
	}
	catch (...) {
		bq::logger::critical("unknown error thown!");
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
			bq::logger::critical("no duplicate game instances!");
			std::terminate();
		}
		thisApp_sm = this;
	}

