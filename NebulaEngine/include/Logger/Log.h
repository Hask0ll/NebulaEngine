#pragma once
#include "spdlog/spdlog.h"

#include <memory>

namespace Nebula
{
	class Log
	{
	public:
		static void Init();
		static void Shutdown();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	#define NB_CORE_TRACE(...)    ::Nebula::Log::GetCoreLogger()->trace(__VA_ARGS__);
	#define NB_CORE_INFO(...)     ::Nebula::Log::GetCoreLogger()->info(__VA_ARGS__);
	#define NB_CORE_WARN(...)     ::Nebula::Log::GetCoreLogger()->warn(__VA_ARGS__);
	#define NB_CORE_ERROR(...)    ::Nebula::Log::GetCoreLogger()->error(__VA_ARGS__);
	#define NB_CORE_CRITICAL(...) ::Nebula::Log::GetCoreLogger()->critical(__VA_ARGS__);

	#define NB_CLIENT_TRACE(...)    ::Nebula::Log::GetClientLogger()->trace(__VA_ARGS__);
	#define NB_CLIENT_INFO(...)     ::Nebula::Log::GetClientLogger()->info(__VA_ARGS__);
	#define NB_CLIENT_WARN(...)     ::Nebula::Log::GetClientLogger()->warn(__VA_ARGS__);
	#define NB_CLIENT_ERROR(...)    ::Nebula::Log::GetClientLogger()->error(__VA_ARGS__);
	#define NB_CLIENT_CRITICAL(...) ::Nebula::Log::GetClientLogger()->critical(__VA_ARGS__);
}
