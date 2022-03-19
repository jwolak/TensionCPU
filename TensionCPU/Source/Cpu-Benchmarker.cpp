/*
 * Cpu-Benchmarker.cpp
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

#include "Cpu-Benchmarker.h"
#include "Logger.h"

#include <unistd.h>

const int32_t kSleepTime = 10 * 1000;

void tension_cpu::CpuBenchmarker::Run() {
/*  LOG_DEBUG("%s", "CpuBenchmarker::Run");
  LOG_DEBUG("variables_for_cpu_benchmarker_->load: %f, %s, Line: %d", variables_for_cpu_benchmarker_->load, __FILE__, __LINE__);
  LOG_DEBUG("variables_for_cpu_benchmarker_->load_slice: %f, %s, Line: %d", variables_for_cpu_benchmarker_->load_slice, __FILE__, __LINE__);*/

  while (variables_for_cpu_benchmarker_->load < variables_for_cpu_benchmarker_->load_slice) {
    variables_for_cpu_benchmarker_->load += 1.0;
  }

/*  LOG_DEBUG("variables_for_cpu_benchmarker_->load: %f,  %s, Line: %d", variables_for_cpu_benchmarker_->load, __FILE__, __LINE__ );*/
}

void tension_cpu::CpuBenchmarker::SetLoadSlice(double load_s) {
/*  LOG_DEBUG("%s", "CpuBenchmarker::SetLoadSlice()");
  LOG_DEBUG("load_s: %f", load_s);*/

  variables_for_cpu_benchmarker_->load_slice = load_s;

/*  LOG_DEBUG("variables_for_cpu_benchmarker_->load_slice: %f, %s, Line: %d", variables_for_cpu_benchmarker_->load_slice, __FILE__, __LINE__ );*/
}

double tension_cpu::CpuBenchmarker::GetLoadSlice(void) {
/*  LOG_DEBUG("%s", "CpuBenchmarker::GetLoadSlice");
  LOG_DEBUG("variables_for_cpu_benchmarker_->load_slice: %f, %s, Line: %d", variables_for_cpu_benchmarker_->load_slice, __FILE__, __LINE__ );*/

  return variables_for_cpu_benchmarker_->load_slice;
}

uint32_t tension_cpu::CpuBenchmarker::GenerateIdle(const uint32_t cpu_idle) {
/*
  LOG_DEBUG("%s", "CpuBenchmarker::GenerateIdle");
  LOG_DEBUG("cpu_idle: %d, %s, Line: %d", cpu_idle, __FILE__, __LINE__ );
*/

  variables_for_cpu_benchmarker_->tmp_cpu_idle = cpu_idle;
/*  LOG_DEBUG("variables_for_cpu_benchmarker_->tmp_cpu_idle: %d, %s, Line: %d", variables_for_cpu_benchmarker_->tmp_cpu_idle, __FILE__, __LINE__ );*/
  if (variables_for_cpu_benchmarker_->tmp_cpu_idle > 0) {
    /* sleeping for 10 ms */
    /*LOG_DEBUG("Sleep for: %d [us], %s, Line: %d", kSleepTime, __FILE__, __LINE__);*/
    usleep(kSleepTime);
    variables_for_cpu_benchmarker_->tmp_cpu_idle--;
  }

  /*LOG_DEBUG("variables_for_cpu_benchmarker_->tmp_cpu_idle: %d, %s, Line: %d", variables_for_cpu_benchmarker_->tmp_cpu_idle, __FILE__, __LINE__ );*/
  return variables_for_cpu_benchmarker_->tmp_cpu_idle;
}
