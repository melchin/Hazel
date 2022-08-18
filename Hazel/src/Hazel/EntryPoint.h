#pragma once

/*
* This is our entry point if our Platform is set to Windows.
*/
#ifdef HZ_PLATFORM_WINDOWS

/*
* extern keyword here specifies that the CreateApplication method has external linkage.
* This allows us to define the function in another translation unit. For instance,
* our game (Sandbox) can define the CreateApplication function that will be used within the
* main function below.
*/
extern Hazel::Application* Hazel::CreateApplication();
int main(int argc, char** argv)
{
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif