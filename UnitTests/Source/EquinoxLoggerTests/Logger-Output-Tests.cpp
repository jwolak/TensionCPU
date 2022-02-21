/*
 * Logger-Output-Tests.cpp
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

#include "../../../TensionCPU/Source/EquinoxLogger/Logger-Output.cpp"

namespace logger_output_tests{

namespace {
enum class UnknownOutputType {
  UNKNOWN_OUTPUT  = 5
};
}

class LoggerOutputTests :public ::testing::Test {
 public:
  LoggerOutputTests()
      :
      logger_output(new equinox_logger::LoggerOutput) {}

  std::unique_ptr<equinox_logger::LoggerOutput> logger_output;
};

TEST_F(LoggerOutputTests, SetLoggingOutput_Sets_Successfully_CONSOLE) {
  logger_output->SetOutput(equinox_logger::LogOutputType::CONSOLE);
  ASSERT_EQ(logger_output->logger_output_type, equinox_logger::LogOutputType::CONSOLE);
}

TEST_F(LoggerOutputTests, SetLoggingOutput_Sets_Successfully_FILE_LOG) {
  logger_output->SetOutput(equinox_logger::LogOutputType::FILE_LOG);
  ASSERT_EQ(logger_output->logger_output_type, equinox_logger::LogOutputType::FILE_LOG);
}

TEST_F(LoggerOutputTests, SetLoggingOutput_Sets_Successfully_FILE_AND_CONSOLE) {
  logger_output->SetOutput(equinox_logger::LogOutputType::FILE_AND_CONSOLE);
  ASSERT_EQ(logger_output->logger_output_type, equinox_logger::LogOutputType::FILE_AND_CONSOLE);
}

TEST_F(LoggerOutputTests, SetLoggingOutput_Sets_UNKNOWN_OUTPUT_And_FILE_AND_CONSOLE_Is_Set) {
  logger_output->SetOutput(static_cast<equinox_logger::LogOutputType>(UnknownOutputType::UNKNOWN_OUTPUT));
  ASSERT_EQ(logger_output->logger_output_type, equinox_logger::LogOutputType::FILE_AND_CONSOLE);
}

TEST_F(LoggerOutputTests, Set_Logger_Output_Type_To_Console_And_GetOutput_Returns_CONSOLE) {
  logger_output->logger_output_type = equinox_logger::LogOutputType::CONSOLE;
  ASSERT_EQ(logger_output->GetOutput(), equinox_logger::LogOutputType::CONSOLE);
}

TEST_F(LoggerOutputTests, Set_Logger_Output_Type_To_Console_And_GetOutput_Returns_FILE_LOG) {
  logger_output->logger_output_type = equinox_logger::LogOutputType::FILE_LOG;
  ASSERT_EQ(logger_output->GetOutput(), equinox_logger::LogOutputType::FILE_LOG);
}

TEST_F(LoggerOutputTests, Set_Logger_Output_Type_To_Console_And_GetOutput_Returns_FILE_AND_CONSOLE) {
  logger_output->logger_output_type = equinox_logger::LogOutputType::FILE_AND_CONSOLE;
  ASSERT_EQ(logger_output->GetOutput(), equinox_logger::LogOutputType::FILE_AND_CONSOLE);
}

} /*namespace test_logger_set_logging_output_tests*/

