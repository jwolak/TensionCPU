/*
 * Timer.cpp
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

#include "Timer.h"
#include "Logger.h"

int32_t tension_cpu::Timer::next_id_ { 1 };

void tension_cpu::Timer::Start() {
  thread_ = std::thread(&tension_cpu::Timer::threadTimerLoop, this);
  LOG_DEBUG("Timer id: %d started for period %d", id_, period_.count());
  thread_.detach();
}


void tension_cpu::Timer::threadTimerLoop() {
  LOG_DEBUG("%s%d%s", "threadTimerLoop timer with id: ", id_, " started");
  uint32_t counter = 0;
  LOG_DEBUG("%s%d%s", "Timer period set to: ", period_.count(), " [s]");
  while (counter < period_.count() && GetStatus()) {
    fflush(stdout);
    std::cout<<"\r"<<counter<<" [s]";
    std::this_thread::sleep_for(std::chrono::seconds{1});
    ++counter;
  }
  callback_func_();
  std::cout<<std::endl;
  LOG_DEBUG("%s%d%s", "Callback in Timer id: ",id_, " after timeout called");
}
