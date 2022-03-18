/*
 * Cmd-Args-Parser.cpp
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

#include "Cmd-Args-Parser.h"

#include <getopt.h>
#include <cstring>

#include <iostream>

#include "Logger.h"

namespace tension_cpu {

const char kQuickHelpMenuPrint[] = "Usage: tensionCpu -l [CPU load in %] -T [total time in sec] [options]\n"
                              "Try `tensionCpu --help' for more information.\n";

const char kFHelpMenuPrint[] = "Usage: tensionCpu -l [--load] [CPU load in %] -T [--Time] [total time in sec] -S [--Sched] [scheduling mode]\n"
                           "       tensionCpu [-h|--help] [-v|--version]\n\n"
                           "  -l, --load                CPU load value in percentages\n"
                           "  -T, --Time                total load time ['-T 0' -> sets unlimited time] \n"
                           "Scheduling mode: [-S, --Sched] :\n"
                           "  b, --batch               set SCHED_BATCH scheduler\n"
                           "  f, --fifo                set SCHED_FIFO scheduler (real time)\n"
                           "  r, --roundr              set SCHED_RR scheduler (real time)\n"
                           "  o, --default             set SCHED_OTHER (default) scheduler\n\n"
                           "Example:  tensionCpu -l 90 -T 60 [90% CPU load for 60 seconds time]\n"
                           "Example:  tensionCpu --load 90 --Time 60 --Sched r\n";

} /*namespace tension_cpu*/

bool tension_cpu::CmdArgsParser::ProcessArguments(int argc, char **argv) {

  int flag;
  int32_t cpu_load;
  int32_t cpu_load_total_time;
  SchedulingPolicyType sched_mode;

  static struct option longopts[] = {
      {"help", no_argument, NULL, 'h' },
      {"load", required_argument, NULL, 'l' },
      {"Time", required_argument, NULL, 'T' },
      {"Sched", required_argument, NULL, 'S'},
  };

  LOG_DEBUG("%s, File: %s, Line: %d", "CmdArgsParser::ProcessArguments", __FILE__, __LINE__);
  LOG_DEBUG("argc: %d", argc);

  for (int i = 0; i < argc; ++i) {
    LOG_DEBUG("argv[%d]: %s", i, argv[i]);
  }

  while ((flag = getopt_long(argc, argv, "hl:T:S:", longopts, NULL)) != -1) {
    switch (flag) {
    case 'h':
      std::cout << kFHelpMenuPrint << std::endl;
      LOG_DEBUG("%s", "Help printed");
      break;

    case 'l':
      LOG_DEBUG("%s%s", "Load value:", optarg);
      cpu_load = atoi(optarg);
      LOG_DEBUG("%s %d[%]", "Load CPU set to: ", cpu_load);
      break;

    case 'T':
      LOG_DEBUG("%s%s", "Time value:", optarg);
      cpu_load_total_time = atoi(optarg);
      LOG_DEBUG("%s %d [s]", "CPU load total time set to: ", cpu_load_total_time );
      break;

    case 'S':
        LOG_DEBUG("%s%s", "Scheduling mode:", optarg);

        if( strncmp(optarg, " b", 2) == 0) {
          cmd_arguments_->scheduling_policy = SchedulingPolicyType::BATCH;
          LOG_DEBUG("%s", "Scheduling mode set to: BTACH");
        }

        if (strncmp(optarg, " f", 2)  == 0) {
          cmd_arguments_->scheduling_policy = SchedulingPolicyType::FIFO;
          LOG_DEBUG("%s", "Scheduling mode set to: FIFO");
        }

        if (strncmp(optarg, " r", 2)  == 0) {
          cmd_arguments_->scheduling_policy = SchedulingPolicyType::RR;
          LOG_DEBUG("%s", "Scheduling mode set to: RR");
        }

        if (strncmp(optarg, " o", 2)  == 0) {
          cmd_arguments_->scheduling_policy = SchedulingPolicyType::OTHER;
          LOG_DEBUG("%s", "Scheduling mode set to: OTHER");
        }
      break;

    default:
      std::cout << kQuickHelpMenuPrint << std::endl;
      LOG_ERROR("%s", "Invalid parameter(s) provided");
      return false;
    }
  }

  LOG_DEBUG("%s", "Parameters parsed successfully");
  return true;
}


void tension_cpu::CmdArgsParser::PrintHelpMenu() {
  std::cout << kFHelpMenuPrint << std::endl;
  LOG_DEBUG("%s", "kFHelpMenuPrint() called");
}
