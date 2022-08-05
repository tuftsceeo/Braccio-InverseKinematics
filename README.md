# Braccio++InverseKinematics
Inverse Kinematics solver for the Arduino Braccio++ robot arm. The library calculates joint angles based on the given end effector position.

![assembly](https://github.com/tuftsceeo/Braccio-InverseKinematics/blob/main/img/assembly.gif)

## Instructions
Download this library as a .zip file and install it using your Arduino IDE by going under Sketch->Add .zip library. Once downloaded, it can be included in any file by including the header file:

```
#include <BraccioIK.h>
```

## Initialization
You can Initialize a solver object in this way:

```
IK_Calculator bracciocalc(motorMin, motorMax, homePos);
```

The constructor requires 3 arguments which are the motorMin, motorMax, and homePos.

```
float motorMin[4] = {0, 84, 55, 38.19};
float motorMax[4] = {360, 225, 256, 251.76};
float homePos[6] = {230.92, 159.63, 147.26, 152.15, 150.81, 180.42};
```
motorMin and motorMax follow the format: **base,shoulder,elbow,wrist**
homePos follows default arduino configuration: **gripper, wrist roll, wrist pitch, elbow, shoulder, base**

These values can be found using the provided ObtainMinMax code(Provided in the same repository) which disengages the arm and prints joint positions to the serial monitor. Move each joint to its min and max and write the values down in an array. The home position is when the arm is facing straight up.

## Function Calls

There are two main function calls:

* Fixed angle of attack
* Random angle of attack

```
bool calculateAngles(float x_e, float y_e, float z_e, bool gripper,float outputAngles[6], float phi);
```

```
bool calculateAngles(float x_e, float y_e, float z_e, bool gripper,float outputAngles[6]);
```

The same function can be overloaded and passed an angle of attack **phi** to solve for that particular wrist angle. If no angle of attack is provided, it will try to solve for the flattest angle of attack.

returns true if angle is in range of motion, false if not.

* x_e is the x coordinate for the end effector
* y_e is the y coordinate for the end effector
* z_e is the z coordinate for the end effector
* gripper is the gripper configuration. False for open, true for closed
* outputAngles is a float array of size 6 to store the output angles

The outputAngles array follows the same format the robot arm uses so it can be passed directly to the arm.
