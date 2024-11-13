#include "global.h"

void _init(int argc, char** argv) {
    gCfg.option.parse(argc, argv);
    Logger::createInstance(
        gCfg.path.cache.log, 
        gCfg.option.debug 
        ? Logger::Level::kDebug 
        : Logger::Level::kInfo, 
        [](const std::string& message) {
            std::cerr << message << std::endl;
        }
    );
}

void _execute() {
    if (gCfg.option.daily) {
        // TODO: 调用 daily 入口
    }
    if (gCfg.option.grind) {
        // TODO: 调用 grind 入口
        // 将 profession 和 market 当参数传进去
    }
}

int main(int argc, char* argv[]) {
    _init(argc, argv);
    gLog.info("开始");
    _execute();
    gLog.info("结束");
    return 0;
}