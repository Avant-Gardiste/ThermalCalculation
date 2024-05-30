#ifndef SOLARCHARIACTERISTICS_GLOBAL_H
#define SOLARCHARIACTERISTICS_GLOBAL_H

#ifdef _WIN32
#if defined(SOLARCHARIACTERISTICS_LIBRARY)
#  define SOLARCHARIACTERISTICSSHARED_EXPORT __declspec(dllexport)
#else
#  define SOLARCHARIACTERISTICSSHARED_EXPORT __declspec(dllimport)
#endif
#else
#  define SOLARCHARIACTERISTICSSHARED_EXPORT
#endif
#endif // SOLARCHARIACTERISTICS_GLOBAL_H