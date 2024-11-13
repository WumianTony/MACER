#include "config.h"

#include <iostream>
#include <fstream>
#include "logger.h"
#include "system.h"

namespace Macer {
namespace Class {

json _load(const char* path) {
    std::ifstream fin(path);
    if (fin.is_open()) {
        json j = json::parse(fin);
        fin.close();
        return j;
    }
}

void _save(const char* path, const json j) {
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
            _save(kCfgPath, j);
        } else { // 更新配置，有更改就保存
            json user_j = _load(kCfgPath);
            j.update(user_j);
            if (j != user_j) {
                _save(kCfgPath, j);
            }
        }
        // 解析并补全其他配置
        path.loadLocals();
        time.parse(j["time"]);
        mumu.parse(j["mumu"]);
        option.loadDefault();
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

void Config::Path::loadLocals() {
    this->self = System::getLocalPath();
    // this->rox = System::getFilePath("RagnarokX.exe")
    this->mumu.manager = System::getFilePath("MumuManager.exe")
    this->mumu.screenshot = "/sdcard/screenshot.png"
    this->cache.self = this->self + "./cache";
    this->cache.log = this->cache.self + "/log";
    this->cache.data = this->cache.self + "/data";
    this->cache.image = this->cache.self + "/image";
    this->cache.images["screenshot"] = this->cache.image + "/screenshot.png";
    this->resource.self = this->self + "./resource";
    this->resource.image = this->resource.self + "/image";
    this->resource.images = System::getFiles(this->resource.image);
    if (!System::isPathValid(this->cache.self)) {
        System::createPath({
            this->cache.self,
            this->cache.log,
            this->cache.data,
            this->cache.image,
            this->resource.self,
            this->resource.image
        });
    }
}

void Config::Time::parse(const json& j) {
    this->rox_start = j["rox_start"];
    this->login = j["login"];
    this->loading = j["loading"];
}

json Config::Time::dump() const {
    return {
        "time", {
            {"rox_start", this->rox_start},
            {"login", this->login},
            {"loading", this->loading}
        }
    };
}

void Config::Mumu::parse(const json& j) {
    this->package = j["package"];
    this->device = j["device"];
}

json Config::Mumu::dump() const {
    return {
        "mumu", {
            {"package", this->package},
            {"device", this->device}
        }
    };
}

//       启动项 默认值 其他选项
//      -debug false  /true
// 不写 -platf mumu   /windows
// 不写 -dvice 0      /1/2/3/4
//      -daily true   /false
//      -profs none   /farm/fish/mine
//      -grind true   /false
// 待定 -mrket true   /false
bool _strToBool(const std::string& value) {
    if (value == "true") {
        return true;
    }
    return false;
}

void Option::loadDefault() {
    this->debug = false;
    this->daily = true;
    this->grind = true;
    this->market = true;
    this->profession = Profession::kNone;
}

void Option::parse(int argc, char** argv) {
    for (int i = 1; i + 1 < argc; i += 2) {
        std::string key = argv[i], value = argv[i + 1];
        if (key == "-debug") {
            this->debug = _strToBool(value);
        } else if (key == "-daily") {
            this->daily = _strToBool(value);
        } else if (key == "-grind") {
            this->grind = _strToBool(value);
        } else if (key == "-mrket") {
            this->market = _strToBool(value);
        } else if (key == "-profs") {
            if (value == "farm") {
                this->profession = Profession::kFarm;
            } else if (value == "fish") {
                this->profession = Profession::kFish;
            } else if (value == "mine") {
                this->profession = Profession::kMine;
            } else {
                this->profession = Profession::kNone;
            }
        }
    }
}

} // namespace Class
} // namespace Macer