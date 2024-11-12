#include "global.h"

Utils::Logger::createInstance(
    gCfg.path.cache.log, 
    Utils::Logger::Level::kDebug, 
    [](const std::string& message) {
        std::cerr << message << std::endl;
    }
);