#include "global.h"

#include <iostream>

void _init(int argc, char** argv) {
    gCfg.option.parse(argc, argv);
    gLogger::createInstance(
        gCfg.path.cache.log, 
        gCfg.option.debug 
        ? gLogger::Level::kDebug 
        : gLogger::Level::kInfo, 
        [](const std::string& message) {
            std::cerr << message << std::endl;
        }
    );
}

void _execute() {
    gLogin::run();
    if (gCfg.option.daily) {
        // TODO: 调用 daily 入口
    }
    if (gCfg.option.grind) {
        // TODO: 调用 grind 入口
        // 将 profession 和 market 当参数传进去
    }
}

int main(int argc, char* argv[]) {
    std::cout << "test\n";
    _init(argc, argv);
    gLog.info("Start");
    _execute();
    gLog.info("Finish");
    return 0;
}