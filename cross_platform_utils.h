#ifndef _CROSS_PLATFORM_UTILS_
#define _CROSS_PLATFORM_UTILS_

#include <cstring>
#include <string>

#if defined _WIN32 || defined _WIN64
#define FILE_SEP "\\"
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1):__FILE__)
#else
#define FILE_SEP "/"
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#endif

#define FILE_FUN   __FILENAME__<<":"<<__FUNCTION__<<":"<<__LINE__<<"|"
#define FILE_FUN_STR  TC_Common::tostr(__FILENAME__)+":"+TC_Common::tostr(__FUNCTION__)+":"+TC_Common::tostr(__LINE__)+"|"

class CrossPlatformUtils
{
public:
	/* 
	 * 获取当前线程唯一标识：tid
	 * 跨平台实现，与unix下的top显示和windows下的process explore查看的线程id一致
	 */
	static long GetTid();
	static bool IsProcessRunning(const std::string& process);
	static int64_t GetLocalTimeStamp();
};

#endif // !_LOG_UTIL_H_