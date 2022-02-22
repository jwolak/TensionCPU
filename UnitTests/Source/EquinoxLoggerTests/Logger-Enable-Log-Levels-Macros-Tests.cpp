/*
 * Logger-Enable-Log-Levels-Macros-Tests.cpp
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

#include "../../../TensionCPU/Source/EquinoxLogger/Logger.h"

namespace logger_enable_log_levels_macros_tests{

namespace {
const std::string kTestLogMessage = "Test log message ";
const std::string kErrorHeader = "ERROR";
const std::string kWarningHeader = "WARNING";
const std::string kDebugHeader = "DEBUG";
}

class LoggerEnableLogLevelsMacrosTests : public ::testing::Test {
 public:
  LoggerEnableLogLevelsMacrosTests()
      :
      cout_strbuf(std::cout.rdbuf()),
      string_stream_output() {
  }

  std::streambuf *cout_strbuf;
  std::ostringstream string_stream_output;

  void RedirectStandarOutputToBuffer(std::ostringstream &output) {
    std::cout.rdbuf(output.rdbuf());
  }

  void RedirectFromBufferToStandarOutput() {
    std::cout.rdbuf(cout_strbuf);
  }

};

TEST_F(LoggerEnableLogLevelsMacrosTests, Disable_Log_And_DEBUG_Message_Is_NOT_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::DISABLE_LOG);
  LOG_DEBUG("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kDebugHeader) == std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Disable_Log_And_ERROR_Message_Is_NOT_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::DISABLE_LOG);
  LOG_ERROR("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kErrorHeader) == std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Disable_Log_And_WARNING_Message_Is_NOT_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::DISABLE_LOG);
  LOG_WARNING("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kWarningHeader) == std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_DEBUG_Log_And_DEBUG_Message_Is_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);
  LOG_DEBUG("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kDebugHeader) != std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_DEBUG_Log_And_ERROR_Message_Is_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);
  LOG_ERROR("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kErrorHeader) != std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_DEBUG_Log_And_WARNING_Message_Is_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);
  LOG_WARNING("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kWarningHeader) != std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_WARNING_Log_And_WARNING_Message_Is_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);
  LOG_WARNING("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kWarningHeader) != std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_WARNING_Log_And_ERROR_Message_Is_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);
  LOG_ERROR("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kErrorHeader) != std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_WARNING_Log_And_DEBUG_Message_Is_NOT_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_WARNING);
  LOG_DEBUG("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kDebugHeader) == std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_ERROR_Log_And_ERROR_Message_Is_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_ERROR);
  LOG_ERROR("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kErrorHeader) != std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_ERROR_Log_And_WARNING_Message_Is_NOT_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_ERROR);
  LOG_WARNING("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kWarningHeader) == std::string::npos);
}

TEST_F(LoggerEnableLogLevelsMacrosTests, Enable_ERROR_Log_And_DEBUG_Message_Is_NOT_Printed) {
  RedirectStandarOutputToBuffer(string_stream_output);
  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_ERROR);
  LOG_DEBUG("%s", kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kDebugHeader) == std::string::npos);
}

} /*logger_enable_log_levels_macros_tests*/
