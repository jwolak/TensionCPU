/*
 * Cpu-Benchmarker-Tests.cpp
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


#include "../../../TensionCPU/Source/Variables-For-Cpu-Benchmarker.h"

#include <gtest/gtest.h>

#include <memory>

namespace cpu_benchmarker_tests {

namespace {
const double kLoadDefaultValue = 1.0;
const double kLoadLessThenLoadSlice = 0.5;
const double kLoadIncreaseStepValue =1.0;
const double kLoadSliceValue = 4.0;
const int32_t kTempCpuIdle = 10;
const int32_t kTempCpuIdleEqualZero = 0;
}

class CpuBenchmarkerTests : public ::testing::Test {
 public:
  CpuBenchmarkerTests()
      :
      variables_for_cpu_benchmarker_ { new tension_cpu::VariablesForCpuBenchmarker },
      cpu_benchmarker { new tension_cpu::CpuBenchmarker { variables_for_cpu_benchmarker_ } } {
  }

  std::shared_ptr<tension_cpu::VariablesForCpuBenchmarker> variables_for_cpu_benchmarker_;
  std::unique_ptr<tension_cpu::ICpuBenchmarker> cpu_benchmarker;
};


TEST_F(CpuBenchmarkerTests, Load_Is_Default_1_0_Value_And_Launch_Run_Method_And_Then_Load_Stil_Is_Set_To_1_0) {
  cpu_benchmarker->Run();
  ASSERT_EQ(variables_for_cpu_benchmarker_->load, kLoadDefaultValue);
}

TEST_F(CpuBenchmarkerTests, Load_Is_Less_Than_Load_Slice_And_Run_Method_Then_Load_Is_Increased_By_One ) {
  variables_for_cpu_benchmarker_->load = kLoadLessThenLoadSlice;
  cpu_benchmarker->Run();
  ASSERT_EQ(variables_for_cpu_benchmarker_->load, kLoadLessThenLoadSlice + kLoadIncreaseStepValue);
}

TEST_F(CpuBenchmarkerTests, Load_Is_Default_1_0_Value_And_LoadSlice_Has_Grater_Value_Then_Launch_Run_Method_And_Then_Load_Is_Set_To_2_0) {
  variables_for_cpu_benchmarker_->load_slice = 2 * kLoadDefaultValue;
  cpu_benchmarker->Run();
  ASSERT_EQ(variables_for_cpu_benchmarker_->load, kLoadDefaultValue + 1);
}

TEST_F(CpuBenchmarkerTests, Call_SetLoadSlice_And_Load_Slice_Is_Set) {
  cpu_benchmarker->SetLoadSlice(kLoadSliceValue);
  ASSERT_EQ(variables_for_cpu_benchmarker_->load_slice, kLoadSliceValue);
}

TEST_F(CpuBenchmarkerTests,Set_LoadSlice_To_Value_And_Call_GetLoadSlice_Then_Same_Value_Is_Returned ) {
  variables_for_cpu_benchmarker_->load_slice = kLoadSliceValue;
  ASSERT_EQ(cpu_benchmarker->GetLoadSlice(), kLoadSliceValue);
}

TEST_F(CpuBenchmarkerTests, TempCpuIdle_Set_To_Value_Call_GenerateIdle_Then_TemCpuIdle_Decreased_By_One) {
  cpu_benchmarker->GenerateIdle(kTempCpuIdle);
  ASSERT_EQ(variables_for_cpu_benchmarker_->tmp_cpu_idle, kTempCpuIdle - 1);
}

TEST_F(CpuBenchmarkerTests, TempCpuIdle_Set_To_Zero_Call_GenerateIdle_Then_TemCpuIdle_Equal_Zero) {
  cpu_benchmarker->GenerateIdle(kTempCpuIdleEqualZero);
  ASSERT_EQ(variables_for_cpu_benchmarker_->tmp_cpu_idle, kTempCpuIdleEqualZero);
}

} /*namespace cpu_benchmarker_tests */
