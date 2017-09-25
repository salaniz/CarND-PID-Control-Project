#include "PID.h"
#include <iostream>

using namespace std;

PID::PID() {
  p_error = i_error = d_error = 0;

  Kp = Ki = Kd = 1;

  is_initialized = false;
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, double first_cte) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  p_error = first_cte;

  is_initialized = true;
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  i_error += cte;
  p_error = cte;
}

double PID::TotalError() {
  double total_error = -Kp * p_error - Ki * i_error - Kd * d_error;

  // Debug output
  //cout << "p_error: " << p_error << " i_error: " << i_error << " d_error: " << d_error << endl;
  //cout << "p_error: " << -Kp * p_error << " i_error: " << -Ki * i_error << " d_error: " << -Kd * d_error << endl;

  if (total_error > 1) {
    total_error = 1;
  } else if (total_error < -1) {
    total_error = -1;
  }

  return total_error;
}

