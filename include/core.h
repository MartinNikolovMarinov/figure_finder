#pragma once

#include "API.h"

#include "core/ansi.h"
#include "core/system_checks.h"
#include "core/types.h"
#include "core/utils.h"

namespace core {

FIGURE_FINDER_API_EXPORT bool initCore(coretypes::i32 argc, char** argv);
FIGURE_FINDER_API_EXPORT void shutdownCore();

} // namespace core
