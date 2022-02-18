/*
 * Logger.cpp
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

#include "../EquinoxLogger/Logger.h"

equinox_logger::Logger *equinox_logger::Logger::logger_instance_ { nullptr };
std::mutex equinox_logger::Logger::logger_instance_mutex_;

void equinox_logger::Logger::SetLoggingLevel(LogLevelType log_level_type) {
  logger_level_->SetLevel(log_level_type);
}

void equinox_logger::Logger::SetLoggingOutput(LogOutputType log_output_type) {
  logger_output_->SetOutput(log_output_type);
}

void equinox_logger::Logger::Error(const char *format, ...) {
  if (equinox_logger::LogLevelType::LOG_LEVEL_ERROR <= logger_level_->GetLevel()) {

    va_list argp;
    std::string log_message_buffer;

    va_start(argp, format);
    vsnprintf((char*) log_message_buffer.c_str(), sizeof(log_message_buffer.c_str()), format, argp);

    switch (logger_output_->GetOutput()) {
      case equinox_logger::LogOutputType::CONSOLE:
        console_logger_->LogMessage(log_message_buffer, equinox_logger::LogLevelType::LOG_LEVEL_ERROR);
        break;
      case equinox_logger::LogOutputType::FILE_LOG:
        /*file_logger_->LogMessage();*/
        break;
      case equinox_logger::LogOutputType::FILE_AND_CONSOLE:
      default:
        console_logger_->LogMessage(log_message_buffer, equinox_logger::LogLevelType::LOG_LEVEL_ERROR);
        /*file_logger_->LogMessage();*/
        break;
    }

    va_end(argp);
  }
}

void equinox_logger::Logger::Warning(const char *format, ...) {
}
void equinox_logger::Logger::Debug(const char *format, ...) {
}

equinox_logger::Logger* equinox_logger::Logger::GetInstance() {
  std::lock_guard<std::mutex> lock(equinox_logger::Logger::logger_instance_mutex_);

  if (equinox_logger::Logger::logger_instance_ == nullptr) {
    equinox_logger::Logger::logger_instance_ = new equinox_logger::Logger();
  }

  return equinox_logger::Logger::logger_instance_;
}
