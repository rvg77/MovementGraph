#include "moveparams.h"

MoveParams::MoveParams() {
  ToDefault();
}

void MoveParams::ToDefault() {
  for (size_t i = 0; i < MOVE_PARAM_NAMES.size(); ++i) {
    param_values_[MOVE_PARAM_NAMES[i]] = MOVE_PARAM_DEFAULT[i];
  }
}

void MoveParams::SetParam(std::string param_name, float param_value) {
  assert(param_values_.find(param_name) != param_values_.end());

  param_values_[param_name] = param_value;
}

AL::ALValue MoveParams::GetParams() const {
  AL::ALValue params;

  for (auto it = param_values_.begin(); it != param_values_.end(); ++it) {
    AL::ALValue param = AL::ALValue::array(it->first, it->second);
    params.arrayPush(param);
  }

  return params;
}
