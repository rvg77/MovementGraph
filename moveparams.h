#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include <alcommon/almodule.h>
#include <math.h>

#include "config.h"

class MoveParams {
 public:
  MoveParams();

  void ToDefault();

  void SetParam(std::string param_name, float param_value);

  AL::ALValue GetParams() const;
 private:
  std::map <std::string, float> param_values_;

};