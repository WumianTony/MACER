#ifndef DAFF9627_8D19_431D_9B7F_1DE35557CB07
#define DAFF9627_8D19_431D_9B7F_1DE35557CB07

#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

namespace Macer {
namespace Class {
using json = nlohmann::json;

class Config {
public:
    static Config& getInstance(); // 单例
    static void printDebugMessage(); // 打印所有配置
    
    using umap_s_to_s = std::unordered_map<std::string, std::string>;
    struct Path {
        std::string self;
        // std::string rox;
        struct Mumu {
            std::string manager;
            std::string screenshot;
        } mumu;

        struct Cache {
            std::string self;
            std::string log;
            std::string data;
            std::string image;
            umap_s_to_s images;
        } cache;
        
        struct Resource {
            std::string self;
            std::string image;
            umap_s_to_s images;
        } resource;

        void loadLocals();
    } path;
    
    struct Time {
        int mumu_start;
        int rox_start;
        int login;
        int loading;

        void parse(const json& j);
        json dump() const;
    } time;

    struct Mumu {
        std::string package;
        int device;

        void parse(const json& j);
        json dump() const;
    } mumu;

    struct Option {
        bool debug;
        bool daily;
        bool grind;
        bool market;
        // int device;
        
        // enum class Platform {
        //     kWindows = 0,
        //     kMumu
        // } platform;
        
        enum class Profession {
            kNone = 0,
            kFarm,
            kFish,
            kMine
        } profession;
        
        void loadDefault();
        void parse(int argc, const char* const* argv);
    } option;

private:
    Config();
    // 默认路径与配置
    static constexpr char kDirPath[] = "/config";
    static constexpr char kCfgPath[] = "/config/config.json";
    static json kDefault;
    static void printConfig();
    
}; // class Config
} // namespace Class
} // namespace Macer

#endif /* DAFF9627_8D19_431D_9B7F_1DE35557CB07 */