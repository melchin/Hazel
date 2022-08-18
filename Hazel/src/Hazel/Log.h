#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

namespace Hazel {
	class HAZEL_API Log
	{
	public:
		static void Init();
		/*
		* inline allows us to both declare AND define the method within a .h file.
		* This allows us to #include this .h file in multiple places without running into
		* linker issues.
		*/
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

/*
* Core Log Macros
* (...) for variable number of arguments
* __VA_ARGS__ so that the trace method receives those arguments
*/
#define HZ_CORE_TRACE(...) ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)  ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)  ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...) ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...) ::Hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Macros
#define HZ_TRACE(...) ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)  ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)  ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...) ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...) ::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)