#ifndef A51D1620_27C8_49B9_8DE5_650E276861EB
#define A51D1620_27C8_49B9_8DE5_650E276861EB

#include "config.h"
#include "logger.h"
#include "mumu.h"
#include "system.h"
#include "visual.h"
#include "module.h"

#define gConfig Macer::Class::Config
#define gLogger Macer::Class::Logger
#define gMumu   Macer::Platf::Mumu
#define gSystem Macer::Platf::System
#define gVisual Macer::Utils::Visual
#define gLogin  Macer::Modul::Login

#define gCfg gConfig::getInstance()
#define gLog gLogger::getInstance()

namespace Macer {

namespace Class {
    class Config;
    class Logger;
}

namespace Platf {
    namespace Mumu   {}
    namespace System {}
}

namespace Utils {
    namespace Visual {}
}

namespace Modul {
    namespace Login  {}
}
}

#endif /* A51D1620_27C8_49B9_8DE5_650E276861EB */