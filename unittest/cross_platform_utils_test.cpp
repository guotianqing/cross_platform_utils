#include <gtest/gtest.h>
#include "cross_platform_utils.h"
#include "time_span_stats.h"

#include <string>
#include <vector>
#include <thread>

using std::string;
using std::vector;

TEST(get_tid_test, unix)
{
    ASSERT_TRUE(CrossPlatformUtils::GetTid() > 0);
    EXPECT_GT(CrossPlatformUtils::GetTid(), 1000);
    EXPECT_LT(CrossPlatformUtils::GetTid(), __LONG_MAX__);
    ASSERT_EQ(CrossPlatformUtils::GetTid(), CrossPlatformUtils::GetTid());
}

TEST(is_process_running_test, unix)
{
    EXPECT_FALSE(CrossPlatformUtils::IsProcessRunning("abc"));
    EXPECT_TRUE(CrossPlatformUtils::IsProcessRunning("init"));
}

TEST(get_local_time_stamp_test, unix)
{
    EXPECT_TRUE(CrossPlatformUtils::GetLocalTimeStamp() > 0);
    EXPECT_GT(CrossPlatformUtils::GetLocalTimeStamp(), 1000);
    EXPECT_LT(CrossPlatformUtils::GetLocalTimeStamp(), __INT64_MAX__);
    EXPECT_LE(CrossPlatformUtils::GetLocalTimeStamp(), CrossPlatformUtils::GetLocalTimeStamp());
}

TEST(split_string_test, unix)
{
    string s_space = "a b c";
    string s_underscore = "a_b_c";
    vector<string> s = {"a", "b", "c"};

    EXPECT_TRUE(CrossPlatformUtils::SplitString(s_space).size() == s.size());
    EXPECT_EQ(CrossPlatformUtils::SplitString(s_space).at(0), s.at(0));
    EXPECT_NE(CrossPlatformUtils::SplitString(s_underscore, '_').at(2), s.at(1));
    EXPECT_EQ(CrossPlatformUtils::SplitString(s_underscore, '_').at(2), s.at(2));
}

TEST(get_random_number_test, unix)
{
    EXPECT_GE(CrossPlatformUtils::GetRandomNumber(0, 10), 0);
    EXPECT_LE(CrossPlatformUtils::GetRandomNumber(0, 10), 10);
    EXPECT_LT(CrossPlatformUtils::GetRandomNumber(0.0, 10.0), 11);
}

TEST(time_span_stats_deconstruct, unix)
{
    TimeSpanStats time_span_stats(1, std::cout << "time_span_stats_deconstruct");
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

TEST(time_span_stats_point, unix)
{
    TimeSpanStats time_span_stats(1, std::cout << "time_span_stats_point");
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    EXPECT_GT(time_span_stats.GetTimeSpanUs(), 1000);
}

TEST(GetFileLastModTime, unix)
{
    ASSERT_GT(CrossPlatformUtils::GetFileLastModTime("test").size(), 0);
    std::cout << CrossPlatformUtils::GetFileLastModTime("test") << std::endl;
}
