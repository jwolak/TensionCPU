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
#include <mutex>

#include <cstdint>
#include <unistd.h>
#include <cstdio>

#include "Cmd-Arguments.h"
#include "Cpu-Speed-Detector.h"
#include "Variables-For-Cpu-Load-Generator.h"

namespace tension_cpu {

class CpuLoadGenerator : public ICpuLoadGenerator {
 public:
  CpuLoadGenerator(std::shared_ptr<CmdArguments> cmd_arguments,
                   std::shared_ptr<VariablesForCpuLoadGenerator> variables_for_cpu_generator,
                   std::shared_ptr<ICpuBenchmarker> cpu_benchmarker,
                   std::shared_ptr<ICpuSpeedDetector> cpu_speed_detector)
      :
      cmd_arguments_ { cmd_arguments },
      variables_for_cpu_generator_ { variables_for_cpu_generator },
      cpu_benchmarker_ { cpu_benchmarker },
      cpu_speed_detector_ { cpu_speed_detector },
      mutex_ { } {
  }

  void Start(void) override;
  void Stop(void) override;

 private:
  std::shared_ptr<CmdArguments> cmd_arguments_;
  std::shared_ptr<VariablesForCpuLoadGenerator> variables_for_cpu_generator_;
  std::shared_ptr<ICpuBenchmarker> cpu_benchmarker_;
  std::shared_ptr<ICpuSpeedDetector> cpu_speed_detector_;
  std::mutex mutex_;

  bool GetCpuLoadGeneratorStatus() {
    return variables_for_cpu_generator_->GetContinueCpuLoad();
  }
};

} /*namespace tension_cpu*/

#endif /* SOURCE_CPU_LOAD_GENERATOR_H_ */
