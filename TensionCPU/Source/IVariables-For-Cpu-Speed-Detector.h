/*
 * IVariables-For-Cpu-Speed-Detector.h
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

#ifndef SOURCE_IVARIABLES_FOR_CPU_SPEED_DETECTOR_H_
#define SOURCE_IVARIABLES_FOR_CPU_SPEED_DETECTOR_H_

#include <cstdint>
#include <time.h>

namespace tension_cpu {

class IVariablesForCpuSpeedDetector {
 public:
  virtual ~IVariablesForCpuSpeedDetector() = default;
  virtual uint64_t GetLoopS(void) = 0;
  virtual time_t GetPeriod(void) = 0;
  virtual uint64_t GetLoop(void) = 0;
  virtual uint64_t GetLoopsPerSecond() = 0;
  virtual double GetLoadSlice(void) = 0;

  virtual void SetLoopS(uint64_t) = 0;
  virtual void SetLoop(uint64_t) = 0;
  virtual void SetTimePeriod(void) = 0;
  virtual time_t GetTimePeriodDiff(void) = 0;
  virtual void SetLoadSlice(double) = 0;
  virtual void SetLoopsPerSecond (uint64_t) = 0;
  virtual bool CheckLoopSCounterNotZero() = 0;
  virtual bool LoopSCounterSet() = 0;
  virtual void IncreaseLoop(uint64_t) = 0;
  virtual void MulLoopS(uint64_t) = 0;
};

} /*namespace tension_cpu*/

#endif /* SOURCE_IVARIABLES_FOR_CPU_SPEED_DETECTOR_H_ */