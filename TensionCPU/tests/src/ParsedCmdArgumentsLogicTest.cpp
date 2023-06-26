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

} /*namespace parsed_cmd_arguments_logic_test*/
