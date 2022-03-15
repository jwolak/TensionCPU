/*
 * Variables-For-Cpu-Speed-Detector.h
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

#ifndef SOURCE_VARIABLES_FOR_CPU_SPEED_DETECTOR_H_
#define SOURCE_VARIABLES_FOR_CPU_SPEED_DETECTOR_H_

#include "IVariables-For-Cpu-Speed-Detector.h"

namespace tension_cpu {

class VariablesForCpuSpeedDetector : public IVariablesForCpuSpeedDetector {
 public:
  VariablesForCpuSpeedDetector()
      :
      loops { 0 },
      period { NULL },
      loop { 0 },
      loops_per_second { 0 },
      load_slice { 0 } {
  }

  uint64_t GetLoopS() override { return loops; }
  time_t GetPeriod() override { return period; }
  uint64_t GetLoop() override { return loop; }
  uint64_t GetLoopsPerSecond() override { return loops_per_second; }
  double GetLoadSlice() override { return load_slice; }

  void SetLoopS(uint64_t loopS_value) override { loops = loopS_value; }
  void SetLoop(uint64_t loop_value) override { loop = loop_value; }
  void SetTimePeriod() override { period = time(NULL); }
  time_t GetTimePeriodDiff() override { period =  time(NULL) - period; return period; }
  void SetLoadSlice(double load_slice_value) override { load_slice = load_slice_value; }
  void SetLoopsPerSecond (uint64_t loops_per_second_value) override { loops_per_second =  loops_per_second_value; }
  bool CheckLoopSCounterNotZero() override { return loops > 0; }
  bool LoopSCounterSet() override { return loops != 0; }

  uint64_t loops;
  time_t period;
  uint64_t loop;
  uint64_t loops_per_second;
  double load_slice;

};

} /*namespace tension_cpu*/

#endif /* SOURCE_VARIABLES_FOR_CPU_SPEED_DETECTOR_H_ */
