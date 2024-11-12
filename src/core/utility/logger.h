#ifndef E71DC334_1E8F_4B5E_959F_A573A861CA95
#define E71DC334_1E8F_4B5E_959F_A573A861CA95

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <mutex>

class Logger {

public:
    using Callback = std::function<void(const std::string&)>;
    // 日志级别枚举
    enum class Level {
        kTrace,
        kDebug,
        kInfo,
        kWarning,
        kError,
        kCritical
    };

    // 单例
    static Logger& getInstance(const std::string& path, Level level = Level::kInfo, Callback callback = nullptr);

    // 删除复制构造函数和赋值操作符
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 调整会被记录的最低级别
    void setLogLevel(Level level);

    // 具体日志级别方法
    void trace(const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void crit(const std::string& message);

private:
    std::ofstream logFile;
    Level logLevel;
    Callback logCallback;
    std::mutex logMutex;

    // 私有构造函数
    Logger(const std::string& filename, Level level, Callback callback);
    ~Logger() = default;

    // 日志记录
    void log(Level level, const std::string& message);
    
    // 消息格式化
    std::string formatLogMessage(Level level, const std::string& message);
};

#endif /* E71DC334_1E8F_4B5E_959F_A573A861CA95 */