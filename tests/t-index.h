#pragma once

#include "rnd.h"

#include <figure_finder.h>

#include <iostream>
#include <chrono>
#include <thread>

using namespace coretypes;

inline i32 g_testCount = 0;

#define FN_NAME_TO_CPTR(test) #test

template <typename TSuite>
i32 runTestSuite(std::string_view suiteName, TSuite suite) {
    std::cout << "[SUITE RUNNING] " << suiteName.data() << std::endl;
    i32 ret = suite();
    std::cout << "[SUITE " << (ret == 0 ? "PASSED" : "FAILED") << "] " << suiteName.data() << std::endl;
    return ret;
}

struct TestContext {
    std::chrono::steady_clock::time_point beginTime;
    std::chrono::duration<f64> deltaTime;

    void startMeasure();
    void endMeasure();

    std::string timeTakenByTest() const;
};

template <typename TTest, typename... TArgs>
i32 runTest(std::string_view testName, TTest test, TArgs&&... args) {
    g_testCount++;
    std::cout << "\t[TEST " << "№ " << g_testCount << " RUNNING] " << testName.data() << "\n";

    TestContext ctx = {};
    i32 ret = test(ctx, std::forward<TArgs>(args)...);

    std::cout << "\t[TEST " << "№ " << g_testCount << " "
              << (ret == 0 ? "PASSED" : "FAILED") << "] "
              << testName.data()
              << " [ Time: " << ctx.timeTakenByTest().data() << " ]"
              << std::endl;

    return ret;
}

i32 runFigureFinderTestSuite();

i32 runAllTests();
