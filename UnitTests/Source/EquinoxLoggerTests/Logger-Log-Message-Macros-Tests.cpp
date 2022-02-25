/*
 * Logger-Log-Message-Macros-Tests.cpp
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

#include "../../../TensionCPU/Source/EquinoxLogger/Logger.cpp"


namespace logger_log_macros_tests{

namespace {
const std::string kTestLogMessage = "Test log message ";

const int kNumberInt = 3;
const std::string kMessageWithTypeIntSpecificator = kTestLogMessage + "%d";
const std::string kMessageWithIntNumber = kTestLogMessage + std::to_string(kNumberInt);

const float kNumberFloat = 10.110000;
const std::string kMessageWithTypeFloatSpecificator = kTestLogMessage + "%f2.6";
const std::string kMessageWithFloatNumber = kTestLogMessage + std::to_string(kNumberFloat);
}

class LoggerLogMessageMacrosTests : public ::testing::Test {
 public:
  LoggerLogMessageMacrosTests()
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

  void SetUp() override {
    SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);
  }

  void TearDown() override {
    std::remove(equinox_logger::kLogFileName.c_str());
  }

  std::string ReadDataFromLogFile(const std::string &file_name) {
    std::ifstream log_file;
    log_file.open(file_name);
    std::string buffer;

    if (log_file.is_open()) {
      while (log_file) {
        buffer += log_file.get();
      }
    }

    return buffer;
  }

};


TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_ERROR_To_Console_And_File_And_It_Is_Successfully) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_ERROR("%s", kTestLogMessage.c_str());
  RedirectFromBufferToStandarOutput();

  /*ASSERT_EQ(string_stream_output.str(), kTestLogMessage);*/
  ASSERT_TRUE(string_stream_output.str().find(kTestLogMessage) != std::string::npos);
  std::string data_from_log_file = ReadDataFromLogFile(equinox_logger::kLogFileName);
  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage) != std::string::npos);
}

TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_ERROR_To_Console_And_ERROR_Header_Is_Placed_Successfull) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_ERROR("%s", kTestLogMessage.c_str());
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(equinox_logger::kErrorMessageHeader) != std::string::npos);
}

TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_ERROR_With_Integer_Number_To_Console_And_It_Is_Placed_Successfull) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_ERROR(kMessageWithTypeIntSpecificator.c_str(), kNumberInt);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(std::to_string(kNumberInt)) != std::string::npos);
}

TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_WARNING_To_Console_And_It_Is_Successfully) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_WARNING("%s", kTestLogMessage.c_str());
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kTestLogMessage) != std::string::npos);
}

TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_WARNING_To_Console_And_WARNING_Header_Is_Placed_Successfull) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_WARNING("%s", kTestLogMessage.c_str());
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(equinox_logger::kWarningMessageHeader) != std::string::npos);
}

TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_WARNING_With_Integer_Number_To_Console_And_It_Is_Placed_Successfull) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_WARNING(kMessageWithTypeIntSpecificator.c_str(), kNumberInt);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(std::to_string(kNumberInt)) != std::string::npos);
}

TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_DEBUG_To_Console_And_Message_Is_Placed_In_The_File_Successfully) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_DEBUG("%s", kTestLogMessage.c_str());
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(kTestLogMessage) != std::string::npos);
}

TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_DEBUG_To_Console_And_DEBUG_Header_Is_Placed_Successfull) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_DEBUG("%s", kTestLogMessage.c_str());
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(equinox_logger::kDebugMessageHeader) != std::string::npos);
}

TEST_F(LoggerLogMessageMacrosTests, Log_Message_As_DEBUG_With_Integer_Number_To_Console_And_It_Is_Placed_Successfull) {
  RedirectStandarOutputToBuffer(string_stream_output);
  LOG_DEBUG(kMessageWithTypeIntSpecificator.c_str(), kNumberInt);
  RedirectFromBufferToStandarOutput();

  ASSERT_TRUE(string_stream_output.str().find(std::to_string(kNumberInt)) != std::string::npos);
}

} /*namespace logger_log_macros_tests*/


