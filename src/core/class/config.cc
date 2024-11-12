#include "config.h"

#include <iostream>
#include <fstream>
#include "logger.h"
#include "system.h"

namespace Macer {
namespace Class {
using json = nlohmann::json;

static json load(const char* path) {
    std::ifstream fin(path);
    if (fin.is_open()) {
        json j = json::parse(fin);
        fin.close();
        return j;
    }
}

static void save(const char* path, const json j) {
    std::ofstream fout(path);
    if (fout.is_open()) {
        fout << j.dump(4);
        fout.close();
    }
}

Config::Config() {
    try {
        json j = kdefault;
        // 创建配置并保存
        if (!System::isPathValid(kDirPath)) {
            System::createPath(kDirPath);
            save(kCfgPath, j);
        } else { // 更新配置，有更改就保存
            json user_j = load(kCfgPath);
            j.update(user_j);
            if (j != user_j) {
                save(kCfgPath, j);
            }
        }
        // 解析并补全其他配置
        time.parse(j);
        path.loadLocals();

    } catch (...) {
        std::cerr << "配置加载出现问题" << std::endl;
        exit(1);
    }
}

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

void Config::printDebugMessage() {
#define PRINT_CONFIG(x) << #x" = " << c.x << std::endl
    const auto& c = get();
    std::cerr << "Config: " << std::endl
        PRINT_CONFIG(time.rox_start)
        PRINT_CONFIG(time.login)
        PRINT_CONFIG(time.loading)
        // PRINT_CONFIG(path.rox)
        PRINT_CONFIG(path.self)
        PRINT_CONFIG(path.cache.self)
        PRINT_CONFIG(path.cache.log)
        PRINT_CONFIG(path.cache.data)
        PRINT_CONFIG(path.cache.image)
        PRINT_CONFIG(path.cache.images)
        PRINT_CONFIG(path.resource.self)
        PRINT_CONFIG(path.resource.image)
        PRINT_CONFIG(path.resource.images)
    ;
#undef PRINT_CONFIG
}
}
}