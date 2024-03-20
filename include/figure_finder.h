#pragma once

#include <core.h>

#include <vector>
#include <string>

namespace figfind {

using namespace coretypes;

using DataType = std::vector<bool>;

/**
 * @brief Count the number of figures in the given grid using depth-first search.
 *
 * @param figures The grid of figures.
 * @param w The width of the grid.
 * @param h The height of the grid.
 *
 * @return The number of figures in the grid.
*/
FIGURE_FINDER_API_EXPORT i32 countFiguresDFS(const DataType& figures, i64 w, i64 h);

/**
 * @brief Count the number of figures in the given grid using breadth-first search.
 *
 * @param figures The grid of figures.
 * @param w The width of the grid.
 * @param h The height of the grid.
 *
 * @return The number of figures in the grid.
*/
FIGURE_FINDER_API_EXPORT i32 countFiguresBFS(const DataType& figures, i64 w, i64 h);

/**
 * @brief Count the number of figures in the given grid using a variant of Disjoint Set Union (aka. union find) with
 *        path compression.
 *
 * @param figures The grid of figures.
 * @param w The width of the grid.
 * @param h The height of the grid.
 *
 * @return The number of figures in the grid.
*/
FIGURE_FINDER_API_EXPORT i32 countFiguresPathCompression(const DataType& figures, i64 w, i64 h);

/**
 * @brief Count the number of figures in the given grid in parallel.
 *
 * @param figures The grid of figures.
 * @param w The width of the grid.
 * @param h The height of the grid.
 * @param nThreads The number of threads to use.
 *
 * @return The number of figures in the grid.
*/
FIGURE_FINDER_API_EXPORT i32 countFiguresParallel(const DataType& figures, i64 w, i64 h, u32 nThreads);

} // namespace figfind
