#ifndef OSGI_Launch_H
#define OSGI_Launch_H

#include "config/config.h"

#define BeginPackageOSGILaunch BeginPackage4(org,dragon,osgi,launch)
#define EndPackageOSGILaunch EndPackage4
#define OSGILaunch org::dragon::osgi::launch

BeginPackageOSGILaunch
	
	class DragonOSGI;
	class DragonOSGIFactory;

EndPackageOSGILaunch

#include "dragon.h"
#include "../framework/osgi_framework.h"
#include "DragonOSGI.h"
#include "DragonOSGIFactory.h"

#endif