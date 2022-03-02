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

#include <memory>

#include "Cpu-Benchmarker.h"

namespace tension_cpu {

#define  CALIBRATION_PERIOD   5

class CpuSpeedDetector : public ICpuSpeedDetector {
 public:
  CpuSpeedDetector()
      :
      loops_per_second { 0 },
      load_slice { 1.0 },
      cpu_benchmarker_ { new CpuBenchmarker } {
  }
  bool Start() override {
  }

  uint64_t GetLoopsPerSecond() override {
/*    cpu_benchmarker_->GetLoadSlice();
    cpu_benchmarker_->SetLoadSlice(load_slice);*/

    uint64_t   loops;
    time_t period;

    printf ("calibrating cpu speed:");
    fflush(stdout);

    do
    {
       loops = 1000 * 1000;

       while (loops)
       {
          uint64_t loop = 0;

          period = time(NULL);
          while (loop < loops)
          {
             /*cpu_load_slice();*/
             cpu_benchmarker_->Start();
             loop++;
          }
          period = time(NULL) - period;

          if (period >= CALIBRATION_PERIOD)
             break;
          else if ( 0 == period )
             loops *= 10;
          else
             loops *= 1 + CALIBRATION_PERIOD / period;
       }

       if ( loops )
          break;
       else {
          /*s_slice *= 10.0;*/
          load_slice = cpu_benchmarker_->GetLoadSlice();
          cpu_benchmarker_->SetLoadSlice( load_slice * 10.0 );
       }
    } while ( 1 );

    /*s_loops = loops / period;*/
    loops_per_second = loops / period;
    printf (" %llu loops per second\n", loops_per_second);

  }

  uint64_t loops_per_second;
  double load_slice;

 private:
  std::unique_ptr<ICpuBenchmarker> cpu_benchmarker_;
};

} /*namespace tension_cpu*/

#endif /* SOURCE_CPU_SPEED_DETECTOR_H_ */
