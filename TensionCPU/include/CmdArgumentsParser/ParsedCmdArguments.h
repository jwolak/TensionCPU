/*
 * ParsedCmdArguments.h
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

#ifndef INCLUDE_PARSEDCMDARGUMENTS_H_
#define INCLUDE_PARSEDCMDARGUMENTS_H_

#include "IParsedCmdArguments.h"
#include "ParsedCmdArgumentsLogic.h"

namespace tension_cpu {
namespace cmd_arguments_parser {

//!  ParsedCmdArguments class.
/*!
 ParsedCmdArguments contains parameters parsed from the command line.
 */
class ParsedCmdArguments : public IParsedCmdArguments {
 public:
  ParsedCmdArguments()
      :
      parsed_cmd_arguments_logic_ { } {
  }

  /**
   * SetScheduligMode() method sets parameters contains scheduling policy like: FIFO, RoundRobin, BATCH or OTHER
   * @param sched_mode_type a scheduling mode to be set (FIFO, RR, BATCH, OTHER).
   */
  void SetScheduligMode(SchedulingModeType sched_mode_type) override;

  /**
   * GetScheduligMode() method returns scheduling policy.
   * @return SchedulingModeType as scheduling mode parsed from command line.
   */
  SchedulingModeType GetScheduligMode() override;

  /**
   * SetLoad() method sets CPU load in percentage.
   * @param CPU load in percentage to be set.
   */
  void SetLoad(int32_t load) override;

  /**
   * GetLoad() method returns CPU load in percentage.
   * @return CPU load in percentage parsed form command line.
   */
  int32_t GetLoad() override;

  /**
   * SetTestTime() method sets CPU load time in seconds.
   * @param CPU load time in in seconds.
   */
  void SetTestTime(std::chrono::seconds time) override;

  /**
   * GetTestTime() method returns CPU load time in seconds.
   * @return CPU load time in seconds.
   */
  std::chrono::seconds GetTestTime() override;

 private:
  /**
   * parsed_cmd_arguments_logic_ contains a functionality implementation for ParsedCmdArguments.
   */
  ParsedCmdArgumentsLogic parsed_cmd_arguments_logic_;
};

} /*namespace cmd_arguments_parser*/
} /*namespace tension_cpu*/

#endif /* INCLUDE_PARSEDCMDARGUMENTS_H_ */
