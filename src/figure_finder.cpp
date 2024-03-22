#include <figure_finder.h>

#include <queue>
#include <stack>
#include <thread>
#include <unordered_map>
#include <unordered_set>

namespace figfind {

#pragma region DFS Implementation

namespace {

void dfs(const DataType& figures, i64 w, i64 h, std::vector<std::vector<bool>>& visited, i64 startX, i64 startY) {
    std::stack<std::pair<i64, i64>> stack;
    stack.push({startX, startY});

    while (!stack.empty()) {
        auto p = stack.top();
        auto x = p.first;
        auto y = p.second;
        stack.pop();

        const bool isOutOfBounds = x < 0 || x >= w || y < 0 || y >= h;
        if (isOutOfBounds) {
            continue;
        }

        const bool alreadyVisited = visited[x][y];
        const bool isNotFigure = !figures[y * w + x];
        if (alreadyVisited || isNotFigure) {
            continue;
        }

        visited[x][y] = true;

        // Push adjacent cells onto the stack
        stack.push({x + 1, y}); // Right
        stack.push({x - 1, y}); // Left
        stack.push({x, y + 1}); // Down
        stack.push({x, y - 1}); // Up
    }
}

} // namespace

i32 countFiguresDFS(const DataType& figures, i64 w, i64 h) {
    i32 figureCount = 0;
    std::vector<std::vector<bool>> visited(w, std::vector<bool>(h, false));

    for (i64 x = 0; x < w; x++) {
        for (i64 y = 0; y < h; y++) {
           if (figures[y * w + x] && !visited[x][y]) {
                dfs(figures, w, h, visited, x, y);
                ++figureCount;
           }
        }
    }

    return figureCount;
}

#pragma endregion

#pragma region BFS Implementation

namespace {

void bfs(const DataType& figures, i64 w, i64 h, std::vector<std::vector<bool>>& visited, i64 startX, i64 startY) {
    std::queue<std::pair<i64, i64>> queue;
    queue.push({startX, startY});

    while (!queue.empty()) {
        auto p = queue.front();
        auto x = p.first;
        auto y = p.second;
        queue.pop();

        const bool isOutOfBounds = x < 0 || x >= w || y < 0 || y >= h;
        if (isOutOfBounds) {
            continue;
        }

        const bool alreadyVisited = visited[x][y];
        const bool isNotFigure = !figures[y * w + x];
        if (alreadyVisited || isNotFigure) {
            continue;
        }

        visited[x][y] = true;

        // Push adjacent cells onto the queue
        queue.push({x + 1, y}); // Right
        queue.push({x - 1, y}); // Left
        queue.push({x, y + 1}); // Down
        queue.push({x, y - 1}); // Up
    }
}

} // namespace

i32 countFiguresBFS(const DataType& figures, i64 w, i64 h) {
    i32 figureCount = 0;
    std::vector<std::vector<bool>> visited(w, std::vector<bool>(h, false));

    for (i64 x = 0; x < w; x++) {
        for (i64 y = 0; y < h; y++) {
           if (figures[y * w + x] && !visited[x][y]) {
                bfs(figures, w, h, visited, x, y);
                ++figureCount;
           }
        }
    }

    return figureCount;
}

#pragma endregion

#pragma region Path Comporession

namespace {

i32 pathCompression(i32* markings, i64 w, i64 h, bool normalize = false) {
    auto reconcileRoots = [](std::unordered_map<i32, i32>& m, i32 leftRoot, i32 topRoot, i32& curr) {
        // This code creates connections between the roots of the current cell's left and top neighbors.
        // It also compresses the path to the root for each figure

        while (m.find(leftRoot) != m.end() && m[leftRoot] != topRoot) {
            leftRoot = m[leftRoot];
        }
        while (m.find(topRoot) != m.end() && m[topRoot] != leftRoot) {
            topRoot = m[topRoot];
        }

        if (leftRoot != topRoot) {
            if (auto it = m.find(topRoot); it != m.end()) {
                // Prevent cycles in the path:
                if (it->second != leftRoot) {
                    m[leftRoot] = topRoot;
                }
                else {
                    topRoot = leftRoot;
                }
            }
            else {
                m[leftRoot] = topRoot;
            }
        }

        curr = topRoot; // Set current cell's root to the reconciled root
    };

    i32* currRow = markings;
    i32* rowAbove = markings - w;

    i32 counter = 1; // Unique identifier for each figure found
    std::unordered_map<i32, i32> figureConnections; // Map to reconcile figure identifiers

    for (i64 y = 0; y < h; y++) {
        for (i64 x = 0; x < w; x++, currRow++, rowAbove++) {
            if (*currRow == 0) continue; // Skip non-figure cells

            i32 leftNeighbor = 0;
            if (x > 0 && *(currRow - 1) != 0) leftNeighbor = *(currRow - 1);

            i32 topNeighbor = 0;
            if (y > 0 && *rowAbove != 0) topNeighbor = *rowAbove;

            // Determine the root for the current cell based on its neighbors
            if (leftNeighbor != 0) {
                *currRow = leftNeighbor;
                if (topNeighbor != 0 && leftNeighbor != topNeighbor) {
                    // Reconcile differing neighbor roots
                    reconcileRoots(figureConnections, leftNeighbor, topNeighbor, *currRow);
                }
            }
            else if (topNeighbor != 0) {
                *currRow = topNeighbor;
            }
            else {
                // New, uniquely identified figure
                counter++;
                *currRow = counter;
            }
        }
    }

    auto normalizeMarkings = [](i32* curr, i64 _w, i64 _h, std::unordered_map<i32, i32>& m) {
        // Every mark that is not a root is replaced with its root.
        const i32* end = curr + _w * _h;
        while (curr != end) {
            i32 v = *curr;
            if (v > 0) {
                auto it = m.find(v);
                while (it != m.end()) {
                    v = it->second;
                    it = m.find(v);
                }
                *curr = v;
            }
            curr++;
        }
    };

    if (normalize) {
        normalizeMarkings(markings, w, 1, figureConnections); // normalize first row
        normalizeMarkings(markings + w * (h - 1), w, 1, figureConnections); // normalize last row
    }

    i32 res = counter - 1 - i32(figureConnections.size());
    return res;
}

} // namespace

i32 countFiguresPathCompression(const DataType& figures, i64 w, i64 h) {
    std::vector<i32> markings(w * h, 0);
    for (i64 y = 0; y < h; y++) {
        for (i64 x = 0; x < w; x++) {
            markings[y * w + x] = figures[y * w + x];
        }
    }

    i32 nFigures = pathCompression(markings.data(), w, h);
    return nFigures;
}

#pragma endregion

#pragma region Parallel Implementation

i32 countFiguresParallel(const DataType& figures, i64 w, i64 h, u32 nThreads) {
    bool useSingleThread = nThreads <= 1;
    bool hightTooSmallForParallelism = h < i64(nThreads);

    if (useSingleThread || hightTooSmallForParallelism) {
        return countFiguresPathCompression(figures, w, h);
    }

    constexpr u32 MAX_THREADS_ALGORITHM_SUPPORTS = 32; // The marge section of the algorithms supports up to 32 chunks.
    const u32 MAX_THREADS = (std::thread::hardware_concurrency() < MAX_THREADS_ALGORITHM_SUPPORTS) ?
                                MAX_THREADS_ALGORITHM_SUPPORTS :
                                std::thread::hardware_concurrency();
    if (nThreads > MAX_THREADS) {
        nThreads = MAX_THREADS;
    }

    std::vector<i32> markings(w * h, 0);
    for (i64 y = 0; y < h; y++) {
        for (i64 x = 0; x < w; x++) {
            markings[y * w + x] = figures[y * w + x];
        }
    }

    // The work is divided into chunks based on the hight of the input set, each of which is processed by a separate
    // thread. This approach to splitting is great for memory locality and cache coherency, but for extreamley large
    // input it may be better to split into square chunks by the width and the height.
    const i64 chunkHeight = h / i64(nThreads);

    std::vector<std::thread> threads (nThreads);
    std::vector<i32> results (nThreads, 0);

    for (i32 i = 0; i < i32(nThreads); i++) {
        auto work = [&results, &markings, i, nThreads, w, h, chunkHeight]() {
            i64 currChunkHeight = h / i64(nThreads);
            bool lastChunk = (i == i32(nThreads) - 1);
            if (lastChunk) {
                currChunkHeight = h - (i64(nThreads) - 1) * currChunkHeight;
            }

            i32* chunkStartPtr = markings.data() + i * w * chunkHeight;
            results[i] = pathCompression(chunkStartPtr, w, currChunkHeight, true);
        };

        // Spawn thread
        threads[i] = std::thread(work);
        // work();
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    i32 nFigures = 0;
    for (auto res : results) {
        nFigures += res;
    }

    /**
     * IMPORTANT: This comment explains why the algorithm is capped to 32 threads?
     *
     * The following code merges the results from the parallel processed chunks. It works by connecting the last row of
     * chunk i with the first row of the chunk i+1.
     *
     * In order to do this, the following conditions must be met:
     *      0. The markings vector must have normalized rows at the top and bottom of each chunk.
     *      1. Each figure must be uniquely identified across all chunks.
     *      2. Each identifier in figure i must be smaller than the identifier in figure i+1.
     *
     * Point 0 is achieved by the pathCompression function, when the normalize parameter is set to true.
     *
     * Point 1 and 2 create a nasty problem - the seperately processed chunks have their own "local" figure identifiers,
     * which will overlap with the identifiers of the other chunks.
     *
     * To address this problem an "offset per chunk" variable is introduced. Adding this variable to the current chunk
     * figure "local" identifier will create a new "global" identifier.
     *
     * Example:
     *
     * Lets say we have 3 chunks and the following "local" figure identifiers:
     *
     * chunk 0: { 2, 3, 4, 5 }
     * chunk 1: { 3, 4, 8 }
     * chunk 2: { 2, 3 }
     *
     * And lets say "offset per chunk" = 10000, then the "global" figure identifiers will be:
     *
     * chunk 0: { 10002, 10003, 10004, 10005 }
     * chunk 1: { 20003, 20004, 20008 }
     * chunk 2: { 30002, 30003 }
     *
     * Adding the offset introduces the risk of figure identifier overflow beyond the 32-bit integer limit. To prevent
     * this, we employ 64-bit integers for "global" identifiers, allocating the upper 32 bits for chunk-specific offsets.
     * This allocation strategy consumes 1 bit of the number space for each chunk, setting a hard limit of 32 chunks.
     * Beyond this threshold, the available precision for "local" identifiers drops below 32 bits, making overlaps
     * possible again. Consequently, this limitation also restricts the maximum number of processing threads to 32.
     *
     * TODO: Avenues to explore to remove the 32 thread limitation:
     *    1. Use a big integer for a wider range of numbers.
     *    2. Use some kind of hashing to map the "local" identifiers to a wider range.
    */
    {
        i64 offsetPerChunk = i64(core::MAX_I64 / nThreads);
        std::unordered_map<i64, i64> chunkBoundaryConnections; // Map to reconcile figures at chunk boundaries.

        for (i32 c = 0; c < i32(nThreads) - 1; c++) {
            i32* bottomPtr = markings.data() + w * chunkHeight * (c + 1);
            i32* topPtr = bottomPtr - w;

            i64 topOffset = i64(c) * offsetPerChunk;
            i64 bottomOffset = topOffset + offsetPerChunk;

            for (i32 x = 0; x < w; x++, topPtr++, bottomPtr++) {
                i64 top = i64(*topPtr);
                i64 bottom = i64(*bottomPtr);

                if (top == 0 || bottom == 0) continue;

                top += topOffset;
                bottom += bottomOffset;

                while (top != bottom) {
                    i64& higher = top > bottom ? top : bottom;
                    i64& lower = top > bottom ? bottom : top;

                    auto it = chunkBoundaryConnections.find(higher);
                    if (it != chunkBoundaryConnections.end() && it->second != lower) {
                        // Some figures may overlap between chunks.
                        // There might be a chain of connections, so we need to follow it to the end.
                        higher = it->second;
                    }
                    else {
                        // Create a connection between the two figures
                        chunkBoundaryConnections[higher] = lower;
                        break;
                    }
                }
            }
        }

        nFigures -= i32(chunkBoundaryConnections.size());
    }

    return nFigures;
}

#pragma endregion

} // namespace figfind

