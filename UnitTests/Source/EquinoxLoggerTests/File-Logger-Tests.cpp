/*
 * File-Logger-Tests.cpp
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
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>

#include "../../../TensionCPU/Source/EquinoxLogger/File-Logger.cpp"
#include "../../../TensionCPU/Source/EquinoxLogger/Log-Level-Type.h"

namespace file_logger_tests {

namespace {
std::string kTestLogMessage = "Test log message";
std::string kTestLogMessage2 = "Test log message2";
std::string kTestLogMessage3 = "Test log message3";
}

class FileLoggerTests : public ::testing::Test {
 public:
  FileLoggerTests()
      :
      logger_time(new equinox_logger::LoggerTime),
      file_logger(new equinox_logger::FileLogger(logger_time)) {
  }

  std::shared_ptr<equinox_logger::ILoggerTime> logger_time;
  std::unique_ptr<equinox_logger::IFileLogger> file_logger;

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

  void TearDown() override {
    std::remove(equinox_logger::kLogFileName.c_str());
  }
};

TEST_F(FileLoggerTests, Call_LogMessage_And_No_Throw_Occurs) {
  ASSERT_NO_THROW(file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage));
}

TEST_F(FileLoggerTests, Log_Message_To_File_And_Message_Is_Placed_In_The_File_Successfully) {
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage);
  std::string data_from_log_file = ReadDataFromLogFile(equinox_logger::kLogFileName);

  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage) != std::string::npos);
}

TEST_F(FileLoggerTests, Log_Several_Messages_To_File_And_Messages_Are_Placed_In_The_File_Successfully) {
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage);
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage2);
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage3);
  std::string data_from_log_file = ReadDataFromLogFile(equinox_logger::kLogFileName);

  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage) != std::string::npos);
  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage2) != std::string::npos);
  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage3) != std::string::npos);
}

TEST_F(FileLoggerTests, Log_Several_Messages_With_Several_Levels_To_File_And_Messages_Are_Placed_In_The_File_Successfully) {
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage);
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_WARNING, kTestLogMessage2);
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG, kTestLogMessage3);
  std::string data_from_log_file = ReadDataFromLogFile(equinox_logger::kLogFileName);

  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage) != std::string::npos);
  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage2) != std::string::npos);
  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage3) != std::string::npos);
}

TEST_F(FileLoggerTests, Disable_Logger_And_Log_Message_To_File_And_Message_Is_NOT_Placed_In_The_File) {
  file_logger->LogMessage(equinox_logger::LogLevelType::DISABLE_LOG, kTestLogMessage);
  std::string data_from_log_file = ReadDataFromLogFile(equinox_logger::kLogFileName);

  ASSERT_TRUE(data_from_log_file.find(kTestLogMessage) == std::string::npos);
}

TEST_F(FileLoggerTests, Log_Message_To_File_And_ERROR_Message_Header_Is_Placed_In_The_File_Successfully) {
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage);
  std::string data_from_log_file = ReadDataFromLogFile(equinox_logger::kLogFileName);

  ASSERT_TRUE(data_from_log_file.find(equinox_logger::kErrorMessageHeader) != std::string::npos);
}

TEST_F(FileLoggerTests, Log_Message_To_File_And_WARNING_Message_Header_Is_Placed_In_The_File_Successfully) {
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_WARNING, kTestLogMessage);
  std::string data_from_log_file = ReadDataFromLogFile(equinox_logger::kLogFileName);

  ASSERT_TRUE(data_from_log_file.find(equinox_logger::kWarningMessageHeader) != std::string::npos);
}

TEST_F(FileLoggerTests, Log_Message_To_File_And_DEBUG_Message_Header_Is_Placed_In_The_File_Successfully) {
  file_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG, kTestLogMessage);
  std::string data_from_log_file = ReadDataFromLogFile(equinox_logger::kLogFileName);

  ASSERT_TRUE(data_from_log_file.find(equinox_logger::kDebugMessageHeader) != std::string::npos);
}

} /*file_logger_tests*/
