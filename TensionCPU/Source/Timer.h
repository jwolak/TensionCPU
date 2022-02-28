/*
 * Timer.h
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

#ifndef SOURCE_TIMER_H_
#define SOURCE_TIMER_H_

#include "ITimer.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>

namespace tension_cpu {

class Timer : public ITimer {
 public:
  Timer(std::function<void(void)> callback_f, const std::chrono::seconds period)
      :
      callback_func_ { callback_f },
      period_ { period },
      thread_ { },
      id_ { next_id_++ },
      status_ { true },
      mutex_ { } {
  }

  void Start() override;

  void Stop() override {
    std::lock_guard<std::mutex> lock(mutex_);
    status_ = false;
    thread_.join();
  }

 private:

  void threadTimerLoop() {
    while (GetStatus()) {
      std::this_thread::sleep_for(period_);
      callback_func_();
    }
  }

  bool GetStatus() {
    std::lock_guard<std::mutex> lock(mutex_);
    return status_;
  }

  std::function<void(void)> callback_func_;
  const std::chrono::seconds period_;
  std::thread thread_;
  int32_t id_;
  static int32_t next_id_;
  bool status_;
  std::mutex mutex_;

};

} /*namespace tension_cpu*/

#endif /* SOURCE_TIMER_H_ */
