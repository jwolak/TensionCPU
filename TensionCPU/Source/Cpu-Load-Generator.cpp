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
  variables_for_cpu_generator_->SetContinueCpuLoad(false);
  LOG_DEBUG("%s", "continue_cpu_load_ set to false");
  LOG_DEBUG("%s", "CpuLoadGenerator set to stop");
}

void tension_cpu::CpuLoadGenerator::Start(void) {

  variables_for_cpu_generator_->SetCpuBusyLevel(cmd_arguments_->cpu_load);
  LOG_DEBUG("cmd_arguments_->cpu_load: %d, File: %s, Line: %d", cmd_arguments_->cpu_load, __FILE__, __LINE__);

  variables_for_cpu_generator_->SetCpuSlice(cpu_speed_detector_->GetLoopsPerSecond() / 100);

  LOG_DEBUG("%s %d [%]", "CpuLoadGenerator generates CPU load: ", cmd_arguments_->cpu_load);

  while (variables_for_cpu_generator_->GetContinueCpuLoad()) {
    variables_for_cpu_generator_->SetCpuIdleLevel(100 - variables_for_cpu_generator_->GetCpuBusyLevel());

    while ((variables_for_cpu_generator_->GetCpuBusyLevel() || variables_for_cpu_generator_->GetCpuIdleLevel()) && variables_for_cpu_generator_->GetContinueCpuLoad()) {
      if (variables_for_cpu_generator_->GetCpuBusyLevel()) {

        variables_for_cpu_generator_->SetCpuLoop(0);
        while ((variables_for_cpu_generator_->GetCpuLoop() < variables_for_cpu_generator_->GetCpuSlice()) && variables_for_cpu_generator_->GetContinueCpuLoad()) {
          cpu_benchmarker_->Run();
          variables_for_cpu_generator_->SetCpuLoop(variables_for_cpu_generator_->GetCpuLoop() + 1 );
        }
          variables_for_cpu_generator_->SetCpuBusyLevel(variables_for_cpu_generator_->GetCpuBusyLevel() - 1);
      }

      variables_for_cpu_generator_->SetCpuIdleLevel(cpu_benchmarker_->GenerateIdle(variables_for_cpu_generator_->GetCpuIdleLevel()));
    }
  }

}

