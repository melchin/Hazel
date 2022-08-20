#pragma once

/* 
	<project>->Properties->C / C++->Preprocessor->Preprocessor Definitions
	By adding HZ_PLATFORM_WINDOWS and HZ_BUILD_DLL within the Hazel project would
	allow us to dllexport anything prefixed with HAZEL_API. We can then update the
	Preporcessor Definitions for anything that needs to import the dll functions. 
	For example, the game project (Sandbox) will not include the HZ_BUILD_DLL but it
	will include the HZ_PLATFORM_WINDOWS (For now).
*/
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif	
#else
	#error Hazel only support Windows (for now)!
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)