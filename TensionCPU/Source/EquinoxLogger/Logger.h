/*
 * Logger.h
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

#ifndef SOURCE_EQUINOXLOGGER_LOGGER_H_
#define SOURCE_EQUINOXLOGGER_LOGGER_H_

#include <memory>

#include "../EquinoxLogger/Console-Logger.h"
#include "../EquinoxLogger/File-Logger.h"
#include "../EquinoxLogger/ILogger.h"
#include "../EquinoxLogger/Logger-Level.h"
#include "../EquinoxLogger/Logger-Output.h"

namespace equinox_logger {

class Logger : public ILogger {
 public:
  Logger(std::shared_ptr<ILoggerLevel> logger_level,
         std::shared_ptr<ILoggerOutput> logger_output)
      :
      logger_level_(logger_level),
      logger_output_(logger_output){
  }

  void SetLoggingLevel(LogLevelType) override;
  void SetLoggingOutput(LogOutputType) override;

  void Error(const char*, ...) override;
  void Warning(const char*, ...) override;
  void Debug(const char*, ...) override;

 private:
  std::shared_ptr<ILoggerLevel> logger_level_;
  std::shared_ptr<ILoggerOutput> logger_output_;

/*static std::unique_ptr<Logger> logger_instance_;*/
  std::unique_ptr<IFileLogger> file_logger_;
  std::unique_ptr<IConsoleLogger> console_logger_;

};

} /*namespace equinox_logger*/

#endif /* SOURCE_EQUINOXLOGGER_LOGGER_H_ */
