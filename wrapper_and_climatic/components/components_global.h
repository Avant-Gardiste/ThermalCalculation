#ifndef COMPONENTS_GLOBAL_H
#define COMPONENTS_GLOBAL_H

#ifdef _WIN32
#if defined(COMPONENTS_LIBRARY)
#  define COMPONENTSSHARED_EXPORT __declspec(dllexport)
#else
#  define COMPONENTSSHARED_EXPORT __declspec(dllimport)
#endif
#else
#  define COMPONENTSSHARED_EXPORT
#endif

#endif // COMPONENTS_GLOBAL_H
