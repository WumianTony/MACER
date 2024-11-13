#include "module.h"

#include "global.h"

namespace Macer {
namespace Module {
namespace Login {

void run() {
    if (!Mumu::isRunning()) {
        Mumu::start();
        System::sleep(gCfg.time.mumu_start);
    }

    if (!Mumu::isRoxRunning()) {
        Mumu::launchRox();
        System::sleep(gCfg.time.rox_start);
    }

    Mumu::screenshot();
    auto p = Visual::findPos(
        gCfg.path.cache.images["screenshot"],
        gCfg.path.resource.images["login_button"]
    );
    if (p.x >= 0 && p.y >= 0) {
        Mumu::click(p.x, p.y);
        System::sleep(gCfg.time.login);
    }

    Mumu::screenshot();
    auto p = Visual::findPos(
        gCfg.path.cache.images["screenshot"],
        gCfg.path.resource.images["start_button"]
    );
    if (p.x >= 0 && p.y >= 0) {
        Mumu::click(p.x, p.y);
        System::sleep(gCfg.time.start);
    }
}

}
}
}