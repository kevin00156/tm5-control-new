#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "header/generateLogFileName.h"

std::string generateLogFileName() {
    // 獲取當前時間
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
    // 格式化時間 yyyy-mm-dd_hh:mm:ss
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "./log/%Y-%m-%d_%H-%M-%S.log");
    
    // 返回格式化的文件名
    return ss.str();
}