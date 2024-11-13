#include "mumu.h"
#include "global.h"

#include <cstdio>
#include <sstream>

namespace Macer {
namespace Platf {
namespace Mumu {

// 递归拆解
template<>
void _append(std::stringstream& ss) {
    return; // 递归终止
}

// 迭代
template<typename T, typename... Args>
void _append(std::stringstream& ss, T arg, Args... rest) {
    ss << ' ' << arg;
    _append(ss, rest...);
}

// 封装指令，并返回状态值
template<typename... Args>
int _MumuManager(Args... args) {
    std::stringstream cmd(gCfg.path.mumu.manager);
    _append(cmd, args...); // 加空格，依次放入 ss
    return system(cmd.str().c_str());
}

// 封装指令，并返回完整结果
template<typename... Args>
std::string _MumuManager_Full(Args... args) {
    std::stringstream cmd(gCfg.path.mumu.manager);
    _append(cmd, args...); // 加空格，依次放入 ss

    std::array<char, 128> buffer;
    std::string output;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.str().c_str(), "r"), pclose);
    if (!pipe) {
        gLog.error("Popen 失败了");
        return "";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        output += buffer.data();
    }
    return output;
}

// mumumanager api -v 0 player_state
bool isRunning() {
    return _MumuManager("api -v", gCfg.mumu.device, "player_state") == 0;
}

// mumumanager api -v 0 app_state com.zlongame.cn.ro
bool isRoxRunning() {
    return _MumuManager_Full("api -v", gCfg.mumu.device, "app_state", gCfg.mumu.package).find("state=running") != std::string::npos;
}

// mumumanager control -v 0 launch
// taskkill /f /im adb.exe
// adb start-server
// adb connect 127.0.0.1:16384
void start() {
    _MumuManager("control -v", gCfg.mumu.device, "launch");
    system("taskkill /f /im adb.exe");
    system("adb start-server");
    system("adb connect 127.0.0.1:16384");
}

// mumumanager control -v 0 app launch -pkg com.zlongame.cn.ro
void launchRox() {
    _MumuManager("control -v", gCfg.mumu.device, "app launch -pkg", gCfg.mumu.package);
}

// 废弃 mumumanager control -v 0 tool func -n screenshot
// mumumanager adb -v 0 -c shell screencap -p /sdcard/test.png
// mumumanager adb -v 0 -c pull /sdcard/test.png Path/To/Cache
void screenshot() {
    // _MumuManager("control -v", gCfg.mumu.device, "tool func -n screenshot");
    _MumuManager("adb -v", gCfg.mumu.device, "shell screencap -p", gCfg.path.mumu.screenshot);
    _MumuManager("adb -v", gCfg.mumu.device, "pull", gCfg.path.mumu.screenshot, gCfg.path.cache.images["screenshot"]);
}

// mumumanager adb -v 0 -c "shell input tap X Y"
void click(int x, int y) {
    _MumuManager("adb -v", gCfg.mumu.device, "shell input tap", x, y)
}

} // namespace Mumu
} // namespace Platf
} // namespace Macer