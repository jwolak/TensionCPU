/*
 * Cpu-Benchmark.cpp
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


#include "Cpu-Benchmark.h"
#include "Logger.h"

#include <iostream>

void tension_cpu::CpuBenchmark::DetectCpuSpeed() {

  unsigned long long   loops;
  time_t period;

  std::cout<<"TensionCPU detects Your CPU speed..."<<std::endl;
  LOG_DEBUG("%s", "CpuBenchmark detects CPU speed");
  fflush(stdout);

  do
  {
     loops = 1000 * 1000;

     while (loops)
     {
       unsigned long long loop = 0;

        period = time(NULL);
        while (loop < loops)
        {
          unit_cpu_load_producer_->ProduceMinimalCpuLoad();
           loop++;
        }
        period = time(NULL) - period;

        if (period >= cpu_load_generator_shared_data_->CALIBRATION_PERIOD)
           break;
        else if ( 0 == period ) {
           loops *= 10;
        }
        else {
           loops *= 1 + cpu_load_generator_shared_data_->CALIBRATION_PERIOD / period;
        }
     }

     if ( loops )
        break;
     else {
       cpu_load_generator_shared_data_->s_slice *= 10.0;
     }
  } while ( 1 );

  cpu_load_generator_shared_data_->s_loops = loops / period;
  LOG_DEBUG("%s%lld%s", "CPU can run: ", cpu_load_generator_shared_data_->s_loops, " per second");
  std::cout<<"Your CPU can run "<<cpu_load_generator_shared_data_->s_loops<<" loops per second"<<std::endl;
}

