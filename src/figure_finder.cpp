#include <figure_finder.h>

#include <stack>
#include <unordered_map>

namespace figfind {

namespace {

void dfs(const DataType& figures, i64 w, i64 h, std::vector<std::vector<bool>>& visited, i64 startX, i64 startY);
i32 pathCompression(std::vector<i32>& markings, i64 w, i64 h);

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

i32 countFiguresPathCompression(const DataType& figures, i64 w, i64 h) {
    std::vector<i32> markings(w * h, 0);

    for (i64 y = 0; y < h; y++) {
        for (i64 x = 0; x < w; x++) {
            markings[y * w + x] = figures[y * w + x];
        }
    }

    i32 nFigures = pathCompression(markings, w, h);

    // // TODO: Remove this, DEBUG: Print markings
    // for (i64 y = 0; y < h; y++) {
    //     for (i64 x = 0; x < w; x++) {
    //         std::cout << markings[y * w + x] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return nFigures;
}

namespace {

void dfs(const DataType& figures, i64 w, i64 h, std::vector<std::vector<bool>>& visited, i64 startX, i64 startY) {
    std::stack<std::pair<i64, i64>> stack;
    stack.push({startX, startY});

    while (!stack.empty()) {
        auto p = stack.top();
        auto x = p.first;
        auto y = p.second;
        stack.pop();

        if (x < 0 || x >= w || y < 0 || y >= h || !figures[y * w + x] || visited[x][y]) {
            continue;
        }

        visited[x][y] = true;

        // Push adjacent cells onto the stack
        stack.push({x + 1, y});
        stack.push({x - 1, y});
        stack.push({x, y + 1});
        stack.push({x, y - 1});
    }
}

i32 pathCompression(std::vector<i32>& markings, i64 w, i64 h) {
    i32* current = markings.data();
    i32* rowAbove = markings.data() - w;

    i32 counter = 1; // Unique identifier for each figure found
    std::unordered_map<i32, i32> rootConnections; // Map to reconcile figure identifiers

    auto reconcileRoots = [](std::unordered_map<i32, i32>& recMap, i32 leftRoot, i32 topRoot, i32& curr) {
        // Compress the path

        while (recMap.find(leftRoot) != recMap.end() && recMap[leftRoot] != topRoot) {
            leftRoot = recMap[leftRoot];
        }
        while (recMap.find(topRoot) != recMap.end() && recMap[topRoot] != leftRoot) {
            topRoot = recMap[topRoot];
        }

        // Union the disjoint sets

        if (leftRoot != topRoot) {
            recMap[leftRoot] = topRoot;
        }

        curr = topRoot; // Set current cell's root to the reconciled root
    };

    for (i64 y = 0; y < h; y++) {
        for (i64 x = 0; x < w; x++, current++, rowAbove++) {
            if (*current == 0) continue; // Skip non-figure cells

            i32 leftNeighbor = 0, topNeighbor = 0;
            if (x > 0 && *(current - 1) != 0) leftNeighbor = *(current - 1);
            if (y > 0 && *rowAbove != 0) topNeighbor = *rowAbove;

            // Determine the root for the current cell based on its neighbors
            if (leftNeighbor != 0) {
                *current = leftNeighbor;
                if (topNeighbor != 0 && leftNeighbor != topNeighbor) {
                    // Reconcile differing neighbor roots
                    reconcileRoots(rootConnections, leftNeighbor, topNeighbor, *current);
                }
            }
            else if (topNeighbor != 0) {
                *current = topNeighbor;
            }
            else {
                // New, uniquely identified figure
                counter++;
                *current = counter;
            }
        }
    }

    return counter - 1 - i32(rootConnections.size());
}

} // namespace

} // namespace figfind

