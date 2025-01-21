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
motor Catapult = motor(PORT9, ratio36_1, false);

limit LimitSwitch = limit(Brain.ThreeWirePort.C);
controller Controller1 = controller(primary);
motor IntakeMotor = motor(PORT11, ratio6_1, false);

digital_out IntakePneu = digital_out(Brain.ThreeWirePort.E);
digital_out WingPneu = digital_out(Brain.ThreeWirePort.D);
motor LeftMotorsMotorA = motor(PORT1, ratio6_1, false);
motor LeftMotorsMotorB = motor(PORT12, ratio6_1, false);
motor_group LeftMotors = motor_group(LeftMotorsMotorA, LeftMotorsMotorB);

motor RightMotorsMotorA = motor(PORT8, ratio6_1, false);
motor RightMotorsMotorB = motor(PORT20, ratio6_1, false);
motor_group RightMotors = motor_group(RightMotorsMotorA, RightMotorsMotorB);




// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;
bool isShootingMatchLoads = false;
int isShooting = false; 
int numTimes = 0;
bool intakePneuPosition = false;
bool wingPneuPosition = false;

void shootCatapult() {
  isShooting = false;
  while (LimitSwitch.pressing()) {
    Catapult.spin(forward);
    if (Controller1.ButtonB.pressing()) {
      isShootingMatchLoads = true;
    }
  }
  wait(0.25, seconds);
  while (!LimitSwitch.pressing()) {
    Catapult.spin(forward);
    if (Controller1.ButtonB.pressing()) {
      isShootingMatchLoads = true;
    }
  }
  Catapult.stop();
  isShooting = true;
}

void shootMatchloads() {
  while (LimitSwitch.pressing()) {
    Catapult.spin(forward);
  }
  wait(0.25, seconds);
  while (!LimitSwitch.pressing()) {
    Catapult.spin(forward);
  }
  Catapult.stop();
}

void spinIntakeForward() {
  IntakeMotor.spin(forward);
}
void spinIntakeReverse() {
  IntakeMotor.spin(reverse);
}
void stopIntake() {
  IntakeMotor.stop();
}

void toggleIntake() {
  if (intakePneuPosition) {
    IntakePneu.set(false);
    intakePneuPosition = false;
  }
  else {
    IntakePneu.set(true);
    intakePneuPosition = true;
  }
  
}
void toggleWings() {
  if (wingPneuPosition) {
    WingPneu.set(false);
    wingPneuPosition = false;
  }
  else {
    WingPneu.set(true);
    wingPneuPosition = true;
  }
  
}
void doMatchloads() {
  Catapult.spin(forward);
}
void stopMatchloads() {
  //Catapult.stop();
  shootCatapult();
}

int main() {
  Catapult.setStopping(brake);Catapult.spinToPosition(90, degrees);

  Catapult.setMaxTorque(100, percent);
  Catapult.setVelocity(80, percent);
  IntakeMotor.setStopping(brake);
  IntakeMotor.setMaxTorque(100, percent);
  IntakeMotor.setVelocity(85, percent);
  RightMotors.setStopping(brake);
  LeftMotors.setStopping(brake);
  RightMotors.setVelocity(100, percent);
  LeftMotors.setVelocity(100, percent);
  RightMotors.setMaxTorque(100, percent);
  LeftMotors.setMaxTorque(100, percent);
  
  if (!isShooting) {
    Controller1.ButtonR2.pressed(shootCatapult);
  }

  Controller1.ButtonL1.pressed(spinIntakeForward); 
  Controller1.ButtonL1.released(stopIntake); 
  Controller1.ButtonL2.pressed(spinIntakeReverse); 
  Controller1.ButtonL2.released(stopIntake); 
  IntakePneu.set(true);
  Controller1.ButtonUp.pressed(toggleIntake);
  WingPneu.set(true);
  Controller1.ButtonLeft.pressed(toggleWings);
  Controller1.ButtonB.pressed(doMatchloads);
  Controller1.ButtonB.released(stopMatchloads);
  
  int driveSpeed = 1;
  while (true) {
    LeftMotors.setVelocity(driveSpeed*Controller1.Axis3.position(), percent);
    RightMotors.setVelocity(driveSpeed*Controller1.Axis2.position(), percent);
    LeftMotors.spin(reverse);
    RightMotors.spin(forward);

    wait(5, msec);
  }
}
