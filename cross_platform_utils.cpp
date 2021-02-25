#include "cross_platform_utils.h"

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#include <processthreadsapi.h>
#include <tlhelp32.h>
#else
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#endif

#include <chrono>
#include <boost/shared_ptr.hpp>

using std::string;

long CrossPlatformUtils::GetTid()
{
#if TARGET_PLATFORM_WINDOWS
	return GetCurrentThreadId();
#else
	return syscall(SYS_gettid);
#endif // TARGET_PLATFORM_WINDOWS
}

bool CrossPlatformUtils::IsProcessRunning(const std::string& process)
{
#if TARGET_PLATFORM_WINDOWS
	PROCESSENTRY32 processEntry32;
	HANDLE toolHelp32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (((int)toolHelp32Snapshot) != -1)
	{
		processEntry32.dwSize = sizeof(processEntry32);
		if (Process32First(toolHelp32Snapshot, &processEntry32))
		{
			do
			{
				const size_t size = strlen(processEntry32.szExeFile) + 1;
				boost::shared_ptr<wchar_t[]> wa(new wchar_t[size]);
				mbstowcs(wa.get(), processEntry32.szExeFile, size);

				int iLen = 2 * wcslen(wa.get());
				char* chRtn = new char[iLen + 1];
				//转换成功返回为非负值
				wcstombs(chRtn, wa.get(), iLen + 1);
				if (strcmp(process.c_str(), chRtn) == 0)
				{
					CloseHandle(toolHelp32Snapshot);
					return true;
				}
			} while (Process32Next(toolHelp32Snapshot, &processEntry32));
		}
		CloseHandle(toolHelp32Snapshot);
	}
	return false;
#else
	string cmdline = "pidof -x " + process + " > /dev/null";
	return (system(cmdline.c_str()) == 0);
#endif // TARGET_PLATFORM_WINDOWS
}

int64_t CrossPlatformUtils::GetLocalTimeStamp()
{
	// 根据需要调整时间精度，这里是us
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
