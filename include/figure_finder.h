#pragma once

#include <core.h>

#include <vector>

namespace figfind {

using namespace coretypes;

using DataType = std::vector<bool>;

FIGURE_FINDER_API_EXPORT i32 countFiguresDFS(const DataType& figures, i64 w, i64 h);
FIGURE_FINDER_API_EXPORT i32 countFiguresPathCompression(const DataType& figures, i64 w, i64 h);

} // namespace figfind
