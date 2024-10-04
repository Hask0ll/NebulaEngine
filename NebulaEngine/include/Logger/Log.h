#pragma once
#include "spdlog/spdlog.h"
#include "Core/Core.h"

#include <memory>

namespace Nebula
{
	/**
	 * \brief The Log class provides static methods for initializing and shutting down logging,
	 * and for accessing core and client loggers.
	 */
	class NEBULA Log
	{
	public:
		/**
		 * \brief Initialize the logging system.
		 *
		 * This function sets up the core and client loggers using `spdlog`.
		 * It should be called early in the application lifecycle.
		 */
		static void Init();

		/**
		 * \brief Shutdown the logging system.
		 *
		 * This function should be called before the application exits to properly shut down the logging system.
		 */
		static void Shutdown();

		/**
		 * \brief Get the core logger instance.
		 *
		 * The core logger is used for logging messages related to the engine or core library itself.
		 *
		 * \return A shared pointer to the core logger instance.
		 */
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/**
		 * \brief Get the client logger instance.
		 *
		 * The client logger is used for logging messages related to the client application or game.
		 *
		 * \return A shared pointer to the client logger instance.
		 */
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		/** \brief A shared pointer to the core logger instance. */
		static std::shared_ptr<spdlog::logger> s_CoreLogger;

		/** \brief A shared pointer to the client logger instance. */
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	// Macros for logging with the core logger
#define NB_CORE_TRACE(...)    ::Nebula::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NB_CORE_INFO(...)     ::Nebula::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NB_CORE_WARN(...)     ::Nebula::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NB_CORE_ERROR(...)    ::Nebula::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NB_CORE_CRITICAL(...) ::Nebula::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Macros for logging with the client logger
#define NB_CLIENT_TRACE(...)    ::Nebula::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NB_CLIENT_INFO(...)     ::Nebula::Log::GetClientLogger()->info(__VA_ARGS__)
#define NB_CLIENT_WARN(...)     ::Nebula::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NB_CLIENT_ERROR(...)    ::Nebula::Log::GetClientLogger()->error(__VA_ARGS__)
#define NB_CLIENT_CRITICAL(...) ::Nebula::Log::GetClientLogger()->critical(__VA_ARGS__)
}
