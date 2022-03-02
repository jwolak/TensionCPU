/*
 * Cpu-Load-Generator.h
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

#ifndef SOURCE_CPU_LOAD_GENERATOR_H_
#define SOURCE_CPU_LOAD_GENERATOR_H_

#include "ICpu-Load-Generator.h"

#include <memory>

#include <cstdint>
#include <unistd.h>
#include <cstdio>

#include "Cmd-Arguments.h"
#include "Cpu-Speed-Detector.h"

namespace tension_cpu {

class CpuLoadGenerator : public ICpuLoadGenerator {
 public:
  CpuLoadGenerator(std::shared_ptr<CmdArguments> cmd_arguments)
      :
      cmd_arguments_ { cmd_arguments },
      cpu_speed_detector_ { new CpuSpeedDetector }
      {}

  void Start(void) override {
    /*cpu_speed_detector_->GetLoopsPerSecond();*/
    /*cpu_benchmarker_->Start();*/

    uint32_t load = cmd_arguments_->cpu_load;

    const uint64_t slice = cpu_speed_detector_->GetLoopsPerSecond() / 100;/*s_loops / 100;*/
    static const char show[] = "-\\|/";
    unsigned stage = 0;

    printf ("generate %u%c cpu load\n", load, '%');
    while (1)
    {
       unsigned busy = (load ? load : (0 == (random() & 1) ? 100 : 50));
       unsigned idle = 100 - busy;

       printf("\r%c", show[stage]);
       fflush(stdout);
       if ( !show[++stage] )
          stage = 0;

       while (busy || idle)
       {
          if ( busy )
          {
             /* try to be produce load for 10 ms */
             uint64_t loop = 0;
             while (loop < slice)
             {
                /*cpu_load_slice();*/
                cpu_benchmarker_->Start();
                loop++;
             }
             busy--;
          }

          if ( idle )
          {
             /* sleeping for 10 ms */
             usleep(10 * 1000);
             idle--;
          }
       }
    }

  }

  void Stop(void) override {
  }

 private:
  std::shared_ptr<CmdArguments> cmd_arguments_;
  std::unique_ptr<ICpuBenchmarker> cpu_benchmarker_;
  std::unique_ptr<ICpuSpeedDetector> cpu_speed_detector_;
};

} /*namespace tension_cpu*/

#endif /* SOURCE_CPU_LOAD_GENERATOR_H_ */
