/*
 * Cmd-Args-Parser-Tests.cpp
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

#include "../../../TensionCPU/Source/Cmd-Args-Parser.cpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <iostream>

namespace cmd_args_parser_test {

namespace {
const uint32_t kNumberOfArgumentsSetToOne   = 1;
const uint32_t kNumberOfArgumentsSetToTwo   = 2;
const uint32_t kNumberOfArgumentsSetToThree = 3;
const uint32_t kNumberOfArgumentsSetToFour  = 4;

int32_t cpu_load_value = 90;
int32_t test_time      = 10;

char* kTestProgramName = (char*)"TestAppName";
char* kEmptyCommandLineArgument[] = {kTestProgramName};
char* kCpuLoadCommandLineArgument[] = {{(char*)kTestProgramName}, {(char*)"-l 90"}};
char* kCpuLoadAndTestTimeCommandLineArguments[] = {{kTestProgramName}, {(char*)"-l 90"}, {(char*)"-T 10"}};
char* kCpuLoadAndTestTimeAndSchedulingAlgorithBatchCommandLineArguments[] = {{(char*)kTestProgramName}, {(char*)"-l 90"}, {(char*)"-T 10"}, {(char*)"-S b"}};
char* kCpuLoadAndTestTimeAndSchedulingAlgorithFifoCommandLineArguments[] = {{(char*)kTestProgramName}, {(char*)"-l 90"}, {(char*)"-T 10"}, {(char*)"-S f"}};
char* kCpuLoadAndTestTimeAndSchedulingAlgorithRoundRobinCommandLineArguments[] = {{(char*)kTestProgramName}, {(char*)"-l 90"}, {(char*)"-T 10"}, {(char*)"-S r"}};
char* kCpuLoadAndTestTimeAndSchedulingAlgorithOtherCommandLineArguments[] = {{(char*)kTestProgramName}, {(char*)"-l 90"}, {(char*)"-T 10"}, {(char*)"-S o"} };
}

class CmdArgsParserTests : public ::testing::Test {
 public:
  CmdArgsParserTests()
      :
      cmd_arguments { new tension_cpu::CmdArguments },
      cmd_args_parser { new tension_cpu::CmdArgsParser { cmd_arguments } } {
  }

  std::shared_ptr<tension_cpu::CmdArguments> cmd_arguments;
  std::unique_ptr<tension_cpu::ICmdArgsParser> cmd_args_parser;

};

TEST_F(CmdArgsParserTests, Process_Empty_CommandLine_Arguments_And_False_Returned) {
  ASSERT_FALSE(cmd_args_parser->ProcessArguments(kNumberOfArgumentsSetToOne, kEmptyCommandLineArgument));
}

TEST_F(CmdArgsParserTests, Process_Load_Cpu_Argument_And_Cpu_Load_Value_In_CmdArguments_Is_Set) {
  cmd_args_parser->ProcessArguments(kNumberOfArgumentsSetToTwo, kCpuLoadCommandLineArgument);
  ASSERT_EQ(cpu_load_value, cmd_arguments->cpu_load);
}

TEST_F(CmdArgsParserTests, Process_Test_Time_Argument_And_Test_Time_In_CmdArguments_Is_Set) {
  cmd_args_parser->ProcessArguments(kNumberOfArgumentsSetToThree, kCpuLoadAndTestTimeCommandLineArguments);
  ASSERT_EQ(test_time, cmd_arguments->test_time.count());
}

TEST_F(CmdArgsParserTests, Process_Sched_Mode_Batch_Argument_And_Batch_Mode_In_CmdArguments_Is_Set) {
  cmd_args_parser->ProcessArguments(kNumberOfArgumentsSetToFour, kCpuLoadAndTestTimeAndSchedulingAlgorithBatchCommandLineArguments);
  ASSERT_EQ(cmd_arguments->scheduling_policy, tension_cpu::SchedulingPolicyType::BATCH);
}

TEST_F(CmdArgsParserTests, Process_Sched_Mode_Fifo_Argument_And_Fifo_Mode_In_CmdArguments_Is_Set) {
  cmd_args_parser->ProcessArguments(kNumberOfArgumentsSetToFour, kCpuLoadAndTestTimeAndSchedulingAlgorithFifoCommandLineArguments);
  ASSERT_EQ(cmd_arguments->scheduling_policy, tension_cpu::SchedulingPolicyType::FIFO);
}

TEST_F(CmdArgsParserTests, Process_Sched_Mode_RounRobin_Argument_And_RoundRobin_Mode_In_CmdArguments_Is_Set) {
  cmd_args_parser->ProcessArguments(kNumberOfArgumentsSetToFour, kCpuLoadAndTestTimeAndSchedulingAlgorithRoundRobinCommandLineArguments);
  EXPECT_EQ(cmd_arguments->scheduling_policy, tension_cpu::SchedulingPolicyType::RR);
}

TEST_F(CmdArgsParserTests, Process_Sched_Mode_Other_Argument_And_Other_Mode_In_CmdArguments_Is_Set) {
  cmd_args_parser->ProcessArguments(kNumberOfArgumentsSetToFour, kCpuLoadAndTestTimeAndSchedulingAlgorithOtherCommandLineArguments);
  ASSERT_EQ(cmd_arguments->scheduling_policy, tension_cpu::SchedulingPolicyType::OTHER);
}

} /*namespace cmd_args_parser_test*/

