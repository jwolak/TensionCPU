/*
 * Cpu-Speed-Detector-Tests-With-Mock.cpp
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

#include "../Mocks/Variables-For-Cpu-Speed-Detector-Mock.h"
#include "../../../TensionCPU/Source/Cpu-Speed-Detector.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>
#include <cstdint>

using ::testing::Return;
using ::testing::_;

namespace cpu_speed_detector_tests_with_mock {

namespace {
}

class CpuSpeedDetectorTestsWithMock : public ::testing::Test {
 public:
  CpuSpeedDetectorTestsWithMock()
      :
      variables_for_cpu_speed_detector_mock { new tension_cpu_mocks::VariablesForCpuSpeedDetectorMock },
      variables_for_cpu_benchmarker { new tension_cpu::VariablesForCpuBenchmarker },
      cpu_benchmarker { new tension_cpu::CpuBenchmarker { variables_for_cpu_benchmarker } },
      cpu_speed_detector { new tension_cpu::CpuSpeedDetector { variables_for_cpu_speed_detector_mock, cpu_benchmarker } } {
  }

  std::shared_ptr<tension_cpu_mocks::VariablesForCpuSpeedDetectorMock> variables_for_cpu_speed_detector_mock;
  std::shared_ptr<tension_cpu::VariablesForCpuBenchmarker> variables_for_cpu_benchmarker;
  std::shared_ptr<tension_cpu::ICpuBenchmarker> cpu_benchmarker;
  std::unique_ptr<tension_cpu::ICpuSpeedDetector> cpu_speed_detector;

};

TEST_F(CpuSpeedDetectorTestsWithMock, LoopS_Count_And_Time_Exceeded_And_GetLoopsPerSecond_Returned) {
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, SetLoopS(_)).Times(1);
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, LoopSCounterSet()).WillOnce(Return(false));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, CheckLoopSCounterNotZero()).WillOnce(Return(true));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, GetLoopS()).WillOnce(Return(10));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, GetPeriod()).WillOnce(Return(2));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, SetLoopsPerSecond(_)).Times(1);
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, GetLoopsPerSecond()).WillOnce(Return(2));

  ASSERT_EQ(cpu_speed_detector->GetLoopsPerSecond(), 2);
}

TEST_F(CpuSpeedDetectorTestsWithMock, PeriodTime_Exceeded__And_GetLoopsPerSecond_Returned) {
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, SetLoopS(_)).Times(1);
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, LoopSCounterSet()).WillOnce(Return(true));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, SetLoop(_)).Times(1);
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, SetTimePeriod()).Times(1);
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, GetLoop()).WillOnce(Return(10));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, GetLoopS()).Times(2).WillRepeatedly(Return(10));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, GetTimePeriodDiff()).WillOnce(Return(6));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, CheckLoopSCounterNotZero()).WillOnce(Return(true));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, GetPeriod()).WillOnce(Return(2));
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, SetLoopsPerSecond(_)).Times(1);
  EXPECT_CALL(*variables_for_cpu_speed_detector_mock, GetLoopsPerSecond()).WillOnce(Return(2));

  ASSERT_EQ(cpu_speed_detector->GetLoopsPerSecond(), 2);
}

} /*namespace cpu_speed_detector_tests_with_mock*/

