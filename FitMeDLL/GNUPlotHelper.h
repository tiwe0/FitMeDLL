#pragma once
#include <windows.h>
#include <fstream>
#include <string>
#include <sys/stat.h>

#define IDR_GNUPLOT_EXECUTABLE 102

void CreateDirectoryIfNotExists(const std::string& dirPath);
void ExtractAndWriteGnuplotExecutable();
void AddToPath(const std::string& newPath);
void CleanupGnuplotExecutable(const std::string& exePath);