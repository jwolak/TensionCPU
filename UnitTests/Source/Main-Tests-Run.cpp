/*#include "Command-Line-Parser-Tests.cpp"*/

#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "EquinoxLoggerTests/File-Logger-Tests.cpp"
#include "EquinoxLoggerTests/Console-Logger-Tests.cpp"
#include "EquinoxLoggerTests/Logger-Level-Tests.cpp"
#include "EquinoxLoggerTests/Logger-Output-Tests.cpp"
#include "EquinoxLoggerTests/Logger-Log-Message-Macros-Tests.cpp"
#include "EquinoxLoggerTests/Logger-Enable-Log-Levels-Macros-Tests.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
