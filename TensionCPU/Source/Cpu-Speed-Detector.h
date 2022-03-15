/*
 * Cpu-Speed-Detector.h
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

#ifndef SOURCE_CPU_SPEED_DETECTOR_H_
#define SOURCE_CPU_SPEED_DETECTOR_H_

#include "ICpu-Speed-Detector.h"
#include "Logger.h"

#include <memory>

#include "Cpu-Benchmarker.h"
#include "Variables-For-Cpu-Speed-Detector.h"

namespace tension_cpu {

#define  CALIBRATION_PERIOD   5

class CpuSpeedDetector : public ICpuSpeedDetector {
 public:
  CpuSpeedDetector(std::shared_ptr<IVariablesForCpuSpeedDetector> variables_for_cpu_speed_detector, std::shared_ptr<ICpuBenchmarker> cpu_benchmarker)
      :
      variables_for_cpu_speed_detector_ { variables_for_cpu_speed_detector },
      cpu_benchmarker_ { cpu_benchmarker } {
  }

  uint64_t GetLoopsPerSecond() override {

    do {
      variables_for_cpu_speed_detector_->SetLoopS(1000 * 1000);

      while (variables_for_cpu_speed_detector_->LoopSCounterSet()) {
        variables_for_cpu_speed_detector_->SetLoop(0);

        variables_for_cpu_speed_detector_->SetTimePeriod();
        while (variables_for_cpu_speed_detector_->GetLoop() < variables_for_cpu_speed_detector_->GetLoopS()) {
          cpu_benchmarker_->Run();
          variables_for_cpu_speed_detector_->SetLoop(variables_for_cpu_speed_detector_->GetLoop() + 1);
        }

        if (variables_for_cpu_speed_detector_->GetTimePeriodDiff() >= CALIBRATION_PERIOD)
          break;
        else if (0 == variables_for_cpu_speed_detector_->GetPeriod()) {
          variables_for_cpu_speed_detector_->SetLoopS(variables_for_cpu_speed_detector_->GetLoopS() * 10);
        } else {
          variables_for_cpu_speed_detector_->SetLoopS(
              variables_for_cpu_speed_detector_->GetLoopS() * (1 + CALIBRATION_PERIOD) / variables_for_cpu_speed_detector_->GetPeriod());
        }
      }

      if (variables_for_cpu_speed_detector_->CheckLoopSCounterNotZero()) {
        break;
      } else {
        variables_for_cpu_speed_detector_->SetLoadSlice(cpu_benchmarker_->GetLoadSlice());
        cpu_benchmarker_->SetLoadSlice(variables_for_cpu_speed_detector_->GetLoadSlice() * 10.0);
      }
    } while (true);

    variables_for_cpu_speed_detector_->SetLoopsPerSecond(variables_for_cpu_speed_detector_->GetLoopS() / variables_for_cpu_speed_detector_->GetPeriod());

    return variables_for_cpu_speed_detector_->GetLoopsPerSecond();
  }

 private:
  std::shared_ptr<ICpuBenchmarker> cpu_benchmarker_;
  std::shared_ptr<IVariablesForCpuSpeedDetector> variables_for_cpu_speed_detector_;
};

} /*namespace tension_cpu*/

#endif /* SOURCE_CPU_SPEED_DETECTOR_H_ */
