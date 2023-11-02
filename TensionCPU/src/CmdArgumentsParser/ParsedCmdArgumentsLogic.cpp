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

#include <cstring>

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
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Scheduling mode set to: BATCH", __FILENAME__, __LINE__);
#endif
      break;
    case tension_cpu::cmd_arguments_parser::SchedulingModeType::FIFO:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Scheduling mode set to: FIFO", __FILENAME__, __LINE__);
#endif
      break;
    case tension_cpu::cmd_arguments_parser::SchedulingModeType::OTHER:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Scheduling mode set to: OTHER", __FILENAME__, __LINE__);
#endif
      break;
    case tension_cpu::cmd_arguments_parser::SchedulingModeType::RR:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Scheduling mode set to: RR", __FILENAME__, __LINE__);
#endif
      break;
  }
}

tension_cpu::cmd_arguments_parser::SchedulingModeType tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::GetScheduligMode() {
#ifdef VERBOSE_LOGS
  equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] GetScheduligMode() called", __FILENAME__, __LINE__);
#endif
  return scheduling_mode_type;
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::SetLoad(int32_t load) {
  cpu_load = load;
#ifdef VERBOSE_LOGS
  equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Cpu load set to: [%d%]", load, __FILENAME__, __LINE__);
#endif
}

int32_t tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::GetLoad() {
#ifdef VERBOSE_LOGS
  equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] GetLoad() called", __FILENAME__, __LINE__);
#endif
  return cpu_load;
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::SetTestTime(std::chrono::seconds time) {
  test_time = time;
#ifdef VERBOSE_LOGS
  equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Test time set to: [%ds]", test_time, __FILENAME__, __LINE__);
#endif
}

std::chrono::seconds tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::GetTestTime() {
#ifdef VERBOSE_LOGS
  equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] GetTestTime() called", __FILENAME__, __LINE__);
#endif
  return test_time;
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::SetDebugMode(DebugModeType debug_mode_to_set) {
  debug_mode = debug_mode_to_set;

  switch (debug_mode) {
    case tension_cpu::cmd_arguments_parser::DebugModeType::CRITICAL:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Debug mode set to: CRITICAL", __FILENAME__, __LINE__);
#endif
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::DEBUG:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Debug mode set to: DEBUG", __FILENAME__, __LINE__);
#endif
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::ERROR:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Debug mode set to: ERROR", __FILENAME__, __LINE__);
#endif
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::INFO:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Debug mode set to: INFO", __FILENAME__, __LINE__);
#endif
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::TRACE:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Debug mode set to: TRACE", __FILENAME__, __LINE__);
#endif
      break;
    case tension_cpu::cmd_arguments_parser::DebugModeType::WARNING:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] Debug mode set to: WARNING", __FILENAME__, __LINE__);
#endif
      break;
  }
}

tension_cpu::cmd_arguments_parser::DebugModeType tension_cpu::cmd_arguments_parser::ParsedCmdArgumentsLogic::GetDebugMode() {
#ifdef VERBOSE_LOGS
  equinox::trace("%s, File: %s, Line: %d", "[ParsedCmdArgumentsLogic] GetDebugMode() called", __FILENAME__, __LINE__);
#endif
  return debug_mode;
}
