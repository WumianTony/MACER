#include "module.h"

#include "global.h"

namespace Macer {
namespace Modul {
namespace Login {

void run() {
    if (!gMumu::isRunning()) {
        gMumu::start();
        gSystem::sleep(gCfg.time.mumu_start);
    }

    if (!gMumu::isRoxRunning()) {
        gMumu::launchRox();
        gSystem::sleep(gCfg.time.rox_start);
    }

    gMumu::screenshot();
    auto p = gVisual::findPos(
        gCfg.path.cache.images["screenshot"],
        gCfg.path.resource.images["login_button"]
    );
    if (p.x >= 0 && p.y >= 0) {
        gMumu::click(p.x, p.y);
        gSystem::sleep(gCfg.time.login);
    }

    gMumu::screenshot();
    p = gVisual::findPos(
        gCfg.path.cache.images["screenshot"],
        gCfg.path.resource.images["start_button"]
    );
    if (p.x >= 0 && p.y >= 0) {
        gMumu::click(p.x, p.y);
        gSystem::sleep(gCfg.time.loading);
    }
}

}
}
}