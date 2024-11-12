#include "logger.h"

#include <ctime>
#include <sstream>
#include "global.h"
#include "system.h"

namespace Macer {
namespace Class {

Logger::Logger(const std::string& path, Level level, Callback callback) : logLevel(level), logCallback(callback) {
    std::string folder = gCfg.path.cache.log
    std::string latest = folder + "/latest.log";
    std::string oldlog = System::getCreateTime(latest) + ".log";
    System::renameFile(latest, oldlog);
    logFile(latest, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "打不开日志：" << latest << std::endl;
    }
}

// Logger& Logger::getInstance(const std::string& filename, Level level, Callback callback) {
//     static Logger instance(filename, level, callback); // 局部静态变量，保证只创建一次
//     return instance;
// }

Logger& Logger::getInstance() {
    if (instance == nullptr) {
        throw std::runtime_error("Logger 实例尚未创建");
    }
    return *instance;
}

void Logger::createInstance(const std::string& filename, Level level, Callback callback) {
    if (instance == nullptr) {
        instance = new Logger(filename, level, callback);
    } else {
        std::cerr << "Logger 实例已经创建过，无法创建" << std::endl;
    }
}

void Logger::setLogLevel(Level level) {
    logLevel = level;
}

void Logger::log(Level lvl, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (lvl < logLevel) return;

    std::string formattedMessage = formatLogMessage(lvl, message);
    logFile << formattedMessage << std::endl;
    if (logCallback) {
        logCallback(formattedMessage);
    }
}

void Logger::trace(const std::string& message) {
    log(Level::kTrace, message);
}

void Logger::debug(const std::string& message) {
    log(Level::kDebug, message);
}

void Logger::info(const std::string& message) {
    log(Level::kInfo, message);
}

void Logger::warn(const std::string& message) {
    log(Level::kWarning, message);
}

void Logger::error(const std::string& message) {
    log(Level::kError, message);
}

void Logger::crit(const std::string& message) {
    log(Level::kCritical, message);
}

std::string Logger::formatLogMessage(Level level, const std::string& message) {
    std::string levelStr;
    switch (level) {
        case Level::kTrace: levelStr = "trace"; break;
        case Level::kDebug: levelStr = "debug"; break;
        case Level::kInfo: levelStr = "info"; break;
        case Level::kWarning: levelStr = "warn"; break;
        case Level::kError: levelStr = "error"; break;
        case Level::kCritical: levelStr = "crit"; break;
    }
    std::time_t now = std::time(nullptr);
    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return "[" + std::string(buffer) + "][" + levelStr + "] " + message;
}

}
}