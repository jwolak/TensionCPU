/*
 * Cpu-Load-Generator.cpp
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

#include "Cpu-Load-Generator.h"
#include "Logger.h"


 void tension_cpu::CpuLoadGenerator::Stop(void) {
  std::lock_guard<std::mutex> lock(mutex_);
  continue_cpu_load_ = false;
  LOG_DEBUG("%s", "continue_cpu_load_ set to false");
  LOG_DEBUG("%s", "CpuLoadGenerator set to stop");
}

void tension_cpu::CpuLoadGenerator::Start(void) {

  uint32_t load = cmd_arguments_->cpu_load;
  LOG_DEBUG("cmd_arguments_->cpu_load: %d, File: %s, Line: %d",cmd_arguments_->cpu_load, __FILE__, __LINE__);

  cpu_speed_detector_->Run();
  const uint64_t slice = cpu_speed_detector_->GetLoopsPerSecond() / 100;

  LOG_DEBUG("%s %d [%]", "CpuLoadGenerator generates CPU load: ", load);

  while (GetCpuLoadGeneratorStatus()) {
    unsigned busy = (load ? load : (0 == (random() & 1) ? 100 : 50));
    unsigned idle = 100 - busy;

    while ((busy || idle) && GetCpuLoadGeneratorStatus()) {
      if (busy) {
        /* try to be produce load for 10 ms */
        uint64_t loop = 0;
        while ((loop < slice) && GetCpuLoadGeneratorStatus()) {
          cpu_benchmarker_->Run();
          loop++;
        }
        busy--;
      }

      cpu_benchmarker_->GenerateIdle(idle);
    }
  }

}


