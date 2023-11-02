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

void tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::PrintHelpMenu() {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic::PrintHelpMenu]", __FILENAME__, __LINE__);
#endif

#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic] Help menu printed", __FILENAME__, __LINE__);
#endif
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessLoadParameter(int load_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic::ProcessLoadParameter]", __FILE__, __LINE__);
#endif

#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic] Load parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessTestTimeParameter(int test_time_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic::ProcessTestTimeParameter]", __FILE__, __LINE__);
#endif

#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic] Load parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessSchedulingPolicy(const char* scheduling_policy_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic::ProcessSchedulingPolicy]", __FILE__, __LINE__);
#endif

#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic] Scheduling policy parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessdDebugLevelParameter(int debug_level_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic::ProcessdDebugLevelParameter]", __FILE__, __LINE__);
#endif

#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic] Debug level parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic::ProcessdCoresNumberParameter(int cores_number_parameter) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic::ProcessdCoresNumberParameter]", __FILE__, __LINE__);
#endif

#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[CmdArgumentsParserLogic] Cores number parameter processed successfully", __FILE__, __LINE__);
#endif
  return true;
}
