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
#include "EquinoxLogger.h"

tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::ParsedCmdArgumentsLogic()
: scheduling_mode_type {},
  cpu_load {},
  test_time {},
  debug_mode {} {
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::SetScheduligMode(tension_cpu::cmd_arguments_parser::SchedulingModeType sched_mode_type) {
  scheduling_mode_type = sched_mode_type;

  switch(scheduling_mode_type) {
    case tension_cpu::cmd_arguments_parser::SchedulingModeType::BATCH:
      equinox::trace("[ParsedCmdArgumentsLogic] Scheduling mode set to: BATCH");
      break;
    case tension_cpu::cmd_arguments_parser::SchedulingModeType::FIFO:
      equinox::trace("[ParsedCmdArgumentsLogic] Scheduling mode set to: FIFO");
      break;
    case tension_cpu::cmd_arguments_parser::SchedulingModeType::OTHER:
      equinox::trace("[ParsedCmdArgumentsLogic] Scheduling mode set to: OTHER");
      break;
    case tension_cpu::cmd_arguments_parser::SchedulingModeType::RR:
      equinox::trace("[ParsedCmdArgumentsLogic] Scheduling mode set to: RR");
      break;
  }
}

tension_cpu::cmd_arguments_parser::SchedulingModeType tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::GetScheduligMode() {
  return scheduling_mode_type;
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::SetLoad(int32_t load) {
  cpu_load = load;
  equinox::trace("[ParsedCmdArgumentsLogic] Cpu load set to: [%d%]", load);
}

int32_t tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::GetLoad() {
  return cpu_load;
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::SetTestTime(std::chrono::seconds time) {
  test_time = time;
  equinox::trace("[ParsedCmdArgumentsLogic] Test time set to: [%ds]", test_time);
}

std::chrono::seconds tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::GetTestTime() {
  return test_time;
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::SetDebugMode(DebugModeType debug_mode_to_set) {
  debug_mode = debug_mode_to_set;

  switch (debug_mode) {
    case tension_cpu::cmd_arguments_parser::DebugModeType::CRITICAL:
      equinox::trace("[ParsedCmdArgumentsLogic] Debug mode set to: CRITICAL");
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::DEBUG:
      equinox::trace("[ParsedCmdArgumentsLogic] Debug mode set to: DEBUG");
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::ERROR:
      equinox::trace("[ParsedCmdArgumentsLogic] Debug mode set to: ERROR");
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::INFO:
      equinox::trace("[ParsedCmdArgumentsLogic] Debug mode set to: INFO");
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::TRACE:
      equinox::trace("[ParsedCmdArgumentsLogic] Debug mode set to: TRACE");
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::WARNING:
      equinox::trace("[ParsedCmdArgumentsLogic] Debug mode set to: WARNING");
      break;
  }
}

tension_cpu::cmd_arguments_parser::DebugModeType tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::GetDebugMode() {
  return debug_mode;
}
