#ifndef TIME_SPAN_STATS_H_
#define TIME_SPAN_STATS_H_

#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono;
using std::string;

class TimeSpanStats
{
public:
    TimeSpanStats(const string& msg, const int32_t threshold): msg_(msg), threshold_(threshold) {
        t_start_ = high_resolution_clock::now();
    }
    ~TimeSpanStats() {
        high_resolution_clock::time_point t_end_ = high_resolution_clock::now();
        duration<double, std::micro> time_span = t_end_ - t_start_;
        int ts = time_span.count();
        if (ts >= threshold_) {
            std::cout << msg_ << "|tooks|" << std::fixed << time_span.count() << "|us" << std::endl;
        }
    }

    int64_t GetTimeSpanUs() {
        high_resolution_clock::time_point t_end_ = high_resolution_clock::now();
        duration<double, std::micro> time_span = t_end_ - t_start_;
        return time_span.count();
    }
    
private:
    string msg_;
    int32_t threshold_;
    high_resolution_clock::time_point t_start_;
};

#endif