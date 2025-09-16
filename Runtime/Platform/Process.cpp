#include "CoreMinimal.h"
#include "Utils/StringUtils.h"

#include <string>

#ifdef _WIN32

#include <Windows.h>

void PlatformFunctions::GetProcessName(char* Buf, size_t BufSize)
{
    char Path[MAX_PATH];
    if (GetModuleFileName(NULL, Path, MAX_PATH) != 0)
    {
        std::string FullProcessInfo = StringUtils::Trim(std::string(Path));
        auto Pos = FullProcessInfo.find_last_of("\\/");
        std::string ProcessName = Pos == std::string::npos ? Path : FullProcessInfo.substr(Pos + 1);
        strncpy_s(Buf, BufSize, ProcessName.c_str(), BufSize - 1);
    }
}

#endif

#ifdef __linux__

#include <unistd.h>


void PlatformFunctions::GetProcessName(char* Buf, size_t BufSize)
{
    char Buf[256] = {0};
    ssize_t Len = readlink("/proc/self/exe", Buf, sizeof(Buf) - 1);
    if (Len != -1)
    {
        std::string FullProcessInfo = StringUtils::Trim(std::string(Buf, Len));
        auto Pos = FullProcessInfo.find_last_of("\\/");
        std::string ProcessName = Pos == std::string::npos ? Buf : FullProcessInfo.substr(Pos + 1);
        strncpy_s(Buf, BufSize, ProcessName.c_str(), BufSize - 1);
    }
}
#endif



#ifdef __APPLE__
#include <unistd.h>
void PlatformFunctions::GetProcessName(char* Buf, size_t BufSize)
{
    char Path[1024];
    uint32_t Size = sizeof(Path);
    if (_NSGetExecutablePath(Path, &Size) == 0)
    {
        std::string FullProcessInfo = StringUtils::Trim(std::string(Path));
        auto Pos = FullProcessInfo.find_last_of("\\/");
        std::string ProcessName = Pos == std::string::npos ? Path : FullProcessInfo.substr(Pos + 1);
        strncpy_s(Buf, BufSize, ProcessName.c_str(), BufSize - 1);
    }
}
#endif
