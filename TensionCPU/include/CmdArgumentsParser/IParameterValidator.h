/*
 * IParameterValidator.h
 *
 *  Created on: 2023
 *      Author: Janusz Wolak
 */

#ifndef INCLUDE_CMDARGUMENTSPARSER_IPARAMETERVALIDATOR_H_
#define INCLUDE_CMDARGUMENTSPARSER_IPARAMETERVALIDATOR_H_

namespace tension_cpu {
namespace cmd_arguments_parser {

class IParameterValidator {
 public:
  virtual ~IParameterValidator() = default;
  virtual bool ValidateLoadValue(int) = 0;
  virtual bool ValidateTestTimeValue(int) = 0;
  virtual bool ValidateSchedulingPolicyValue(const char*) = 0;
  virtual bool ValidateDebugLevelParameterValue(int) = 0;
  virtual bool ValidateCoresNumberParameterValue(int) = 0;
};

} /*namespace cmd_arguments_parser*/
} /*namespace tension_cpu*/

#endif /* INCLUDE_CMDARGUMENTSPARSER_IPARAMETERVALIDATOR_H_ */
