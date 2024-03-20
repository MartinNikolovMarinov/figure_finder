#include "t-index.h"

void TestContext::startMeasure() {
    beginTime = std::chrono::steady_clock::now();
}

void TestContext::endMeasure() {
    deltaTime = std::chrono::steady_clock::now() - beginTime;
}

std::string TestContext::timeTakenByTest() const {
    constexpr i32 kBufferSize = 256;
    std::string result;
    result.resize(kBufferSize);

    if (deltaTime >= std::chrono::hours(1)) {
        i32 hours = i32(std::chrono::duration_cast<std::chrono::hours>(deltaTime).count());
        i32 minutes = i32(std::chrono::duration_cast<std::chrono::minutes>(deltaTime).count() % 60);
        i32 seconds = i32(std::chrono::duration_cast<std::chrono::seconds>(deltaTime).count() % 60);
        i64 milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count() % 1000;
        snprintf(&result[0], kBufferSize, "%02dh %02dm %02ds %lldms", hours, minutes, seconds, static_cast<long long int>(milliseconds));
    }
    else if (deltaTime >= std::chrono::minutes(1)) {
        i32 minutes = i32(std::chrono::duration_cast<std::chrono::minutes>(deltaTime).count());
        i32 seconds = i32(std::chrono::duration_cast<std::chrono::seconds>(deltaTime).count() % 60);
        i64 milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count() % 1000;
        snprintf(&result[0], kBufferSize, "%02dm %02ds %lldms", minutes, seconds, static_cast<long long int>(milliseconds));
    }
    else if (deltaTime >= std::chrono::seconds(1)) {
        i32 seconds = i32(std::chrono::duration_cast<std::chrono::seconds>(deltaTime).count());
        i64 milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count() % 1000;
        snprintf(&result[0], kBufferSize, "%02ds %lldms", seconds, static_cast<long long int>(milliseconds));
    }
    else if (deltaTime >= std::chrono::milliseconds(1)) {
        i64 milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();
        snprintf(&result[0], kBufferSize, "%lldms", static_cast<long long int>(milliseconds));
    }
    else {
        i64 nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime).count();
        snprintf(&result[0], kBufferSize, "%lldns", static_cast<long long int>(nanoseconds));
    }

    return result;
}

i32 runAllTests() {
    std::cout << "\nRUNNING TESTS\n" << std::endl;

    core::rndInit();

    runTestSuite(FN_NAME_TO_CPTR(runFigureFinderTestSuite), runFigureFinderTestSuite);

    return 0;
}

