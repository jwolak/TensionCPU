/*
 * Variables-For-Cpu-Speed-Detector-Mock.h
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

#ifndef SOURCE_MOCKS_VARIABLES_FOR_CPU_SPEED_DETECTOR_MOCK_H_
#define SOURCE_MOCKS_VARIABLES_FOR_CPU_SPEED_DETECTOR_MOCK_H_

#include "../../../TensionCPU/Source/Variables-For-Cpu-Speed-Detector.h"

#include "gmock/gmock.h"

namespace tension_cpu_mocks {

class VariablesForCpuSpeedDetectorMock : public tension_cpu::IVariablesForCpuSpeedDetector {
 public:
  MOCK_METHOD(uint64_t, GetLoopS, (), (override));
  MOCK_METHOD(time_t, GetPeriod, (), (override));
  MOCK_METHOD(uint64_t, GetLoop, (), (override));
  MOCK_METHOD(uint64_t, GetLoopsPerSecond, (), (override));
  MOCK_METHOD(double, GetLoadSlice, (), (override));
  MOCK_METHOD(void, SetLoopS, (uint64_t), (override));
  MOCK_METHOD(void, SetLoop, (uint64_t), (override));
  MOCK_METHOD(void, SetTimePeriod, (), (override));
  MOCK_METHOD(time_t, GetTimePeriodDiff, (), (override));
  MOCK_METHOD(void, SetLoadSlice, (double), (override));
  MOCK_METHOD(void, SetLoopsPerSecond, (uint64_t), (override));
  MOCK_METHOD(bool, CheckLoopSCounterNotZero, (), (override));
  MOCK_METHOD(bool, LoopSCounterSet, (), (override));
  MOCK_METHOD(void, IncreaseLoop, (uint64_t), (override));
  MOCK_METHOD(void, MulLoopS, (uint64_t), (override));
};

}/*namespace tension_cpu_mocks*/

#endif /* SOURCE_MOCKS_VARIABLES_FOR_CPU_SPEED_DETECTOR_MOCK_H_ */
