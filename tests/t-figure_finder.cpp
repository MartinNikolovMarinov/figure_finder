#include "t-index.h"
#include "t-figure_test_data.h"

std::string debug_figuresToString(const figfind::DataType& d, i64 w, i64 h) {
    std::string result = "[yn=" + std::to_string(h) + ']' + "[xn=" + std::to_string(w) + "] {\n";
    for (i64 y = 0; y < h; y++) {
        result += " [" + std::to_string(y) + "] { ";
        for (i64 x = 0; x < w; x++) {
            result += std::to_string(d[y*w + x]) + ' ';
        }
        result += "}\n";
    }

    result += "}\n";
    return result;
}

enum struct AlgoType {
    DFS,
    BFS,
    PathCompression,
    Parallel,
};

template <AlgoType TAlgo>
i32 runFigureFinderBasicValidityTests(TestContext& ctx) {
    struct TestCase {
        const figfind::DataType& in;
        i32 w, h;
        i32 expected;
    };

    std::vector<TestCase> testCases = {
        { {}, 0, 0, 0 },
        {testData1, testData1Width, testData1Height, testData1Expected},
        {testData2, testData2Width, testData2Height, testData2Expected},
        {testData3, testData3Width, testData3Height, testData3Expected},
        {testData4, testData4Width, testData4Height, testData4Expected},
        {testData5, testData5Width, testData5Height, testData5Expected},
        {testData6, testData6Width, testData6Height, testData6Expected},
        {testData7, testData7Width, testData7Height, testData7Expected},
        {testData8, testData8Width, testData8Height, testData8Expected},
        {testData9, testData9Width, testData9Height, testData9Expected},
        {testData10, testData10Width, testData10Height, testData10Expected},
        {testData11, testData11Width, testData11Height, testData11Expected},
        {testData12, testData12Width, testData12Height, testData12Expected},

        {backwardsCompatibilityTest1, backwardsCompatibilityTest1Width, backwardsCompatibilityTest1Height, backwardsCompatibilityTest1Expected},
        {backwardsCompatibilityTest2, backwardsCompatibilityTest2Width, backwardsCompatibilityTest2Height, backwardsCompatibilityTest2Expected},
    };

    {
        ctx.startMeasure();
        defer { ctx.endMeasure(); };

        for (const auto& tc : testCases) {
            if constexpr (TAlgo == AlgoType::DFS) {
                i32 result = figfind::countFiguresDFS(tc.in, tc.w, tc.h);
                Assert(result == tc.expected, "Figure Finder DFS Algorithm Failed.");
            }
            else if constexpr (TAlgo == AlgoType::BFS) {
                i32 result = figfind::countFiguresBFS(tc.in, tc.w, tc.h);
                Assert(result == tc.expected, "Figure Finder BFS Algorithm Failed.");
            }
            else if constexpr (TAlgo == AlgoType::PathCompression) {
                i32 result = figfind::countFiguresPathCompression(tc.in, tc.w, tc.h);
                Assert(result == tc.expected, "Figure Finder Path Compression Algorithm Failed.");
            }
        }
    }

    return 0;
}

template <u64 W, u64 H, AlgoType TAlgo>
i32 runFuzzTest(TestContext& ctx, const figfind::DataType& fuzzyData, i32& result) {
    {
        ctx.startMeasure();
        defer { ctx.endMeasure(); };

        if constexpr (TAlgo == AlgoType::DFS) {
            result = figfind::countFiguresDFS(fuzzyData, W, H);
        }
        else if constexpr (TAlgo == AlgoType::BFS) {
            result = figfind::countFiguresBFS(fuzzyData, W, H);
        }
        else if constexpr (TAlgo == AlgoType::PathCompression) {
            result = figfind::countFiguresPathCompression(fuzzyData, W, H);
        }
        else if constexpr (TAlgo == AlgoType::Parallel) {
            i32 nThreads = std::thread::hardware_concurrency();
            result = figfind::countFiguresParallel(fuzzyData, W, H, nThreads);
        }
    }

    return 0;
}

