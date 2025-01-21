#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor LeftDriveMotorA = motor(PORT11, ratio18_1, true);
motor LeftDriveMotorB = motor(PORT20, ratio18_1, true);
motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB);

motor RightDriveMotorA = motor(PORT1, ratio18_1, false);
motor RightDriveMotorB = motor(PORT10, ratio18_1, false);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB);

inertial Inertial9 = inertial(PORT9);

motor CatapultMotorA = motor(PORT15, ratio18_1, false);
motor CatapultMotorB = motor(PORT16, ratio18_1, true);
motor_group Catapult = motor_group(CatapultMotorA, CatapultMotorB);

digital_out DigitalOutA = digital_out(Brain.ThreeWirePort.A);



// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration
// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

// User defined function
void myblockfunction_PStraight_dist_head_velo_kp(double myblockfunction_PStraight_dist_head_velo_kp__dist, double myblockfunction_PStraight_dist_head_velo_kp__head, double myblockfunction_PStraight_dist_head_velo_kp__velo, double myblockfunction_PStraight_dist_head_velo_kp__kp);
// User defined function
void myblockfunction_PTurn_head(double myblockfunction_PTurn_head__head);

float proportional, derivative, kd, integral, ki;

// User defined function
void myblockfunction_PStraight_dist_head_velo_kp(double myblockfunction_PStraight_dist_head_velo_kp__dist, double myblockfunction_PStraight_dist_head_velo_kp__head, double myblockfunction_PStraight_dist_head_velo_kp__velo, double myblockfunction_PStraight_dist_head_velo_kp__kp) {
  LeftDrive.setPosition(0.0, degrees);
  RightDrive.setPosition(0.0, degrees);
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  if (myblockfunction_PStraight_dist_head_velo_kp__velo > 0.0) {
    while ((30.0 * myblockfunction_PStraight_dist_head_velo_kp__dist > LeftDrive.position(degrees))) {
      derivative = myblockfunction_PStraight_dist_head_velo_kp__head - Inertial9.rotation(degrees);
      proportional = myblockfunction_PStraight_dist_head_velo_kp__kp * (kd * derivative);
      LeftDrive.setVelocity((myblockfunction_PStraight_dist_head_velo_kp__velo + proportional), percent);
      RightDrive.setVelocity((myblockfunction_PStraight_dist_head_velo_kp__velo - proportional), percent);
    wait(5, msec);
    }
  }
  else {
    while ((LeftDrive.position(degrees) > 30.0 * myblockfunction_PStraight_dist_head_velo_kp__dist)) {
      derivative = myblockfunction_PStraight_dist_head_velo_kp__head - Inertial9.rotation(degrees);
      proportional = myblockfunction_PStraight_dist_head_velo_kp__kp * (kd * derivative);
      LeftDrive.setVelocity((myblockfunction_PStraight_dist_head_velo_kp__velo + proportional), percent);
      RightDrive.setVelocity((myblockfunction_PStraight_dist_head_velo_kp__velo - proportional), percent);
    wait(5, msec);
    }
  }
  LeftDrive.stop();
  RightDrive.stop();
}

// User defined function
void myblockfunction_PTurn_head(double myblockfunction_PTurn_head__head) {
  integral = 90.0;
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  while ((integral > 2.0)) {
    integral = ki * (myblockfunction_PStraight_dist_head_velo_kp__head - Inertial9.rotation(degrees));
    LeftDrive.setVelocity((0.0 + integral), percent);
    RightDrive.setVelocity((0.0 - integral), percent);
  wait(5, msec);
  }
  LeftDrive.stop();
  RightDrive.stop();
}

// "when started" hat block
int whenStarted1() {
  Inertial9.startCalibration();
  while (Inertial9.isCalibrating()) { task::sleep(50); }
  ki = 1.2;
  kd = 1.0;
  myblockfunction_PStraight_dist_head_velo_kp(36.0, 0.0, 60.0, 2.0);
  myblockfunction_PTurn_head(-150.0);
  // Start shooting 44 match load triballs
  Catapult.spin(forward);
  while ((25.0 > Brain.Timer.time(seconds))) {
    integral = ki * (150.0 - Inertial9.rotation(degrees));
    LeftDrive.setVelocity((0.0 + integral), percent);
    RightDrive.setVelocity((0.0 - integral), percent);
  wait(5, msec);
  }
  LeftDrive.stop();
  RightDrive.stop();
  myblockfunction_PTurn_head(-180.0);
  myblockfunction_PStraight_dist_head_velo_kp(-18.0, -180.0, -60.0, 2.0);
  myblockfunction_PTurn_head(-270.0);
  // Open the wings
  DigitalOutA.set(true);
  // Push triballs into goal
  myblockfunction_PStraight_dist_head_velo_kp(-72.0, -270.0, -100.0, 2.0);
  myblockfunction_PStraight_dist_head_velo_kp(9.0, -270.0, 50.0, 2.0);
  myblockfunction_PStraight_dist_head_velo_kp(-9.0, -270.0, -100.0, 2.0);
  return 0;
}


int main() {
  // post event registration

  // set default print color to black
  printf("\033[30m");

  // wait for rotation sensor to fully initialize
  wait(30, msec);

  whenStarted1();
}
