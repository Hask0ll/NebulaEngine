#ifndef NEBULA_H
#define NEBULA_H

#ifdef _WIN32
#  ifdef NEBULA_EXPORTS
#    define NEBULA __declspec(dllexport)
#  else
#    define NEBULA __declspec(dllimport)
#  endif
#else
#  define NEBULA
#endif

#ifdef NB_ENABLE_ASSERTS
#  define NB_ASSERT(x, ...) { if(!(x)) { NB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#  define NB_CORE_ASSERT(x, ...) { if(!(x)) { NB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#  define NB_ASSERT(x, ...)
#  define NB_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#endif
