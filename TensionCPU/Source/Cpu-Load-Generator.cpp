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
   LOG_DEBUG("%s", "CpuLoadGenerator stopped");
   timer_->Stop();
   load_generator_control_->SetContinueLoadGeneratorWork(false);
}

void tension_cpu::CpuLoadGenerator::Start(void) {

  LOG_DEBUG("%s", "CpuLoadGenerator started");

  load_generator_control_->SetContinueLoadGeneratorWork(true);
  cpu_benchmark_->DetectCpuSpeed();

  const unsigned long long slice = cpu_load_generator_shared_data_->s_loops / 100;
  unsigned stage = 0;

  std::cout << "TensionCPU generates " << cmd_arguments_->cpu_load << " [%] CPU load for " << cmd_arguments_->test_time.count() << " [s]" << std::endl;

  process_scheduler_->SetPolicyType(cmd_arguments_->scheduling_policy);
  timer_->SetPeriodTime(cmd_arguments_->test_time);
  timer_->Start();
  while (load_generator_control_->GetContinueLoadGeneratorWork()) {
    unsigned busy = (cmd_arguments_->cpu_load ? cmd_arguments_->cpu_load : (0 == (random() & 1) ? 100 : 50));
    unsigned idle = 100 - busy;

    while (busy || idle) {
      if (busy) {
        unsigned long long loop = 0;
        while (loop < slice) {
          unit_cpu_load_producer_->ProduceMinimalCpuLoad();
          loop++;
        }
        busy--;
      }

      if (idle) {
        std::this_thread::sleep_for(std::chrono::milliseconds{10});
        idle--;
      }
    }
  }
}

