/*
 * Tension-Cpu-Tests.cpp
 *
 *  Created on: 2022
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Janusz Wolak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <cstdint>

#include "../../../TensionCPU/Source/Tension-Cpu.cpp"
#include "../../../TensionCPU/Source/Cpu-Benchmarker.cpp"
#include "../../../TensionCPU/Source/Cpu-Load-Generator.cpp"
#include "../../../TensionCPU/Source/Timer.cpp"

namespace tension_cpu_tests {

namespace {
const uint32_t kNumberOfArgumentsSetToZero  = 0;
const uint32_t kNumberOfArgumentsSetToOne   = 1;
const uint32_t kNumberOfArgumentsSetToTwo   = 2;
const uint32_t kNumberOfArgumentsSetToThree = 3;
const uint32_t kNumberOfArgumentsSetToFour  = 4;

char* kTestProgramName = (char*)"TestAppName";
char* kEmptyCommandLineArgument[] = {kTestProgramName};
char* kCpuLoadCommandLineArgument[] = {kTestProgramName, (char*)"-l 90"};
char* kCpuLoadAndTestTimeCommandLineArguments[] = {kTestProgramName, (char*)"-l 90 -T 10"};
char* kCpuLoadAndTestTimeAndSchedulingAlgorithCommandLineArguments[] = {kTestProgramName, (char*)"-l 90 -T 10 -S b"};
char* kEnableHelpModeArgument[] = {kTestProgramName, (char*)"h"};

char* kCpuLoadCommandLineArgumentWithoutValue[] = {kTestProgramName, (char*)"-l"};
char* kTestTimeCommandLineArgumentWithoutValue[] = {kTestProgramName, (char*)"-l 90 -T"};
char* kdSchedulingAlgorithCommandLineArgumentWithoutValue[] = {kTestProgramName, (char*)"-l 90 -T 10 -S"};

char* kCpuLoadCommandLineArgumentMoreThan100[] = {kTestProgramName, (char*)"-l 101"};
char* kCpuLoadCommandLineArgumentEqualZero[] = {kTestProgramName, (char*)"-l 0"};
char* kCpuLoadCommandLineArgumentLowerThanlZero[] = {kTestProgramName, (char*)"-l -10"};

char* kTestTimeCommandLineArgumentOverflowed[] = {kTestProgramName, (char*)"-l 90 -T 2147483648"};
char* kTestTimeCommandLineArgumentWithNegativeValue[] = {kTestProgramName, (char*)"-l 90 -T -21"};

char* kTestTimeCommandLineArgumentWithZeroValue[] = {kTestProgramName, (char*)"-l 90 -T 0"};

char* kCommandLineArgumentsWithoutCpuLoad[] = {kTestProgramName, (char*)"-T 10"};

char* kdSchedulingAlgorithCommandLineArgumentWithoWrongValue[] = {kTestProgramName, (char*)"-l 90 -T 10 -S z"};
}

class TensionCpuTests : public ::testing::Test {
 public:
  TensionCpuTests()
      :
      tension_cpu { new tension_cpu::TensionCpu } {
  }

  std::unique_ptr<tension_cpu::ITensionCpu> tension_cpu;
};


TEST_F(TensionCpuTests, Parse_Help_Argument_And_True_Returned) {
  ASSERT_TRUE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToTwo, kEnableHelpModeArgument));
}

TEST_F(TensionCpuTests, Parse_None_Argument_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToOne, kEmptyCommandLineArgument));
}

TEST_F(TensionCpuTests, Parse_Cpu_Load_Argument_And_True_Returned) {
  ASSERT_TRUE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToTwo, kCpuLoadCommandLineArgument));
}

TEST_F(TensionCpuTests, Parse_Cpu_Load_And_Test_Time_Arguments_And_True_Returned) {
  ASSERT_TRUE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToThree, kCpuLoadAndTestTimeCommandLineArguments));
}

TEST_F(TensionCpuTests, Parse_Cpu_Load_And_Test_Time_And_Scheduling_Algorithm_Arguments_And_True_Returned) {
  ASSERT_TRUE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToFour, kCpuLoadAndTestTimeAndSchedulingAlgorithCommandLineArguments));
}

TEST_F(TensionCpuTests, Parse_Cpu_Load_Argument_Without_Value_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToTwo, kCpuLoadCommandLineArgumentWithoutValue));
}

TEST_F(TensionCpuTests, Parse_Test_Time_Argument_Without_Value_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToThree, kTestTimeCommandLineArgumentWithoutValue));
}

TEST_F(TensionCpuTests, Parse_Scheduling_Algorithm_Argument_Without_Value_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToFour, kdSchedulingAlgorithCommandLineArgumentWithoutValue));
}

TEST_F(TensionCpuTests, Parse_Cpu_Load_Argument_Grater_Than_100_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToTwo, kCpuLoadCommandLineArgumentMoreThan100));
}

TEST_F(TensionCpuTests, Parse_Cpu_Load_Argument_Equal_To_Zero_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToTwo, kCpuLoadCommandLineArgumentEqualZero));
}

TEST_F(TensionCpuTests, Parse_Scheduling_Algorithm_Argument_With_Wrong_Value_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToFour, kdSchedulingAlgorithCommandLineArgumentWithoWrongValue));
}

TEST_F(TensionCpuTests, Parse_Test_Time_Argument_Value_Overflowed_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToThree, kTestTimeCommandLineArgumentOverflowed));
}

TEST_F(TensionCpuTests, Parse_Arguments_Without_Cpu_Load_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToTwo, kCommandLineArgumentsWithoutCpuLoad));
}

TEST_F(TensionCpuTests, Parse_Test_Time_Argument_With_Zero_Value_And_True_Returned) {
  ASSERT_TRUE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToTwo, kTestTimeCommandLineArgumentWithZeroValue));
}

TEST_F(TensionCpuTests, DISABLED_Parse_Test_Time_Argument_With_Negative_Value_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToThree, kTestTimeCommandLineArgumentWithNegativeValue));
}

TEST_F(TensionCpuTests, DISABLED_Parse_Cpu_Load_Argument_Lower_Than_Zero_And_False_Returned) {
  ASSERT_FALSE(tension_cpu->ParseCmdArguments(kNumberOfArgumentsSetToTwo, kCpuLoadCommandLineArgumentLowerThanlZero));
}

} /*namespace tension_cpu_tests*/
