#include "system.h"

#include <filesystem>
#include <windows.h>
#include "logger.h"

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

std::vector<std::string> getFiles(const std::string& path) {
    std::vector<std::string> files;
    for (const auto& e : fs::directory_iterator(path)) {
        if (e.is_regular_file()) {
            files.push_back(e.path().string());
        }
    }
    return files;
}

std::string getCreateTime(const std::string& path) {
    if (!fs::exists(path)) {
        std::cerr << "路径不存在：" << path << std::endl;
        return "";
    }
    // 文件创建时间
    std::time_t createTime = fs::last_write_time(path);
    // 转换为本地时间
    std::tm* localTime = std::localtime(&createTime);
    // 格式化为 YYYY-MM-DD-HH-MM-SS
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d-%H-%M-%S");
    return ss.str();
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