#ifndef DAFF9627_8D19_431D_9B7F_1DE35557CB07
#define DAFF9627_8D19_431D_9B7F_1DE35557CB07

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class Config {
  
public:
    static Config& get(); // 单例
    static void printDebugMessage(); // 打印所有配置
    
    struct { // path
        std::string self;
        // std::string rox;
        std::string mumu;

        struct { // cache
            std::string self;
            std::string log;
            std::string data;
            std::string image;
            std::vector<std::string> images;
        } cache;
        
        struct { // resource
            std::string self;
            std::string image;
            std::vector<std::string> images;
        } resource;

        inline void loadLocals() {
            this.self = System::getLocalPath();
            // this.rox = System::getFilePath("RagnarokX.exe")
            this.mumu = System::getFilePath("MumuManager.exe")
            this.cache.self = this.self + "./cache";
            this.cache.log = this.cache.self + "/log";
            this.cache.data = this.cache.self + "/data";
            this.cache.image = this.cache.self + "/image";
            this.cache.images = System::getFiles(this.cache.image);
            this.resource.self = this.self + "./resource";
            this.resource.image = this.resource.self + "/image";
            this.resource.images = System::getFiles(this.resource.image);
            if (!System::isPathValid(this.cache.self)) {
                System::createPath({
                    this.cache.self,
                    this.cache.log,
                    this.cache.data,
                    this.cache.image,
                    this.resource.self,
                    this.resource.image
                });
            }
        };
    } path;
    
    struct { // time
        int rox_start;
        int login;
        int loading;
        
        inline void parse(json j) {
            this.rox_start = j["time"]["rox_start"];
            this.login = j["time"]["login"];
            this.loading = j["time"]["loading"];
        }
        
        inline json parse() {
            return {
                "time", {
                    {"rox_start", this.rox_start},
                    {"login", this.login},
                    {"loading", this.loading}
                }
            };
        }
    } time;

private:
    Config();
    static constexpr char kDirPath[] = "/config";
    static constexpr char kCfgPath[] = "/config/config.json";
    static constexpr json kDefault = {
        "time", {
            {"rox_start", 21},
            {"login", 3},
            {"loading", 5}
        }
    };
};

#endif /* DAFF9627_8D19_431D_9B7F_1DE35557CB07 */