/*
 * Console-Logger-Tests.cpp
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

#include "../../../TensionCPU/Source/EquinoxLogger/Console-Logger.cpp"

namespace console_logger_tests {

namespace {
std::string kTestLogMessage = "Test log message ";
}

class ConsoleLoggerTests : public ::testing::Test {
 public:
  ConsoleLoggerTests()
      :
      console_logger(new equinox_logger::ConsoleLogger),
      cout_strbuf(std::cout.rdbuf()),
      string_stream_output() {
  }

  std::unique_ptr<equinox_logger::IConsoleLogger> console_logger;
  std::streambuf *cout_strbuf;
  std::ostringstream string_stream_output;

  void RedirectStandarOutputToBuffer(std::ostringstream &output) {
    std::cout.rdbuf(output.rdbuf());
  }

  void RedirectFromBufferToStandarOutput() {
    std::cout.rdbuf(cout_strbuf);
  }

};

TEST_F (ConsoleLoggerTests, Call_LogMessage_And_No_Throw_Occurs) {
  ASSERT_NO_THROW(console_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage));
}

TEST_F(ConsoleLoggerTests, LogMessage_As_Text_To_Console_And_It_Is_Printed_Successfully) {

  RedirectStandarOutputToBuffer(string_stream_output);
  console_logger->LogMessage(equinox_logger::LogLevelType::LOG_LEVEL_ERROR, kTestLogMessage);
  RedirectFromBufferToStandarOutput();

  ASSERT_EQ(string_stream_output.str(), kTestLogMessage);
}

} /*console_logger_tests*/
