#include "system.h"

// #include <chrono>
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <windows.h>
#include "global.h"

namespace Macer {
namespace Platf {
namespace System {
namespace fs = std::filesystem;

bool isPathValid(const std::string& path) {
    return fs::exists(path);
}

std::string getLocalPath() {
    return fs::current_path().string();
}

std::string getFilePath(const std::string& file) {
    fs::path root = "C:\\";
    // 从根检索
    for (const auto& e : fs::recursive_directory_iterator(root)) {
        // 是文件 是要找的
        if (e.is_regular_file() 
        && e.path().filename().string() == file) {
            // 返回第一个
            return e.path().string();
        }
    }
    return {}; // 找不到返回空路径
}

std::unordered_map<std::string, std::string> getFiles(const std::string& path) {
    std::unordered_map<std::string, std::string> files;
    for (const auto& e : fs::directory_iterator(path)) {
        if (e.is_regular_file()) {
            files[e.path().stem().string()] = e.path().string();
        }
    }
    return files;
}

// std::string getCloseTime(const std::string& path) {
//     if (!fs::exists(path)) {
//         std::cerr << "路径不存在：" << path << std::endl;
//         return "";
//     }
//     // 文件关闭时间
//     auto last_write_time_ns = fs::last_write_time(path);
//     auto last_write_time_tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>(last_write_time_ns);
//     std::time_t last_edit = std::chrono::system_clock::to_time_t(last_write_time_tp);
//     // 转换为本地时间
//     std::tm local_tm;
//     localtime_s(&local_tm, &last_edit);
//     // 格式化为 YYYY-MM-DD-HH-MM-SS
//     std::stringstream ss;
//     ss << std::put_time(&local_tm, "%Y-%m-%d-%H-%M-%S");
//     return ss.str();
// }

std::string _formatFileTime(const FILETIME& ft) {
    SYSTEMTIME st;
    FileTimeToSystemTime(&ft, &st);

    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(4) << st.wYear << "-"
       << std::setw(2) << st.wMonth << "-"
       << std::setw(2) << st.wDay << " "
       << std::setw(2) << st.wHour << ":"
       << std::setw(2) << st.wMinute << ":"
       << std::setw(2) << st.wSecond;
    return ss.str();
}

std::string getCreateTime(const std::string& path) {
    HANDLE h = CreateFile(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (h == INVALID_HANDLE_VALUE) {
        std::cerr << "Unable to open file" << std::endl;
        return "";
    }

    FILETIME create_time, exit_time, kernel_time;
    if (!GetFileTime(h, &create_time, &exit_time, &kernel_time)) {
        CloseHandle(h);
        std::cerr << "Unable to get file time" << std::endl;
        return "";
    }

    CloseHandle(h);
    return _formatFileTime(create_time);
}

void createPath(const std::string& path) {
    if (!fs::exists(path)) {
        fs::create_directories(path);
    }
}

void createPath(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        createPath(path);
    }
}

void renameFile(const std::string& path, const std::string& name) {
    if (!fs::exists(path)) {
        std::cerr << "路径不存在：" << path << std::endl;
        return;
    }
    std::string new_path = fs::path(path).parent_path().string() + "/" + name;
    fs::rename(path, new_path);
}

void sleep(int second) {
    Sleep(second * 1000);
}

} // namespace System
} // namespace Platf
} // namespace Macer