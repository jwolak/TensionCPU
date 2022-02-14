/*
 * Logger-Test_Set-Logging-Level-Tests.cpp
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

#include "../../TensionCPU/Source/Logger/Logger.cpp"

namespace test_logger_set_logging_level_tests {

namespace {
enum class TestLogLevelType {
  UNKNOWN_LOG_LEVEL       = 6,
};
}

class LoggerTests :public ::testing::Test {
 public:
  LoggerTests() : logger_level(new logger::LoggerLevel),
                  logger(new logger::Logger(logger_level)) {}

  std::shared_ptr<logger::LoggerLevel> logger_level;
  std::unique_ptr<logger::ILogger> logger;
};

TEST_F(LoggerTests, SetLoggingLevel_Sets_Successfully_DISABLE_LOG) {
  logger->SetLoggingLevel(logger::LogLevelType::DISABLE_LOG);
  ASSERT_EQ(logger_level->log_level_type, logger::LogLevelType::DISABLE_LOG);
}

TEST_F(LoggerTests, SetLoggingLevel_Sets_Successfully_LOG_LEVEL_ERROR) {
  logger->SetLoggingLevel(logger::LogLevelType::LOG_LEVEL_ERROR);
  ASSERT_EQ(logger_level->log_level_type, logger::LogLevelType::LOG_LEVEL_ERROR);
}

TEST_F(LoggerTests, SetLoggingLevel_Sets_Successfully_LOG_LEVEL_WARNING) {
  logger->SetLoggingLevel(logger::LogLevelType::LOG_LEVEL_WARNING);
  ASSERT_EQ(logger_level->log_level_type, logger::LogLevelType::LOG_LEVEL_WARNING);
}

TEST_F(LoggerTests, SetLoggingLevel_Sets_Successfully_LOG_LEVEL_DEBUG) {
  logger->SetLoggingLevel(logger::LogLevelType::LOG_LEVEL_DEBUG);
  ASSERT_EQ(logger_level->log_level_type, logger::LogLevelType::LOG_LEVEL_DEBUG);
}

TEST_F(LoggerTests, SetLoggingLevel_Sets_UNKNOWN_LOG_LEVEL_And_LOG_LEVEL_ERROR_Is_Set) {
  logger->SetLoggingLevel(static_cast<logger::LogLevelType>(TestLogLevelType::UNKNOWN_LOG_LEVEL));
  ASSERT_EQ(logger_level->log_level_type, logger::LogLevelType::LOG_LEVEL_ERROR);
}

} /*namespace test_logger_set_logging_level_tests*/

