#include "GNUPlotHelper.h"

void
CreateDirectoryIfNotExists
(const std::string& dirPath)
{
    // 检查目录是否存在，如果不存在则创建
    struct stat info;
    if (stat(dirPath.c_str(), &info) != 0) {
        // 目录不存在，创建它
        CreateDirectoryA(dirPath.c_str(), NULL);
    }
}

void ExtractAndWriteGnuplotExecutable()
{
    // 获取系统临时目录路径
    char tempPath[MAX_PATH];
    DWORD pathLen = GetTempPathA(MAX_PATH, tempPath);
    if (pathLen == 0) {
        // 错误处理，无法获取临时路径
        return;
    }

    // 设置目标目录为临时目录
    std::string outputDir = std::string(tempPath) + "gnuplot\\";

    // 如果目录不存在，则创建
    CreateDirectoryIfNotExists(outputDir.c_str());

    // 查找资源
    HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_GNUPLOT_EXECUTABLE), RT_RCDATA);
    if (!hResource) return;

    // 加载资源
    HGLOBAL hResData = LoadResource(NULL, hResource);
    if (!hResData) return;

    // 锁定资源获取指针
    void* pData = LockResource(hResData);
    DWORD dwSize = SizeofResource(NULL, hResource);

    // 写入到磁盘
    std::string outputFilePath = outputDir + "gnuplot.exe";  // 保存路径
    std::ofstream outFile(outputFilePath, std::ios::binary);
    outFile.write(static_cast<const char*>(pData), dwSize);
    outFile.close();
}

void AddToPath(const std::string& newPath)
{
    // 获取当前 PATH 环境变量
    char buffer[32767]; // 环境变量大小限制
    DWORD pathLen = GetEnvironmentVariableA("PATH", buffer, sizeof(buffer));
    std::string currentPath(buffer, pathLen);

    // 构建新的 PATH
    std::string updatedPath = currentPath + ";" + newPath;

    // 设置新的 PATH
    SetEnvironmentVariableA("PATH", updatedPath.c_str());
}

void 
CleanupGnuplotExecutable
(const std::string& exePath)
{
    DeleteFileA(exePath.c_str());
}