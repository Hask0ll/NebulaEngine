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

#define BIT(x) (1 << x)

#endif
