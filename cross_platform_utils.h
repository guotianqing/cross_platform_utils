#ifndef _CROSS_PLATFORM_UTILS_
#define _CROSS_PLATFORM_UTILS_

#include <cstring>
#include <string>
#include <vector>

#if defined _WIN32 || defined _WIN64
#define FILE_SEP "\\"
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1):__FILE__)
#else
#define FILE_SEP "/"
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)
#endif

#define FILE_FUN   __FILENAME__ << ":" << __FUNCTION__ << ":" << __LINE__<< "|"
#define FILE_FUN_STR  std::string(__FILENAME__) + ":" + __FUNCTION__ + ":" + std::to_string(__LINE__) + "|"

class CrossPlatformUtils
{
public:
	/* 
	 * 获取当前线程唯一标识：tid
	 * 跨平台实现，与unix下的top显示和windows下的process explore查看的线程id一致
	 */
	static long GetTid();

	/* 
	 * 进程是否是运行状态
	 * 返回值：是-true，否-false
	 */
	static bool IsProcessRunning(const std::string& process);

	/*
	 * 获取本地时间戳
	 * 结果为1970年以来的微秒数
	 * 可用来记录到日志，分析业务逻辑的时延
	 */
	static int64_t GetLocalTimeStamp();

	/*
	 * 根据指定的分割符分割字符串
	 * 默认分割符为空格
	 * 返回分割后的结果
	 */
	static std::vector<std::string> SplitString(const std::string& s, char delimiter = ' ');

	/*
	 */
	static int GetRandomNumber(const int min, const int max);

	/*
	* 获取文件最后更新时间
	* param: filename with path
	* return: if succ, return HHMMSS, else return ""
	*/
	static std::string GetFileLastModTime(const std::string& filename);
};

#endif // !_CROSS_PLATFORM_UTILS_