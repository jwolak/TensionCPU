/*
 * CmdArgumentsParser.cpp
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

#include <cstdint>
#include <iostream>

#include <getopt.h>

#include "CmdArgumentsParser.h"
#include "EquinoxLogger.h"

namespace {
const int32_t kMinNumberOfArguments = 2;
const int kFail = -1;
}

tension_cpu::cmd_arguments_parser::CmdArgumentsParser::CmdArgumentsParser()
    :
    cmd_arguments_parserlogic_ { std::make_shared<tension_cpu::cmd_arguments_parser::CmdArgumentsParserLogic>() } {
}


tension_cpu::cmd_arguments_parser::CmdArgumentsParser::CmdArgumentsParser(std::shared_ptr<ICmdArgumentsParserLogic> cmd_arguments_parserlogic)
    :
    cmd_arguments_parserlogic_ { cmd_arguments_parserlogic } {
}

bool tension_cpu::cmd_arguments_parser::CmdArgumentsParser::ParseCmdArguments(std::shared_ptr<IParsedCmdArguments> parsed_cmd_arguments, int argc, char **argv)
{
  if (argc < kMinNumberOfArguments) {
    std::cout << "No arguments provided" << std::endl;
    cmd_arguments_parserlogic_->PrintHelpMenu();
    return false;
  }

  static struct option longopts[] = {
      {"help", no_argument, NULL, 'h' },
      {"load", required_argument, NULL, 'l' },
      {"Time", required_argument, NULL, 'T' },
      {"Sched", required_argument, NULL, 'S'},
      {"Debug", required_argument, NULL, 'D'},
      {"Cores", required_argument, NULL, 'C'},
  };

  int flag = 0;
  while ((flag = getopt_long(argc, argv, "hl:T:S:D:C:", longopts, NULL)) != kFail) {
    switch (flag) {
      case 'h':
        cmd_arguments_parserlogic_->PrintHelpMenu();
        return false;

      case 'l':
        if (!cmd_arguments_parserlogic_->ProcessLoadParameter(atoi(optarg))) {
          return false;
        }
        break;

      case 'T':
        if (!cmd_arguments_parserlogic_->ProcessTestTimeParameter(atoi(optarg))) {
          return false;
        }
        break;

      case 'S':
        if (!cmd_arguments_parserlogic_->ProcessSchedulingPolicy(optarg)) {
          return false;
        }
        break;

      case 'D':
        if (!cmd_arguments_parserlogic_->ProcessdDebugLevelParameter(atoi(optarg))) {
          return false;
        }
        break;

      case 'C':
        if (!cmd_arguments_parserlogic_->ProcessdCoresNumberParameter(atoi(optarg))) {
          return false;
        }
        break;

      default:
        cmd_arguments_parserlogic_->PrintHelpMenu();
        return false;
    }
  }

  std::cout << "[CmdArgumentsParser] Cmd arguments parsed successfully" << std::endl;
  return true;
}
