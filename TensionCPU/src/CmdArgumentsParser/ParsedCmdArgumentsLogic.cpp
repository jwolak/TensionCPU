/*
 * ParsedCmdArgumentsLogic.cpp
 *
 *  Created on: 2023
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2023, Janusz Wolak
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

#include "ParsedCmdArgumentsLogic.h"

tension_cpu::ParsedCmdArgumentsLogic::ParsedCmdArgumentsLogic()
: scheduling_mode_type {},
  cpu_load {},
  test_time {} {
}

void tension_cpu::ParsedCmdArgumentsLogic::SetScheduligMode(tension_cpu::SchedulingModeType sched_mode_type) {
  scheduling_mode_type = sched_mode_type;
}

tension_cpu::SchedulingModeType tension_cpu::ParsedCmdArgumentsLogic::GetScheduligMode() {
  return scheduling_mode_type;
}

void tension_cpu::ParsedCmdArgumentsLogic::SetLoad(int32_t load) {
  cpu_load = load;
}

int32_t tension_cpu::ParsedCmdArgumentsLogic::GetLoad() {
  return cpu_load;
}

void tension_cpu::ParsedCmdArgumentsLogic::SetTestTime(std::chrono::seconds time) {
  test_time = time;
}

std::chrono::seconds tension_cpu::ParsedCmdArgumentsLogic::GetTestTime() {
  return test_time;
}
