/*
 * ParameterValidator.h
 *
 *  Created on: 2023
 *      Author: Janusz Wolak
 */

#ifndef INCLUDE_CMDARGUMENTSPARSER_PARAMETERVALIDATOR_H_
#define INCLUDE_CMDARGUMENTSPARSER_PARAMETERVALIDATOR_H_

#include "IParameterValidator.h"

namespace tension_cpu {
namespace cmd_arguments_parser {

class ParameterValidator : public IParameterValidator {
 public:
  ParameterValidator();
  bool ValidateLoadValue(int) override;
  bool ValidateTestTimeValue(int) override;
  bool ValidateSchedulingPolicyValue(const char*) override;
  bool ValidateDebugLevelParameterValue(int) override;
  bool ValidateCoresNumberParameterValue(int) override;
};

} /*namespace cmd_arguments_parser*/
} /*namespace tension_cpu*/



#endif /* INCLUDE_CMDARGUMENTSPARSER_PARAMETERVALIDATOR_H_ */
