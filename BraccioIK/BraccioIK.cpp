#include <BraccioIK.h>

IK_Calculator::IK_Calculator(float minArray[4], float maxArray[4],
                             float homeArray[6]) {
  memcpy(motorMin, minArray, sizeof(motorMin));
  memcpy(motorMax, maxArray, sizeof(motorMax));
  memcpy(home, homeArray, sizeof(home));
}

bool IK_Calculator::calculateAngles(float x_e, float y_e, float z_e,
                                    bool gripper, float outputAngles[6],
                                    float phi) {
  float D = sqrt(sq(x_e) + sq(y_e));
  internalAngles[0] = (atan2(x_e, y_e));

  float Q = D;
  float P = z_e - l_0;

  float y = (P - l_3 * sin(dtr(phi)));

  if (z_e >= l_0) {
    y = abs(P - l_3 * sin(dtr(phi)));
  }
  float x = (Q - l_3 * cos(dtr(phi)));

  internalAngles[2] =
      -acos((sq(x) + sq(y) - sq(l_1) - sq(l_2)) / (2 * l_1 * l_2));

  float alpha = atan(y / x);
  float beta = -atan((l_2 * sin(internalAngles[2])) /
                     (l_1 + l_2 * cos(internalAngles[2])));
  internalAngles[1] = (alpha + beta);

  internalAngles[3] = dtr(phi) - internalAngles[1] - internalAngles[2];

  calcMotor();
  outputAngles[0] = home[0];
  if (gripper) {
    outputAngles[0] = 160;
  }
  outputAngles[1] = 160;
  outputAngles[2] = motorAngles[3];
  outputAngles[3] = motorAngles[2];
  outputAngles[4] = motorAngles[1];
  outputAngles[5] = motorAngles[0];
  return (inRange(0) && inRange(1) && inRange(2) && inRange(3));
}

bool IK_Calculator::calculateAngles(float x_e, float y_e, float z_e,
                                    bool gripper, float outputAngles[6]) {
  for (int i = 0; i >= -90; i--) {
    if (calculateAngles(x_e, y_e, z_e, gripper, outputAngles, i)) {
      return true;
    }
  }
  for (int i = 0; i <= 90; i++) {
    if (calculateAngles(x_e, y_e, z_e, gripper, outputAngles, i)) {
      return true;
    }
  }
  return false;
}

void IK_Calculator::calcMotor() {
  motorAngles[0] = home[5] - rtd(internalAngles[0]);
  motorAngles[1] = home[4] + (90 - rtd(internalAngles[1]));
  motorAngles[2] = home[3] - (rtd(internalAngles[2]));
  motorAngles[3] = home[2] - (rtd(internalAngles[3]));
}

float IK_Calculator::dtr(float degval) { return (degval * (pi / 180)); }

float IK_Calculator::rtd(float radval) { return (radval * (180 / pi)); }

float IK_Calculator::calcHome(int motorIndex) {
  return ((motorMax[motorIndex] + motorMin[motorIndex]) / 2);
}

bool IK_Calculator::inRange(int i) {
  return ((motorAngles[i] >= motorMin[i]) && (motorAngles[i] <= motorMax[i]) &&
          (!isnan(motorAngles[i])));
}
