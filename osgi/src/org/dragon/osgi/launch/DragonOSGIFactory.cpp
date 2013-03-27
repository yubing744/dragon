#include "DragonOSGIFactory.h"

Import OSGILaunch;

P<Framework> DragonOSGIFactory::newFramework(P<Map<String,String>> configuration)
{
	return new DragonOSGI(configuration);
}
