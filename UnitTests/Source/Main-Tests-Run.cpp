/*#include "Command-Line-Parser-Tests.cpp"*/

#include <gtest/gtest.h>
#include "gmock/gmock.h"

/*
#include "EquinoxLoggerTests/File-Logger-Tests.cpp"
#include "EquinoxLoggerTests/Console-Logger-Tests.cpp"
#include "EquinoxLoggerTests/Logger-Level-Tests.cpp"
#include "EquinoxLoggerTests/Logger-Output-Tests.cpp"
#include "EquinoxLoggerTests/Logger-Log-Message-Macros-Tests.cpp"
#include "EquinoxLoggerTests/Logger-Enable-Log-Levels-Macros-Tests.cpp"
*/
#include "TensionCpuTests/Cmd-Args-Parser-Tests.cpp"
#include "TensionCpuTests/Tension-Cpu-Tests.cpp"
#include "TensionCpuTests/Cpu-Benchmarker-Tests.cpp"
#include "TensionCpuTests/Cpu-Speed-Detector-Tests.cpp"
#include "TensionCpuTests/Cpu-Speed-Detector-Tests-With-Mock.cpp"

int main(int argc, char **argv) {
    SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
