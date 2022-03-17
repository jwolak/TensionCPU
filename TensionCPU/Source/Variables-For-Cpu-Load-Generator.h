/*
 * Variables-For-Cpu-Load-Generator.h
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

#ifndef SOURCE_VARIABLES_FOR_CPU_LOAD_GENERATOR_H_
#define SOURCE_VARIABLES_FOR_CPU_LOAD_GENERATOR_H_

#include "IVariables-For-Cpu-Load-Generator.h"

#include <cstdint>
#include <mutex>

namespace tension_cpu {

class VariablesForCpuLoadGenerator : public IVariablesForCpuLoadGenerator {
 public:
  VariablesForCpuLoadGenerator()
      :
      continue_cpu_load { true },
      cpu_busy_level { 0 },
      cpu_slice { 0 },
      cpu_idle_level { 0 },
      cpu_loop { 0 } {
  }

  bool GetContinueCpuLoad() override {
    std::lock_guard<std::mutex> lock(mutex_);
    return continue_cpu_load;
  }

  void SetContinueCpuLoad(bool status_to_be_set) override {
    std::lock_guard<std::mutex> lock(mutex_);
    continue_cpu_load = status_to_be_set;
  }

  int32_t GetCpuBusyLevel() override {
    return cpu_busy_level;
  }

  void SetCpuBusyLevel(int32_t busy_level_to_be_set) override {
    cpu_busy_level = busy_level_to_be_set;
  }

  uint64_t GetCpuSlice() override {
    return cpu_slice;
  }

  void SetCpuSlice(uint64_t cpu_slice_to_be_set) override {
    cpu_slice = cpu_slice_to_be_set;
  }

  uint32_t GetCpuIdleLevel() override {
    return cpu_idle_level;
  }

  void SetCpuIdleLevel(uint32_t idle_level_to_be_set) override {
    cpu_idle_level = idle_level_to_be_set;
  }

  uint64_t GetCpuLoop() override {
    return cpu_loop;
  }

  void SetCpuLoop(uint64_t cpu_loop_to_be_set) override {
    cpu_loop = cpu_loop_to_be_set;
  }

  bool continue_cpu_load;
  int32_t cpu_busy_level;
  uint64_t cpu_slice;
  uint32_t cpu_idle_level;
  uint64_t cpu_loop;
  std::mutex mutex_;
};

} /*namespace tension_cpu*/

#endif /* SOURCE_VARIABLES_FOR_CPU_LOAD_GENERATOR_H_ */
