/*
 * main.cpp
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

#include <memory>

#include <csignal>
#include <csetjmp>
#include <cstdio>
#include <cstdlib>
#include <string.h>

#include "CmdArgumentsParser.h"
#include "TensionCPU.h"
#include "EquinoxLogger.h"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
static jmp_buf sigend_jmp_buf;

#ifdef VERBOSE_LOGS
static void __attribute__ ((noreturn)) SigendHandler(int signal) {
  equinox::debug("%s, File: %s, Line: %d", "[main] SigendHandler", __FILENAME__, __LINE__);
  equinox::debug("%s %d %s", "Signal", signal, "caught");
#endif
  longjmp(sigend_jmp_buf, 1);
}

void CatchSigend(void (*handler)(int)) {
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[main] CatchSigend called...", __FILENAME__, __LINE__);
#endif
#ifdef SIGINT
  signal(SIGINT, handler);
#endif
#ifdef SIGTERM
  signal(SIGTERM, handler);
#endif
#ifdef SIGHUP
  signal(SIGHUP, handler);
#endif
}

int main(int argc, char **argv) {
#ifdef VERBOSE_LOGS
  equinox::setup(equinox::level::LOG_LEVEL::trace, "TensionCPU", equinox::logs_output::SINK::console_and_file, "tesnion_cpu_verbose.log");
  printf("%s", "\n\n[!WARNING!] Verbose mode of logs print enabled [!WARNING!]\n\n");
#else
  equinox::setup(equinox::level::LOG_LEVEL::off, "TensionCPU", equinox::logs_output::SINK::console_and_file);
#endif

  std::shared_ptr<tension_cpu::cmd_arguments_parser::IParsedCmdArguments> parsed_cmd_arguments {std::make_shared<tension_cpu::cmd_arguments_parser::ParsedCmdArguments>()};
  tension_cpu::cmd_arguments_parser::CmdArgumentsParser CmdArgumentsParser;
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[main] ParsedCmdArguments and CmdArgumentsParser created...", __FILENAME__, __LINE__);
#endif

  if(!CmdArgumentsParser.ParseCmdArguments(parsed_cmd_arguments, argc, argv)) {
    printf("%s", "Parse arguments failed");
#ifdef VERBOSE_LOGS
    equinox::debug("%s, File: %s, Line: %d", "[main] CmdArgumentsParser::ParseCmdArguments failed", __FILENAME__, __LINE__);
    for (int i = 0; i < argc; ++i) {
      equinox::debug("argv[%d]: %s", i, argv[i]);
    }
#endif
    exit(EXIT_FAILURE);
  }

  tension_cpu::TensionCpu tension_cpu_instance(parsed_cmd_arguments);
#ifdef VERBOSE_LOGS
  equinox::debug("%s, File: %s, Line: %d", "[main] TensionCpu instance created...", __FILENAME__, __LINE__);
#endif

  CatchSigend(SigendHandler);
  if (setjmp(sigend_jmp_buf)) {
#ifdef VERBOSE_LOGS
    equinox::debug("%s, File: %s, Line: %d", "[main] SigendHandler call", __FILENAME__, __LINE__);
#endif
    if(!tension_cpu_instance.stop()) {
      printf("%s", "TensionCPU stop by interrupt failed");
      exit(EXIT_FAILURE);
    }

    printf("%s", "TensionCPU stop by interrupt successful");
    exit(EXIT_SUCCESS);
  }

  if(!tension_cpu_instance.start()) {
    printf("%s", "TensionCPU start failed");
    exit(EXIT_FAILURE);
  }

  return 0;
}
