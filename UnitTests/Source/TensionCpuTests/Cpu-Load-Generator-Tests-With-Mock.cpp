/*
 * Cpu-Load-Generator-Tests-With-Mock.cpp
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

#include "../Mocks/Variables-For-Cpu-Load-Generator-Mock.h"
#include "../Mocks/Cpu-Speed-Detector-Mock.h"
#include "../Mocks/Cpu-Benchmarker-Mock.h"
#include "../../../TensionCPU/Source/Cpu-Load-Generator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>
#include <cstdint>

using ::testing::Return;
using ::testing::_;

namespace cpu_load_generator_tests_with_mock {

class CpuLoadGeneratorTestsWithMock : public ::testing::Test {
 public:
  CpuLoadGeneratorTestsWithMock()
      :
      cmd_arguments { new tension_cpu::CmdArguments },
      variables_for_cpu_generator_mock { new tension_cpu_mocks::VariablesForCpuLoadGeneratorMock },
      variables_for_cpu_benchmarker { new  tension_cpu::VariablesForCpuBenchmarker},
      cpu_benchmarkermock { new tension_cpu_mocks::CpuBenchmarkerMock },
      variables_for_cpu_speed_detector {new tension_cpu::VariablesForCpuSpeedDetector},
      cpu_speed_detector_mock { new tension_cpu_mocks::CpuSpeedDetectorMock},
      cpu_load_generator { new tension_cpu::CpuLoadGenerator { cmd_arguments, variables_for_cpu_generator_mock, cpu_benchmarkermock, cpu_speed_detector_mock } } {
  }

  std::shared_ptr<tension_cpu::CmdArguments> cmd_arguments;
  std::shared_ptr<tension_cpu_mocks::VariablesForCpuLoadGeneratorMock> variables_for_cpu_generator_mock;
  std::shared_ptr<tension_cpu::VariablesForCpuBenchmarker> variables_for_cpu_benchmarker;
  std::shared_ptr<tension_cpu_mocks::CpuBenchmarkerMock> cpu_benchmarkermock;
  std::shared_ptr<tension_cpu::IVariablesForCpuSpeedDetector> variables_for_cpu_speed_detector;
  std::shared_ptr<tension_cpu_mocks::CpuSpeedDetectorMock> cpu_speed_detector_mock;
  std::unique_ptr<tension_cpu::ICpuLoadGenerator> cpu_load_generator;

};

TEST_F(CpuLoadGeneratorTestsWithMock, Load_Generator_Started_And_Set_To_Be_Stopped_And_Main_Loop_Stopped) {
  EXPECT_CALL(*variables_for_cpu_generator_mock, SetCpuBusyLevel(_)).Times(1);
  EXPECT_CALL(*variables_for_cpu_generator_mock, SetCpuSlice(_)).Times(1);
  EXPECT_CALL(*cpu_speed_detector_mock, GetLoopsPerSecond()).WillOnce(Return(1));
  EXPECT_CALL(*variables_for_cpu_generator_mock, GetContinueCpuLoad()).WillOnce(Return(false));
  cpu_load_generator->Start();
}

} /*namespace cpu_load_generator_tests_with_mock*/
