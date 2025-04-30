#pragma once

#ifdef _WIN32
#ifdef BUILD_SUM_DLL
#define SUM_DLL_API __declspec(dllexport)
#else
#define SUM_DLL_API __declspec(dllimport)
#endif
#else
#define SUM_DLL_API __attribute__((__visibility__("visible")))
#endif

namespace library {

	SUM_DLL_API int sum(int a, int b);

	double sum(double a, double b);

} // namespace library