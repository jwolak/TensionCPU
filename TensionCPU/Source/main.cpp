/*
 * main.cpp
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

#include <memory>
#include <csignal>
#include <csetjmp>

#include "Tension-Cpu.h"
#include "Logger.h"

static jmp_buf sigend_jmp_buf;

static void __attribute__ ((noreturn)) sigend_handler(int sig) {
  LOG_DEBUG("%s %d %s", "Signal", sig, "caught");
  longjmp(sigend_jmp_buf, 1);
}

void catch_sigend(void (*handler)(int)) {
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

int main(int argc, const char *argv[]) {

  SET_LOG_LEVEL(equinox_logger::LogLevelType::LOG_LEVEL_DEBUG);

  std::unique_ptr<tension_cpu::ITensionCpu> tension_cpu(new tension_cpu::TensionCpu());

  catch_sigend(sigend_handler);
  if (setjmp(sigend_jmp_buf)) {
    tension_cpu->Stop();
    exit(0);
  }

  if (true == tension_cpu->ParseCmdArguments(argc, argv)) {
    LOG_DEBUG("%s", "Parsed cmd arguments successfully");
    if (false == tension_cpu->Start()) {
      LOG_ERROR("%s", "Start TesnsionCPU failed");
      return EXIT_FAILURE;
    }
  } else {
    LOG_ERROR("%s", "Parse cmd arguments failed");
    return EXIT_FAILURE;
  }

  return 0;
}



