#ifndef Dragon_OSGI_H
#define Dragon_OSGI_H
#pragma once

#define DRAGON_HEADER_BUILD
//#define MEM_CHECK

#include "dragon.h"

#include "org/dragon/osgi/framework/osgi_framework.h"
#include "org/dragon/osgi/internal/osgi_internal.h"
#include "org/dragon/osgi/launch/osgi_launch.h"

#ifdef DRAGON_OSGI_STATIC_LIB
#	pragma comment(lib,"DragonOSGI_S.lib") 
#elif !defined NDEBUG
#	pragma comment(lib,"DragonOSGI_D.lib")
#else
#	pragma comment(lib,"DragonOSGI.lib")
#endif

Import org::dragon::osgi::framework;
Import org::dragon::osgi::internal;
Import org::dragon::osgi::launch;


#endif