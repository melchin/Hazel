#pragma once
#include "Core.h"

namespace Hazel {
	/*
	* Prefixed with the HAZEL_API macro which allows us to dllexport or dllimport this
	* Application class depending on which project this .h file is included in.
	*/
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	/*
	* To be defined in CLIENT. Possible because EntryPoint.h prefixes this method with
	* the extern keyword.
	*/ 
	Application* CreateApplication();
}