template <u64 W, u64 H>
i32 runFuzzTestSuite() {
    figfind::DataType fuzzyData(W * H, false);
    for (u64 j = 0; j < W * H; j++) {
        u32 rndN = core::rndU32(0, 2);
        fuzzyData[j] = (rndN == 1) ? true : false;
    }

    i32 algo1;
    runTest(FN_NAME_TO_CPTR(runFuzzTest<AlgoType::DFS>),
            runFuzzTest<W, H, AlgoType::DFS>, fuzzyData, algo1);

    i32 algo2;
    runTest(FN_NAME_TO_CPTR(runFuzzTest<AlgoType::BFS>),
            runFuzzTest<W, H, AlgoType::BFS>, fuzzyData, algo2);

    i32 algo3;
    runTest(FN_NAME_TO_CPTR(runFuzzTest<AlgoType::PathCompression>),
            runFuzzTest<W, H, AlgoType::PathCompression>, fuzzyData, algo3);

    i32 algo4;
    runTest(FN_NAME_TO_CPTR(runFuzzTest<AlgoType::Parallel>),
            runFuzzTest<W, H, AlgoType::Parallel>, fuzzyData, algo4);

    if (algo1 != algo2) {
        std::string errMessage = "Failed to find consensus between DFS and BFS\nInput Data:\n";
        errMessage += debug_figuresToString(fuzzyData, W, H);
        Assert(false, errMessage.c_str());
    }
    else if (algo2 != algo3) {
        std::string errMessage = "Failed to find consensus between BFS and Path Compression\nInput Data:\n";
        errMessage += debug_figuresToString(fuzzyData, W, H);
        Assert(false, errMessage.c_str());
    }
    if (algo3 != algo4) {
        std::string errMessage = "Failed to find consensus between Path Compression and Parallel\nInput Data:\n";
        errMessage += debug_figuresToString(fuzzyData, W, H);
        Assert(false, errMessage.c_str());
    }

    return 0;
}

template <u64 W, u64 H>
i32 runFuzzTestParallelOnly() {
    figfind::DataType fuzzyData(W * H, false);
    for (u64 j = 0; j < W * H; j++) {
        u32 rndN = core::rndU32(0, 2);
        fuzzyData[j] = (rndN == 1) ? true : false;
    }

    i32 algo1;
    runTest(FN_NAME_TO_CPTR(runFuzzTest<AlgoType::Parallel>),
            runFuzzTest<W, H, AlgoType::Parallel>, fuzzyData, algo1);

    Assert(algo1 >= 0, "Parallel Algorithm Failed.");

    // Nothing to compare the result with, this just meassures the time for execution.

    return 0;
}

i32 runFigureFinderTestSuite() {

    runTest(FN_NAME_TO_CPTR(runFigureFinderBasicValidityTests<AlgoType::DFS>),
            runFigureFinderBasicValidityTests<AlgoType::DFS>);

    runTest(FN_NAME_TO_CPTR(runFigureFinderBasicValidityTests<AlgoType::BFS>),
            runFigureFinderBasicValidityTests<AlgoType::BFS>);

    runTest(FN_NAME_TO_CPTR(runFigureFinderBasicValidityTests<AlgoType::PathCompression>),
            runFigureFinderBasicValidityTests<AlgoType::PathCompression>);

    {
        auto runFuzzTestSuite_10x10 = []() { return runFuzzTestSuite<10, 10>(); };
        auto runFuzzTestSuite_10x15 = []() { return runFuzzTestSuite<10, 15>(); };
        auto runFuzzTestSuite_100x100 = []() { return runFuzzTestSuite<100, 100>(); };
        auto runFuzzTestSuite_100x300 = []() { return runFuzzTestSuite<100, 300>(); };
        auto runFuzzTestSuite_200x50 = []() { return runFuzzTestSuite<200, 50>(); };
        auto runFuzzTestSuite_1000x1000 = []() { return runFuzzTestSuite<1000, 1000>(); }; // 1 million elements
        auto runFuzzTestSuite_2000x1000 = []() { return runFuzzTestSuite<2000, 1000>(); }; // 2 million elements
        auto runFuzzTestSuite_1000x3000 = []() { return runFuzzTestSuite<1000, 3000>(); }; // 3 million elements
        auto runFuzzTestSuite_5000x7000 = []() { return runFuzzTestSuite<5000, 7000>(); }; // 35 million elements

        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_10x10), runFuzzTestSuite_10x10);
        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_10x15), runFuzzTestSuite_10x15);
        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_100x100), runFuzzTestSuite_100x100);
        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_100x300), runFuzzTestSuite_100x300);
        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_200x50), runFuzzTestSuite_200x50);
        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_1000x1000), runFuzzTestSuite_1000x1000);
        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_2000x1000), runFuzzTestSuite_2000x1000);
        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_1000x3000), runFuzzTestSuite_1000x3000);
        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuite_5000x7000), runFuzzTestSuite_5000x7000);
    }

    {
        // Fuzz tests for parallel work only
        auto runFuzzTestSuiteParallel_30000x35000 = []() { return runFuzzTestParallelOnly<30000, 35000>(); }; // 1 billion+ elements

        runTestSuite(FN_NAME_TO_CPTR(runFuzzTestSuiteParallel_30000x35000), runFuzzTestSuiteParallel_30000x35000);
    }

    return 0;
}
