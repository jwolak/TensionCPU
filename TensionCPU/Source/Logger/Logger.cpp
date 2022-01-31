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

#include "Logger.h"


bool tension_cpu::logger::Logger::EnableLogging(LogLevelType log_level_type) {

  return false;
}


bool tension_cpu::logger::Logger::DisableLogging(LogLevelType log_level_type) {

  return false;
}


bool tension_cpu::logger::Logger::SetLoggingLevel(LogLevelType log_level_type) {

  return false;
}


tension_cpu::logger::LogLevelType tension_cpu::logger::Logger::GetLoggingLevel() {

  return LogLevelType::DISABLE_LOG;
}


bool tension_cpu::logger::Logger::SetLoggingOutputType(LogOutputType log_output_type) {

  return false;
}


tension_cpu::logger::LogOutputType tension_cpu::logger::Logger::GetLoggingOutputType() {

  return LogOutputType::NO_LOG;
}


void tension_cpu::logger::Logger::Error(const char* message) {}


void tension_cpu::logger::Logger::Error(std::string& message) {}


void tension_cpu::logger::Logger::Error(std::ostringstream& message) {}


void tension_cpu::logger::Logger::Warning(const char* message) {}


void tension_cpu::logger::Logger::Warning(std::string& message) {}


void tension_cpu::logger::Logger::Warning(std::ostringstream& message) {}


void tension_cpu::logger::Logger::Info(const char* message) {}


void tension_cpu::logger::Logger::Info(std::string& message) {}


void tension_cpu::logger::Logger::Info(std::ostringstream& message) {}


void tension_cpu::logger::Logger::Trace(const char* message) {}


void tension_cpu::logger::Logger::Trace(std::string& message) {}


void tension_cpu::logger::Logger::Trace(std::ostringstream& message) {}


void tension_cpu::logger::Logger::Debug(const char* message) {}


void tension_cpu::logger::Logger::Debug(std::string& message) {}


void tension_cpu::logger::Logger::Debug(std::ostringstream& message) {}
