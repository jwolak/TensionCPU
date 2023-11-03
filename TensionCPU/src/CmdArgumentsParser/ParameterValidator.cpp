/*
 * ParameterValidator.cpp
 *
 *  Created on: 2023
 *      Author: Janusz Wolak
 */

#include "ParameterValidator.h"

tension_cpu::cmd_arguments_parser::ParameterValidator::ParameterValidator() {

}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateLoadValue(int load_value) {

  return true;
}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateSchedulingPolicyValue(const char* scheduling_policy_value) {

  return true;
}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateTestTimeValue(int test_time_value) {

  return true;
}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateCoresNumberParameterValue(int number_of_cores_value) {

  return true;
}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateDebugLevelParameterValue(int debug_level_value) {

  return true;
}
