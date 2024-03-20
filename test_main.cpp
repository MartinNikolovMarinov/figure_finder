#include <figure_finder.h>

using namespace coretypes;

#include <iostream>

using DataType = std::vector<bool>;

i32 main(i32 argc, char** argv) {
    if (!core::initCore(argc, argv)) {
        return -1;
    }
    defer { core::shutdownCore(); };

    std::vector<bool> matrix = {
        0, 1, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 1, 0, 0, 1,
        1, 1, 1, 1, 1
    };

    i32 nFigures = figfind::countFiguresPathCompression(matrix, 5, 4);
    i32 nFiguresDFS = figfind::countFiguresDFS(matrix, 5, 4);

    std::cout << "Number of figures: " << nFigures << std::endl;
    std::cout << "Number of figures: " << nFiguresDFS << std::endl;

    return 0;
}
