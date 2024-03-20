#pragma once

#include "t-index.h"

figfind::DataType testData1 = {
    0, 1, 0, 0, 1,
    1, 1, 1, 1, 1,
    0, 1, 0, 0, 1,
    1, 1, 1, 1, 1
};
constexpr i32 testData1Width = 5;
constexpr i32 testData1Height = 4;
constexpr i32 testData1Expected = 1;

figfind::DataType testData2 = {
    1, 1, 1, 1, 1,
    1, 0, 0, 0, 1,
    1, 0, 1, 0, 1,
    1, 0, 1, 0, 1,
    1, 0, 1, 0, 1,
    1, 0, 1, 0, 1,
    1, 0, 0, 0, 1,
    1, 1, 1, 1, 1,
};
constexpr i32 testData2Width = 5;
constexpr i32 testData2Height = 8;
constexpr i32 testData2Expected = 2;

figfind::DataType testData3 = {
    1, 1, 1,
    0, 0, 0,
    1, 1, 1,
    0, 0, 0,
    1, 1, 1,
};
constexpr i32 testData3Width = 3;
constexpr i32 testData3Height = 5;
constexpr i32 testData3Expected = 3;

figfind::DataType testData4 = {
    1, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1,
};
constexpr i32 testData4Width = 9;
constexpr i32 testData4Height = 4;
constexpr i32 testData4Expected = 4;

figfind::DataType testData5 = {
    1, 1, 1, 0, 1, 1, 0, 0, 1,
    1, 1, 1, 0, 1, 1, 0, 1, 0,
    1, 0, 1, 1, 0, 0, 0, 1, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 1, 0, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 1, 0, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 0, 1, 0,
    0, 1, 0, 0, 0, 1, 0, 1, 1,
    1, 1, 0, 0, 1, 1, 0, 1, 1,
    1, 1, 1, 0, 1, 0, 1, 1, 1,
};
constexpr i32 testData5Width = 9;
constexpr i32 testData5Height = 13;
constexpr i32 testData5Expected = 10;

// Example from assignment:
figfind::DataType testData6 = {
    1, 0, 0, 0, 0,
    1, 0, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 0, 1,
};
constexpr i32 testData6Width = 5;
constexpr i32 testData6Height = 5;
constexpr i32 testData6Expected = 3;

figfind::DataType testData7 = {
    0, 0, 0, 0, 0, 0, 0, 0, 0
};
constexpr i32 testData7Width = 9;
constexpr i32 testData7Height = 1;
constexpr i32 testData7Expected = 0;

figfind::DataType testData8 = {
    1, 1, 1, 1, 1, 1, 1, 1, 1
};
constexpr i32 testData8Width = 9;
constexpr i32 testData8Height = 1;
constexpr i32 testData8Expected = 1;

figfind::DataType testData9 = {
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1
};
constexpr i32 testData9Width = 1;
constexpr i32 testData9Height = 9;
constexpr i32 testData9Expected = 1;

figfind::DataType testData10 = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};
constexpr i32 testData10Width = 1;
constexpr i32 testData10Height = 9;
constexpr i32 testData10Expected = 0;

figfind::DataType testData11 = {
    0,
    0,
    1,
    1,
    0,
    0,
    1,
    0,
    1
};
constexpr i32 testData11Width = 1;
constexpr i32 testData11Height = 9;
constexpr i32 testData11Expected = 3;

figfind::DataType testData12 = {
    1, 0, 0, 0, 1,
    0, 1, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 1, 0, 1, 0,
    1, 0, 0, 0, 1,
};
constexpr i32 testData12Width = 5;
constexpr i32 testData12Height = 5;
constexpr i32 testData12Expected = 9;

figfind::DataType testsData13 = {
    1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0,
};
constexpr i32 testData13Width = 9;
constexpr i32 testData13Height = 4;
constexpr i32 testData13Expected = 18;

figfind::DataType backwardsCompatibilityTest1 = {
    1, 0, 0, 1, 1, 1, 1, 1, 0, 1,
    1, 0, 1, 0, 1, 1, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
    0, 0, 1, 1, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 0, 1, 0, 0, 1, 0,
    1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
    0, 1, 0, 1, 1, 1, 0, 0, 1, 1,
    0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 1, 0, 0, 0, 1, 0, 0, 0, 0,
};
constexpr i32 backwardsCompatibilityTest1Width = 10;
constexpr i32 backwardsCompatibilityTest1Height = 10;
constexpr i32 backwardsCompatibilityTest1Expected = 5;

figfind::DataType backwardsCompatibilityTest2 = {
    0, 0, 0, 1, 1,
    0, 1, 1, 1, 1,
    1, 1, 1, 1, 0,
    0, 0, 0, 0, 0,
    1, 0, 1, 1, 1,
};
constexpr i32 backwardsCompatibilityTest2Width = 5;
constexpr i32 backwardsCompatibilityTest2Height = 5;
constexpr i32 backwardsCompatibilityTest2Expected = 3;
