#include <core.h>

#include <stdexcept>
#include <stdio.h>

namespace core {

using namespace coretypes;

bool initCore(i32, char**) {
    core::setGlobalAssertHandler([](const char* failedExpr, const char* file, i32 line, const char* funcName, const char* errMsg) {
        fprintf(stderr,
                ANSI_BOLD(ANSI_RED("[ASSERTION] [EXPR]:")) ANSI_BOLD(" %s\n")
                ANSI_BOLD(ANSI_RED("[FUNC]:"))             ANSI_BOLD(" %s\n")
                ANSI_BOLD(ANSI_RED("[FILE]:"))             ANSI_BOLD(" %s:%d\n")
                ANSI_BOLD(ANSI_RED("[MSG]:"))              ANSI_BOLD(" %s\n"),

                failedExpr, funcName, file, line, errMsg
        );

        // TODO: Add a stack trace here.

        std::exit(-1);
    });

    return true;
}

void shutdownCore() {
    core::setGlobalAssertHandler(nullptr);
}

} // namespacec core

