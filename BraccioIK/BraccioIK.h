#ifndef BRACCIOIK_H
#define BRACCIOIK_H

#include <Arduino.h>
#include <math.h>

class IK_Calculator {
 public:
  IK_Calculator(float minArray[4], float maxArray[4], float homeArray[6]);
  bool calculateAngles(float x_e, float y_e, float z_e, bool gripper,
                       float outputAngles[6], float phi);
  bool calculateAngles(float x_e, float y_e, float z_e, bool gripper,
                       float outputAngles[6]);

 private:
  const float l_0 = 0.067;
  const float l_1 = 0.123;
  const float l_2 = 0.123;
  const float l_3 = 0.140;
  const float pi = 3.14159265358979323846264338327;

  float motorMin[4];
  float motorMax[4];
  float home[6];
  float internalAngles[4];
  float motorAngles[4];

  float dtr(float degval);
  float rtd(float radval);

  void calcMotor();
  float calcHome(int motorIndex);
  bool inRange(int i);
};

#endif
