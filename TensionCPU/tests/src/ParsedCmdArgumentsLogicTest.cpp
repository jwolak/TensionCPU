/*
 * ParsedCmdArgumentsLogicTest.cpp
 *
 *  Created on: 2023
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2023, Janusz Wolak
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

#include "CmdArgumentsParser/ParsedCmdArgumentsLogic.h"

namespace parsed_cmd_arguments_logic_test {

namespace {
const tension_cpu::cmd_arguments_parser::SchedulingModeType kTestSchedulingModeBatch = tension_cpu::cmd_arguments_parser::SchedulingModeType::BATCH;
const tension_cpu::cmd_arguments_parser::SchedulingModeType kTestSchedulingModeRR = tension_cpu::cmd_arguments_parser::SchedulingModeType::RR;
const tension_cpu::cmd_arguments_parser::SchedulingModeType kTestSchedulingModeFIFO = tension_cpu::cmd_arguments_parser::SchedulingModeType::FIFO;
const tension_cpu::cmd_arguments_parser::SchedulingModeType kTestSchedulingModeOTHER = tension_cpu::cmd_arguments_parser::SchedulingModeType::OTHER;
const int32_t kTestCpuLoad = 77;
const std::chrono::seconds kTestTime = std::chrono::seconds(7);
const tension_cpu::cmd_arguments_parser::DebugModeType kTestDebugModeCritical = tension_cpu::cmd_arguments_parser::DebugModeType::CRITICAL;
const tension_cpu::cmd_arguments_parser::DebugModeType kTestDebugModeDebug = tension_cpu::cmd_arguments_parser::DebugModeType::DEBUG;
const tension_cpu::cmd_arguments_parser::DebugModeType kTestDebugModeError = tension_cpu::cmd_arguments_parser::DebugModeType::ERROR;
const tension_cpu::cmd_arguments_parser::DebugModeType kTestDebugModeInfo = tension_cpu::cmd_arguments_parser::DebugModeType::INFO;
const tension_cpu::cmd_arguments_parser::DebugModeType kTestDebugModeTrace = tension_cpu::cmd_arguments_parser::DebugModeType::TRACE;
const tension_cpu::cmd_arguments_parser::DebugModeType kTestDebugModeWarning = tension_cpu::cmd_arguments_parser::DebugModeType::WARNING;
}

class ParsedCmdArgumentsLogicTest : public ::testing::Test {
 public:
  ParsedCmdArgumentsLogicTest() {
  }

  tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic parsed_cmd_arguments_logic;
};

TEST_F(ParsedCmdArgumentsLogicTest, Call_SetScheduligMode_With_BATCH_Argument_And_Field_scheduling_mode_type_Is_Set_To_BATCH) {
  parsed_cmd_arguments_logic.SetScheduligMode(kTestSchedulingModeBatch);
  ASSERT_EQ(parsed_cmd_arguments_logic.scheduling_mode_type, kTestSchedulingModeBatch);
}

TEST_F(ParsedCmdArgumentsLogicTest, Call_SetScheduligMode_With_RR_Argument_And_Field_scheduling_mode_type_Is_Set_To_RR) {
  parsed_cmd_arguments_logic.SetScheduligMode(kTestSchedulingModeRR);
  ASSERT_EQ(parsed_cmd_arguments_logic.scheduling_mode_type, kTestSchedulingModeRR);
}

TEST_F(ParsedCmdArgumentsLogicTest, Call_SetScheduligMode_With_FIFO_Argument_And_Field_scheduling_mode_type_Is_Set_To_FIFO) {
  parsed_cmd_arguments_logic.SetScheduligMode(kTestSchedulingModeFIFO);
  ASSERT_EQ(parsed_cmd_arguments_logic.scheduling_mode_type, kTestSchedulingModeFIFO);
}

TEST_F(ParsedCmdArgumentsLogicTest, Call_SetScheduligMode_With_OTHER_Argument_And_Field_scheduling_mode_type_Is_Set_To_OTHER) {
  parsed_cmd_arguments_logic.SetScheduligMode(kTestSchedulingModeOTHER);
  ASSERT_EQ(parsed_cmd_arguments_logic.scheduling_mode_type, kTestSchedulingModeOTHER);
}

TEST_F(ParsedCmdArgumentsLogicTest, Set_scheduling_mode_type_To_BATCH_And_Call_GetScheduligMode_And_BATCH_Returned) {
  parsed_cmd_arguments_logic.scheduling_mode_type = kTestSchedulingModeBatch;
  ASSERT_EQ(parsed_cmd_arguments_logic.GetScheduligMode(), kTestSchedulingModeBatch);
}

TEST_F(ParsedCmdArgumentsLogicTest, Set_scheduling_mode_type_To_RR_And_Call_GetScheduligMode_And_RR_Returned) {
  parsed_cmd_arguments_logic.scheduling_mode_type = kTestSchedulingModeRR;
  ASSERT_EQ(parsed_cmd_arguments_logic.GetScheduligMode(), kTestSchedulingModeRR);
}

TEST_F(ParsedCmdArgumentsLogicTest, Set_scheduling_mode_type_To_FIFO_And_Call_GetScheduligMode_FIFO_Returned) {
  parsed_cmd_arguments_logic.scheduling_mode_type = kTestSchedulingModeFIFO;
  ASSERT_EQ(parsed_cmd_arguments_logic.GetScheduligMode(), kTestSchedulingModeFIFO);
}

TEST_F(ParsedCmdArgumentsLogicTest, Set_scheduling_mode_type_To_OTHER_And_Call_GetScheduligMode_And_OTHER_Returned) {
  parsed_cmd_arguments_logic.scheduling_mode_type = kTestSchedulingModeOTHER;
  ASSERT_EQ(parsed_cmd_arguments_logic.GetScheduligMode(), kTestSchedulingModeOTHER);
}

TEST_F(ParsedCmdArgumentsLogicTest, Call_SetLoad_And_Field_cpu_load_Set) {
  parsed_cmd_arguments_logic.SetLoad(kTestCpuLoad);
  ASSERT_EQ(parsed_cmd_arguments_logic.cpu_load, kTestCpuLoad);
}

TEST_F(ParsedCmdArgumentsLogicTest, Set_Field_cpu_load_And_Call_GetLoad_And_Set_Cpu_Load_Returned) {
  parsed_cmd_arguments_logic.cpu_load = kTestCpuLoad;
  ASSERT_EQ(parsed_cmd_arguments_logic.GetLoad(), kTestCpuLoad);
}

TEST_F(ParsedCmdArgumentsLogicTest, Call_SetTestTime_And_Test_Field_test_time_Set) {
  parsed_cmd_arguments_logic.SetTestTime(kTestTime);
  ASSERT_EQ(parsed_cmd_arguments_logic.test_time, kTestTime);
}

TEST_F(ParsedCmdArgumentsLogicTest, Set_Field_test_time_And_Call_GetTestTime_And_Set_Test_Time_Returned) {
  parsed_cmd_arguments_logic.test_time = std::chrono::seconds(kTestTime);
  ASSERT_EQ(parsed_cmd_arguments_logic.GetTestTime(), kTestTime);
}

class SetDebugModeTestsParams {
 public:
  SetDebugModeTestsParams(tension_cpu::cmd_arguments_parser::DebugModeType debug_mode,
                          tension_cpu::cmd_arguments_parser::DebugModeType expected_mode)
      :
      set_debug_mode { debug_mode },
      expected_debug_mode { expected_mode } {
  }

  tension_cpu::cmd_arguments_parser::DebugModeType set_debug_mode;
  tension_cpu::cmd_arguments_parser::DebugModeType expected_debug_mode;
};

class DebugModeParametrizedTest : public testing::TestWithParam<SetDebugModeTestsParams> {
 public:
  DebugModeParametrizedTest()
      :
      parsed_cmd_arguments_logic { } {
  }

  tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic parsed_cmd_arguments_logic;
};

TEST_P(DebugModeParametrizedTest, Set_Field_debug_mode_And_Call_GetDebugMode_And_Set_Debug_Mode_Returned) {
  SetDebugModeTestsParams params = GetParam();
  parsed_cmd_arguments_logic.debug_mode = params.set_debug_mode;
  ASSERT_EQ(parsed_cmd_arguments_logic.GetDebugMode(), params.expected_debug_mode);
}

TEST_P(DebugModeParametrizedTest, Call_SetDebugMode_And_Test_Field_debug_mode_Set) {
  SetDebugModeTestsParams params = GetParam();
  parsed_cmd_arguments_logic.SetDebugMode(params.set_debug_mode);
  ASSERT_EQ(parsed_cmd_arguments_logic.debug_mode, params.expected_debug_mode);
}

SetDebugModeTestsParams params[] = { { kTestDebugModeCritical, kTestDebugModeCritical },
                                     { kTestDebugModeDebug, kTestDebugModeDebug },
                                     { kTestDebugModeError, kTestDebugModeError },
                                     { kTestDebugModeInfo, kTestDebugModeInfo },
                                     { kTestDebugModeTrace, kTestDebugModeTrace },
                                     { kTestDebugModeWarning, kTestDebugModeWarning }
};

INSTANTIATE_TEST_CASE_P(PackOfTests, DebugModeParametrizedTest, testing::ValuesIn(params));

} /*namespace parsed_cmd_arguments_logic_test*/
