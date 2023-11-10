/*
 * ParsedCmdArguments.cpp
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

#include "ParsedCmdArguments.h"
#include "EquinoxLogger.h"

#include <cstring>

void tension_cpu::cmd_arguments_parser::ParsedCmdArguments::SetScheduligMode(const char* sched_mode)
{
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] SetScheduligMode() called", __FILENAME__, __LINE__);
#endif

  if( strncmp(sched_mode, "b", 2) == 0) {
    parsed_cmd_arguments_logic_.SetScheduligMode(tension_cpu::cmd_arguments_parser::SchedulingModeType::BATCH);
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Scheduling mode set to BATCH", __FILENAME__, __LINE__);
#endif
  }

  if( strncmp(sched_mode, "f", 2) == 0) {
    parsed_cmd_arguments_logic_.SetScheduligMode(tension_cpu::cmd_arguments_parser::SchedulingModeType::FIFO);
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Scheduling mode set to FIFO", __FILENAME__, __LINE__);
#endif
  }

  if( strncmp(sched_mode, "r", 2) == 0) {
    parsed_cmd_arguments_logic_.SetScheduligMode(tension_cpu::cmd_arguments_parser::SchedulingModeType::RR);
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Scheduling mode set to RR", __FILENAME__, __LINE__);
#endif
  }

  if( strncmp(sched_mode, "o", 2) == 0) {
    parsed_cmd_arguments_logic_.SetScheduligMode(tension_cpu::cmd_arguments_parser::SchedulingModeType::OTHER);
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Scheduling mode set to OTHER", __FILENAME__, __LINE__);
#endif
  }

}

tension_cpu::cmd_arguments_parser::SchedulingModeType tension_cpu::cmd_arguments_parser::ParsedCmdArguments::GetScheduligMode()
{
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] GetScheduligMode() called", __FILENAME__, __LINE__);
#endif

   return parsed_cmd_arguments_logic_.GetScheduligMode();
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArguments::SetLoad(int load)
{
  parsed_cmd_arguments_logic_.SetLoad(load);

#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] SetLoad() called", __FILENAME__, __LINE__);
#endif
}

int tension_cpu::cmd_arguments_parser::ParsedCmdArguments::GetLoad()
{
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] GetLoad() called", __FILENAME__, __LINE__);
#endif

  return parsed_cmd_arguments_logic_.GetLoad();
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArguments::SetTestTime(std::chrono::seconds time)
{
  parsed_cmd_arguments_logic_.SetTestTime(time);

#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] SetTestTime() called", __FILENAME__, __LINE__);
#endif
}

std::chrono::seconds tension_cpu::cmd_arguments_parser::ParsedCmdArguments::GetTestTime()
{
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] GetTestTime() called", __FILENAME__, __LINE__);
#endif

  return parsed_cmd_arguments_logic_.GetTestTime();
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArguments::SetDebugMode(int debug_mode_level) {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] SetDebugMode() called", __FILENAME__, __LINE__);
#endif

      switch(debug_mode_level) {
        case 1:
          parsed_cmd_arguments_logic_.SetDebugMode(DebugModeType::CRITICAL);
#ifdef VERBOSE_LOGS
          equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Set debug mode to CRITICAL", __FILENAME__, __LINE__);
#endif
          break;

        case 2:
          parsed_cmd_arguments_logic_.SetDebugMode(DebugModeType::ERROR);
#ifdef VERBOSE_LOGS
          equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Set debug mode to ERROR", __FILENAME__, __LINE__);
#endif
          break;

        case 3:
          parsed_cmd_arguments_logic_.SetDebugMode(DebugModeType::WARNING);
#ifdef VERBOSE_LOGS
          equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Set debug mode to WARNING", __FILENAME__, __LINE__);
#endif
          break;

        case 4:
          parsed_cmd_arguments_logic_.SetDebugMode(DebugModeType::INFO);
#ifdef VERBOSE_LOGS
          equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Set debug mode to INFO", __FILENAME__, __LINE__);
#endif
          break;

        case 5:
          parsed_cmd_arguments_logic_.SetDebugMode(DebugModeType::DEBUG);
#ifdef VERBOSE_LOGS
          equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Set debug mode to DEBUG", __FILENAME__, __LINE__);
#endif
          break;

        case 6:
          parsed_cmd_arguments_logic_.SetDebugMode(DebugModeType::TRACE);
#ifdef VERBOSE_LOGS
          equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] Set debug mode to TRACE", __FILENAME__, __LINE__);
#endif
          break;
      }
}

tension_cpu::cmd_arguments_parser::DebugModeType tension_cpu::cmd_arguments_parser::ParsedCmdArguments::GetDebugMode() {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] GetDebugMode() called", __FILENAME__, __LINE__);
#endif
  return parsed_cmd_arguments_logic_.GetDebugMode();
}

void tension_cpu::cmd_arguments_parser::ParsedCmdArguments::SetNumberOfCores(int number_of_cores_to_set) {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] SetNumberOfCores() called", __FILENAME__, __LINE__);
#endif
      parsed_cmd_arguments_logic_.SetNumberOfCores(number_of_cores_to_set);
}

int tension_cpu::cmd_arguments_parser::ParsedCmdArguments::GetNumberOfCores() {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParsedCmdArguments] GetNumberOfCores() called", __FILENAME__, __LINE__);
#endif
      return parsed_cmd_arguments_logic_.GetNumberOfCores();
}
