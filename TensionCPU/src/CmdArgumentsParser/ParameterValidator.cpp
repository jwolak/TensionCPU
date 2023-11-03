/*
 * ParameterValidator.cpp
 *
 *  Created on: 2023
 *      Author: Janusz Wolak
 */

#include "ParameterValidator.h"
#include "EquinoxLogger.h"

#include <cstring>

namespace {
const int kMaxCpuLoad = 100;
}

tension_cpu::cmd_arguments_parser::ParameterValidator::ParameterValidator() {

}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateLoadValue(int load_value) {

  if (load_value < 0) {
#ifdef VERBOSE_LOGS
      equinox::error("%s, \t[%s:%d]", "[ParameterValidator] CPU load parameter less than 0", __FILENAME__, __LINE__);
#endif
    return false;
  }

  if (load_value == 0) {
#ifdef VERBOSE_LOGS
      equinox::error("%s, \t[%s:%d]", "[ParameterValidator] CPU load parameter equal 0", __FILENAME__, __LINE__);
#endif
    return false;
  }

  if (load_value > kMaxCpuLoad) {
#ifdef VERBOSE_LOGS
      equinox::error("%s, \t[%s:%d]", "[ParameterValidator] CPU load parameter grater then 100", __FILENAME__, __LINE__);
#endif
    return false;
  }

#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParameterValidator] CPU load parameter valid", __FILENAME__, __LINE__);
#endif
  return true;
}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateSchedulingPolicyValue(const char *scheduling_policy_value) {

  if (strncmp(scheduling_policy_value, "b", 2) == 0) {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParameterValidator] Valid scheduling policy as BATCH", __FILENAME__, __LINE__);
#endif
    return true;
  }

  if (strncmp(scheduling_policy_value, "f", 2) == 0) {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParameterValidator] Valid scheduling policy as FIFO", __FILENAME__, __LINE__);
#endif
    return true;
  }

  if (strncmp(scheduling_policy_value, "r", 2) == 0) {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParameterValidator] Valid scheduling policy as RR", __FILENAME__, __LINE__);
#endif
    return true;
  }

  if (strncmp(scheduling_policy_value, "o", 2) == 0) {
#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParameterValidator] Valid scheduling policy as OTHER", __FILENAME__, __LINE__);
#endif
    return true;
  }

#ifdef VERBOSE_LOGS
      equinox::error("%s, \t[%s:%d]", "[ParameterValidator] Invalid scheduling policy", __FILENAME__, __LINE__);
#endif
  return false;
}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateTestTimeValue(int test_time_value) {

  if (test_time_value < 0) {
#ifdef VERBOSE_LOGS
      equinox::error("%s, File: %s,:%d", "[ParameterValidator] Test time less than zero", __FILENAME__, __LINE__);
#endif
      return false;
  }

  if (test_time_value == 0) {
#ifdef VERBOSE_LOGS
      equinox::error("%s, \t[%s:%d]", "[ParameterValidator] Test time equal zero", __FILENAME__, __LINE__);
#endif
      return false;
  }

#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParameterValidator] Test time equal is valid", __FILENAME__, __LINE__);
#endif

  return true;
}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateCoresNumberParameterValue(int number_of_cores_value) {

  if (number_of_cores_value < 0) {
#ifdef VERBOSE_LOGS
      equinox::error("%s, \t[%s:%d]", "[ParameterValidator] Number of cores less than zero", __FILENAME__, __LINE__);
#endif
      return false;
  }

  if (number_of_cores_value == 0) {
#ifdef VERBOSE_LOGS
      equinox::error("%s, \t[%s:%d]", "[ParameterValidator] Number of cores equal zero", __FILENAME__, __LINE__);
#endif
      return false;
  }

#ifdef VERBOSE_LOGS
      equinox::trace("%s, \t[%s:%d]", "[ParameterValidator] Number of cores is valid", __FILENAME__, __LINE__);
#endif

  return true;
}

bool tension_cpu::cmd_arguments_parser::ParameterValidator::ValidateDebugLevelParameterValue(int debug_level_value) {

  switch (debug_level_value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
#ifdef VERBOSE_LOGS
      equinox::trace("%s, File: %s: %d", "[ParameterValidator] Debug level is valid", __FILENAME__, __LINE__);
#endif
      return true;
  }

#ifdef VERBOSE_LOGS
      equinox::error("%s, File: %s: %d", "[ParameterValidator] Invalid debug level", __FILENAME__, __LINE__);
#endif
  return false;
}
