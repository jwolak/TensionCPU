/*
 * CmdArgumentsParserLogic.cpp
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

#include "CmdArgumentsParserLogic.h"
#include "EquinoxLogger.h"

#include <cstring>
#include <memory>

namespace {

const char kVersionPrint[] = "\tTensionCpu version 2.0\n\n";

const char kHelpMenuPrint[] = "\t-l [--load]\n"
                               "\t-T [--Time]  [total time in sec]\n"
                               "\t-S [--Sched] [scheduling mode]\n"
                               "\t-D [--Debug] set Debug mode\n"
                               "\t-C [--Cores] [number of cores]\n"
                               "\t-h [--help]\n"
                               "\t-v [--version]\n\n"
                               "\t-l, --load               CPU load value in percentages\n"
                               "\t-T, --Time               total load time ['-T 0' -> sets unlimited time] \n"
                               "\t-D, --Debug               enable debug mode\n"
                               "\t-C, --Cores               set number of cores to be loaded\n"
                               "\t-h, --help                print help\n"
                               "\t-v, --version             print version\n\n"
                               "\tScheduling mode: [-S, --Sched] :\n"
                               "\t b, --batch               set SCHED_BATCH scheduler\n"
                               "\t f, --fifo                set SCHED_FIFO scheduler (real time)\n"
                               "\t r, --roundr              set SCHED_RR scheduler (real time)\n"
                               "\t o, --default             set SCHED_OTHER (default) scheduler\n\n"
                               "\tExample:  tensionCpu -l 90 -T 60 [90% CPU load for 60 seconds time]\n"
                               "\tExample:  tensionCpu --load 90 --Time 60 --Sched r\n";
}

tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::CmdArgumentsParserLogic(
    std::shared_ptr<tension_cpu::cmd_arguments_parser::IParsedCmdArguments> parsed_cmd_arguments)
    :
    parsed_cmd_arguments_ { parsed_cmd_arguments },
    parameter_validator_ { std::make_shared<tension_cpu::cmd_arguments_parser::ParameterValidator>() } {
}

tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::CmdArgumentsParserLogic(
    std::shared_ptr<tension_cpu::cmd_arguments_parser::IParsedCmdArguments> parsed_cmd_arguments,
    std::shared_ptr<tension_cpu::cmd_arguments_parser::IParameterValidator> parameter_validator)
    :
    parsed_cmd_arguments_ { parsed_cmd_arguments },
    parameter_validator_ { parameter_validator } {
}

void tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::PrintHelpMenu() {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s:%d", "[CmdArgumentsParserLogic::PrintHelpMenu]", __FILENAME__, __LINE__);
#endif
      std::cout << kHelpMenuPrint << std::endl;
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s:%d", "[CmdArgumentsParserLogic] Help menu printed", __FILENAME__, __LINE__);
#endif
}

void tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::PrintVersion() {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s:%d", "[CmdArgumentsParserLogic::PrintVersion]", __FILENAME__, __LINE__);
#endif
      std::cout << kVersionPrint << std::endl;
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s:%d", "[CmdArgumentsParserLogic] Version printed", __FILENAME__, __LINE__);
#endif
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessLoadParameter(int load_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic::ProcessLoadParameter]", __FILE__, __LINE__);
#endif
  if(!parameter_validator_->ValidateLoadValue(load_parameter)) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Load parameter has invalid value", __FILE__, __LINE__);
#endif
  return false;
  }
  parsed_cmd_arguments_->SetLoad(load_parameter);
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Load parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessTestTimeParameter(int test_time_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic::ProcessTestTimeParameter]", __FILE__, __LINE__);
#endif
  if(!parameter_validator_->ValidateTestTimeValue(test_time_parameter)) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Test time has invalid value", __FILE__, __LINE__);
#endif
    return false;
  }
  parsed_cmd_arguments_->SetTestTime(std::chrono::seconds(test_time_parameter));
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Load parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessSchedulingPolicy(const char* scheduling_policy_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic::ProcessSchedulingPolicy]", __FILE__, __LINE__);
#endif
  if(!parameter_validator_->ValidateSchedulingPolicyValue(scheduling_policy_parameter)) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Scheduling policy has invalid value", __FILE__, __LINE__);
#endif
    return false;
  }
  parsed_cmd_arguments_->SetScheduligMode(scheduling_policy_parameter);
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Scheduling policy parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessdDebugLevelParameter(int debug_level_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic::ProcessdDebugLevelParameter]", __FILE__, __LINE__);
#endif
  if(!parameter_validator_->ValidateDebugLevelParameterValue(debug_level_parameter)) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Debug level has invalid value", __FILE__, __LINE__);
#endif
    return false;
  }
  parsed_cmd_arguments_->SetDebugMode(debug_level_parameter);
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Debug level parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessdCoresNumberParameter(int cores_number_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic::ProcessdCoresNumberParameter]", __FILE__, __LINE__);
#endif
  if(!parameter_validator_->ValidateCoresNumberParameterValue(cores_number_parameter)) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Cores number has invalid value", __FILE__, __LINE__);
#endif
    return false;
  }
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s:%d", "[CmdArgumentsParserLogic] Cores number parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}
