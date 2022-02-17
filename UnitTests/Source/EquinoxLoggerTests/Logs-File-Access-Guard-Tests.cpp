/*
 * Logs-File-Access-Guard-Tests.cpp
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
#include <stdint.h>
#include <thread>
#include <future>

#include "../../../TensionCPU/Source/EquinoxLogger/Logs-File-Access-Guard.cpp"

namespace logs_file_access_guard_tests {

namespace {
const int32_t kValueForThreadLoop = 1000;
const int32_t kResultValue = kValueForThreadLoop + kValueForThreadLoop;
}


class LogsFileAccessGuardTests : public ::testing::Test {
 public:
  LogsFileAccessGuardTests()
      :
      logs_file_access_guard(new equinox_logger::LogsFileAccessGuard) {
  }

  std::unique_ptr<equinox_logger::ILogsFileAccessGuard> logs_file_access_guard;

 void ChangeVariableValueToTwo(int32_t* accessible_variable);
 void ChangeVariableValueToFour(int32_t* accessible_variable);


};

void LogsFileAccessGuardTests::ChangeVariableValueToTwo(int32_t *accessible_variable) {
  logs_file_access_guard->EnableAccessGuard();
  for (int i = 0; i < kValueForThreadLoop; ++i) {
    *accessible_variable = ++(*accessible_variable);
  }
  logs_file_access_guard->DisableAccessGuard();
  std::cout << "ChangeVariableValueToTwo: " << (*accessible_variable) << std::endl;
}

void LogsFileAccessGuardTests::ChangeVariableValueToFour(int32_t *accessible_variable) {
  logs_file_access_guard->EnableAccessGuard();
  for (int i = 0; i < kValueForThreadLoop; ++i) {
    *accessible_variable = ++(*accessible_variable);
  }
  logs_file_access_guard->DisableAccessGuard();
  std::cout << "ChangeVariableValueToFour: " << (*accessible_variable) << std::endl;
}

TEST_F(LogsFileAccessGuardTests, Lock_Access_To_Variable_And_It_Is_Successful) {
  static int32_t accessible_variable = 0;

  std::thread t4(&LogsFileAccessGuardTests::ChangeVariableValueToFour, this, &accessible_variable);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  std::thread t2(&LogsFileAccessGuardTests::ChangeVariableValueToTwo, this, &accessible_variable);

  t4.detach();
  t2.detach();

  ASSERT_EQ(accessible_variable, kResultValue);

}

} /*namespace logs_file_access_guard_tests*/
