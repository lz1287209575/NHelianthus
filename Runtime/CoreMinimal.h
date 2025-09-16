#pragma once

struct PlatformFunctions
{
public:
	static void* GetModuleHandle(const char* ModuleName);
	static void* GetProcAddress(void* ModuleHandle, const char* ProcName);
	static unsigned long GetLastError();
    static void Sleep(unsigned long Milliseconds);

	static void GetProcessName(char* Buf, size_t BufSize);
};