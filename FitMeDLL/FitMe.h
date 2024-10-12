#pragma once

#ifdef FIT_DLL_EXPORTS
#define FIT_DLL_API __declspec(dllexport)
#else
#define FIT_DLL_API __declspec(dllimport)
#endif

#include <vector>
#include <string>

extern "C" FIT_DLL_API void Plot(const std::vector<double>& x, const std::vector<double>& y, const std::string& method, int degree = 5, const std::string& filename = "tmp.svg");
extern "C" FIT_DLL_API void PlotS(const std::string & dataString, const std::string & methodString, int degree, const std::string & filename);