//
// Created by chill on 2024/10/26.
//

#include "PID.h"

PID::PID(float kp, float ki, float kd, float i_max, float out_max){
  kp_ = kp;
  ki_ = ki;
  kd_ = kd;
  i_max_ = i_max;
  out_max_ = out_max;

  output_ = 0.0f;
  ref_ = 0.0f;
  fdb_ = 0.0f;
  err_ = 0.0f;
  err_sum_ = 0.0f;
  last_err_ = 0.0f;
  pout_ = 0.0f;
  iout_ = 0.0f;
  dout_ = 0.0f;
}

float set_limit(float limit, float data){
  if (data >= limit) data = limit;
  else if (data <= -limit) data = -limit;
  return data;
}


float PID::calc(float ref, float fdb) {
  ref_ = ref;
  fdb_ = fdb;

  last_err_ = err_;
  err_ = ref_ - fdb_;
  err_sum_ = set_limit(i_max_, err_sum_ + err_);

  pout_ = kp_ * err_;
  iout_ = ki_ * err_sum_;
  dout_ = kd_ * (err_ - last_err_);

  output_ = set_limit(out_max_, pout_ + iout_ + dout_);
  return  output_;
}