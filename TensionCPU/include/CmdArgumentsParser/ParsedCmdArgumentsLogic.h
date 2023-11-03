/*
 * ParsedCmdArgumentsLogic.h
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

#ifndef INCLUDE_CMDARGUMENTSPARSER_PARSEDCMDARGUMENTSLOGIC_H_
#define INCLUDE_CMDARGUMENTSPARSER_PARSEDCMDARGUMENTSLOGIC_H_

#include <chrono>

#include <cstdint>

#include "SchedulingModeType.h"
#include "DebugModeType.h"

namespace tension_cpu {
namespace cmd_arguments_parser {

//!  ParsedCmdArgumentsLogic class.
/*!
 ParsedCmdArgumentsLogic contains a functionality implementation for ParsedCmdArguments.
 */
class ParsedCmdArgumentsLogic {
 public:
  ParsedCmdArgumentsLogic();

  /**
   * SetScheduligMode() method sets parameters contains scheduling policy like: FIFO, RoundRobin, BATCH or OTHER
   * @param sched_mode_type a scheduling mode to be set (FIFO, RR, BATCH, OTHER).
   */
  void SetScheduligMode(SchedulingModeType sched_mode_type);

  /**
   * GetScheduligMode() method returns scheduling policy.
   * @return SchedulingModeType as scheduling mode parsed from command line.
   */
  SchedulingModeType GetScheduligMode();

  /**
   * SetLoad() method sets CPU load in percentage.
   * @param load CPU load in percentage to be set.
   */
  void SetLoad(int load);

  /**
   * GetLoad() method returns CPU load in percentage.
   * @return CPU load in percentage parsed form command line.
   */
  int GetLoad();

  /**
   * SetTestTime() method sets CPU load time in seconds.
   * @param time CPU load time in in seconds.
   */
  void SetTestTime(std::chrono::seconds time);

  /**
   * GetTestTime() method returns CPU load time in seconds.
   * @return CPU load time in seconds.
   */
  std::chrono::seconds GetTestTime();

  /**
   * SetDebugMode() method to set level of printed logs.
   * @param debug_mode_to_set level of printed logs.
   */
  void SetDebugMode(DebugModeType debug_mode_to_set);

  /**
   * GetDebugMode() method to get level of printed logs.
   * @return level of printed logs.
   */
  DebugModeType GetDebugMode();

  /**
   * scheduling_mode_type contains a scheduling policy.
   */
  SchedulingModeType scheduling_mode_type;

  /**
   * cpu_load contains a CPU in percentage.
   */
  int cpu_load;

  /**
   * test_time contains a CPU load time.
   */
  std::chrono::seconds test_time;

  /**
   * level of printed logs.
   */
  DebugModeType debug_mode;

  //TODO No Cores number!!!
};

} /*namespace cmd_arguments_parser*/
} /*namespace tension_cpu*/

#endif /* INCLUDE_CMDARGUMENTSPARSER_PARSEDCMDARGUMENTSLOGIC_H_ */
