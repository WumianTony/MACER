#ifndef A51D1620_27C8_49B9_8DE5_650E276861EB
#define A51D1620_27C8_49B9_8DE5_650E276861EB

#include "config.h"
#include "logger.h"

namespace Config = Macer::Class::Config;
namespace Logger = Macer::Class::Logger;
namespace Mumu   = Macer::Platf::Mumu;
namespace System = Macer::Platf::System;

#define gCfg Config::getInstance()
#define gLog Logger::getInstance()

#endif /* A51D1620_27C8_49B9_8DE5_650E276861EB */