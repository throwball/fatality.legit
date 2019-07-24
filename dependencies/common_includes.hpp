#pragma once

#include <windows.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <array>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <intrin.h>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "utilities/singleton.hpp"
#include "utilities/fnv.hpp"
#include "../source-sdk/misc/color.hpp"
#include "utilities/utilities.hpp"
#include "interfaces/i_trace.hpp"
#include "utilities/render.hpp"
#include "utilities/hook.hpp"
#include "interfaces/interfaces.hpp"
#include "math/math.hpp"
#include "utilities/netvars.hpp"

#include "../source-sdk/sdk.hpp"
#include "../core/hooks/hooks.hpp"
#include "../core/menu/config/config.hpp"