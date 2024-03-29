/*
 * TensionCpu.h
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

#ifndef SOURCE_TENSION_CPU_H_
#define SOURCE_TENSION_CPU_H_

#include "ITension-Cpu.h"

#include <memory>

#include "Cmd-Args-Parser.h"
#include "Cpu-Load-Generator.h"
#include "Timer.h"
#include "Logger.h"

namespace tension_cpu {

class TensionCpu : public ITensionCpu {
 public:
  TensionCpu()
      :
      cmd_arguments_ { new CmdArguments },
      cmd_arg_parser_ { new CmdArgsParser { cmd_arguments_ } },
      timer_ { new Timer { std::bind(&tension_cpu::TensionCpu::StopLoadGeneratorAfterTimeout, this), cmd_arguments_->test_time } },
      cpu_load_generator_ { new CpuLoadGenerator { cmd_arguments_, timer_ } }{
  }

  bool ParseCmdArguments(int argc, char **argv) override;
  bool Start() override;
  bool Stop() override;

 private:
  std::shared_ptr<CmdArguments> cmd_arguments_;
  std::unique_ptr<ICmdArgsParser> cmd_arg_parser_;
  std::shared_ptr<ITimer> timer_;
  std::unique_ptr<ICpuLoadGenerator> cpu_load_generator_;

  void StopLoadGeneratorAfterTimeout(void) {
    cpu_load_generator_->Stop();
    LOG_DEBUG("%s", "Load generator stopped after timeout");
  }

};

} /*namespace tension_cpu*/


#endif /* SOURCE_TENSION_CPU_H_ */
