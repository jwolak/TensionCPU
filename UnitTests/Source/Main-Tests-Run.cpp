/*#include "Command-Line-Parser-Tests.cpp"*/

#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "Logger-Test_Set-Logging-Level-Tests.cpp"
#include "Logger-Test_Set-Logging-Output-Tests.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
