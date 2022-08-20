#pragma once

/*
* PRECOMPILED HEADER FILE
* <Project> -> Properties -> C/C++ -> Precompiled Headers
* The purpose of the file is to speed up the build process. Any stable header files, 
* for example Standard Library headers such as <vector>, should be included here. 
* The precompiled header is compiled only when it, or any files it includes, are modified. 
* If you only make changes in your project source code, the build will skip compilation for the precompiled header.
*/
#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Hazel/Log.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
