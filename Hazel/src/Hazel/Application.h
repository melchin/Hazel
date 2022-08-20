#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

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
	private:
		// unique_ptr because only this Application class will point to m_Window
		// and we don't need to delete the ptr ourselves when Application terminates
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	/*
	* To be defined in CLIENT. Possible because EntryPoint.h prefixes this method with
	* the extern keyword.
	*/ 
	Application* CreateApplication();
}


