#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#define _GLIBCXX_HAS_GTHREADS
#define __GTHREADS 1
#define __unix__

#include <cstring>
#include <cstdio>
#include "DaisyPlatform.h"
#include "thread.h"

namespace RNBO {
	static DaisyPlatform platformInstance;
}

#include "RNBO.h"
#include "src/RNBO_DataBuffer.cpp"
#include "src/RNBO_DataRefList.cpp"
#include "src/RNBO_CoreObject.cpp"
#include "src/RNBO_Engine.cpp"
#include "src/RNBO_ParameterInterfaceAsync.cpp"
#include "src/RNBO_ParameterInterfaceSync.cpp"
#include "src/RNBO_PatcherFactory.cpp"
#include "src/RNBO_PatcherState.cpp"

#pragma GCC diagnostic pop
#undef _GLIBCXX_HAS_GTHREADS
#undef __GTHREADS
#undef __unix__