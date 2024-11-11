#include "system.h"

#include <filesystem>
#include "logger.h"

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
}