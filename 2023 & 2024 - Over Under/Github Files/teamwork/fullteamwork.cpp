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
motor Intake = motor(PORT11, ratio6_1, true);

digital_out WingPneu = digital_out(Brain.ThreeWirePort.D);
digital_out IntakePneu = digital_out(Brain.ThreeWirePort.E);
limit LimitSwitch = limit(Brain.ThreeWirePort.C);
motor Catapult = motor(PORT9, ratio36_1, false);

motor leftMotorC = motor(PORT14, ratio6_1, false);

motor rightMotorC = motor(PORT18, ratio6_1, true);

motor leftMotorA = motor(PORT1, ratio6_1, true);
motor leftMotorB = motor(PORT12, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT8, ratio6_1, false);
motor rightMotorB = motor(PORT20, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
inertial DrivetrainInertial = inertial(PORT13);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 0.6666666666666666);

controller Controller1 = controller(primary);

void calibrateDrivetrain() {
  wait(200, msec);
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("Inertial");
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }

  // Clears the screen and returns the cursor to row 1, column 1.
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}

// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // stop the motors if the brain is calibrating
      if (DrivetrainInertial.isCalibrating()) {
        LeftDriveSmart.stop();
        RightDriveSmart.stop();
        while (DrivetrainInertial.isCalibrating()) {
          wait(25, msec);
        }
      }
      
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis3.position();
      int drivetrainRightSideSpeed = Controller1.Axis2.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);

#pragma endregion VEXcode Generated Robot Configuration

// ----------------------------------------------------------------------------
//                                                                            
//    Project: 1258V Alliance Routines                                            
//    Author: Anshul Raghav
//    Created: Nov 8 2023
//    Configuration:        
//                                                                            
// ----------------------------------------------------------------------------

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;
bool isShootingMatchLoads = false;
int isShooting = false; 
int numTimes = 0;
bool intakePneuPosition = false;
bool wingPneuPosition = false;
bool autonIsNotRunning = false;

// User defined function
void myblockfunction_PTime_time_angle_velocity(double myblockfunction_PTime_time_angle_velocity__time, double myblockfunction_PTime_time_angle_velocity__angle, double myblockfunction_PTime_time_angle_velocity__velocity);
// User defined function
void myblockfunction_PTurn_head(double myblockfunction_PTurn_head__head);
// User defined function
void myblockfunction_PStraight_dist_head_velo(double myblockfunction_PStraight_dist_head_velo__dist, double myblockfunction_PStraight_dist_head_velo__head, double myblockfunction_PStraight_dist_head_velo__velo);

int Brain_precision = 0, Console_precision = 0, Controller1_precision = 0;

float proportional, derivative, kd, integral, ki, catapultTimePerShot, targetangle;

bool PidSwitch, MotorEnable;

event message1 = event();
event PidMove = event();
event message2 = event();

// User defined function
void myblockfunction_PTime_time_angle_velocity(double myblockfunction_PTime_time_angle_velocity__time, double myblockfunction_PTime_time_angle_velocity__angle, double myblockfunction_PTime_time_angle_velocity__velocity) {
  Brain.Timer.clear();
  Drivetrain.drive(forward);
  Drivetrain.setDriveVelocity(myblockfunction_PTime_time_angle_velocity__velocity, percent);
  waitUntil((Brain.Timer.time(seconds) > myblockfunction_PTime_time_angle_velocity__time));
  Drivetrain.stop();
}

// User defined function
void myblockfunction_PTurn_head(double myblockfunction_PTurn_head__head) {
  repeat(2) {
    Drivetrain.setDriveVelocity(derivative, percent);
    Drivetrain.turnFor(right, (myblockfunction_PTurn_head__head - Drivetrain.rotation()), degrees, true);
    derivative = derivative + -30.0;
    wait(5, msec);
  }
  derivative = 100.0;
}

// User defined function
void myblockfunction_PStraight_dist_head_velo(double myblockfunction_PStraight_dist_head_velo__dist, double myblockfunction_PStraight_dist_head_velo__head, double myblockfunction_PStraight_dist_head_velo__velo) {
  Drivetrain.setDriveVelocity(myblockfunction_PStraight_dist_head_velo__velo, percent);
  Drivetrain.driveFor(forward, myblockfunction_PStraight_dist_head_velo__dist, inches, false);
  waitUntil((!Drivetrain.isMoving()));
}

// "when started" hat block
int whenStarted1() {
  wait(0.1, seconds);
  waitUntil(MotorEnable);
  while (true) {
  wait(5, msec);
  }
  return 0;
}

// "when started" hat block
int whenStarted2() {
  return 0;
}

// "when Controller1 ButtonR2 pressed" hat block
void onevent_Controller1ButtonR2_pressed_0() {
  Catapult.spin(forward);
  wait(0.4, seconds);
  while (true) {
    if (!LimitSwitch.pressing()) {
      while ((!LimitSwitch.pressing())) {
        wait(0.01, seconds);
      wait(5, msec);
      }
    }
    if (!Controller1.ButtonR2.pressing()) {
      break;
    }
    //      if not limit_switch_c.pressing():      while not limit_switch_c.pressing():             wait(0.01,SECONDS)     if not controller_1.buttonR2.pressing():         Catapult.stop()
  wait(5, msec);
  }
}

// "when Controller1 ButtonL1 pressed" hat block
void onevent_Controller1ButtonL1_pressed_0() {
  Intake.spin(forward);
}

// "when Controller1 ButtonL2 pressed" hat block
void onevent_Controller1ButtonL2_pressed_0() {
  Intake.spin(reverse);
}

// "when Controller1 ButtonL2 pressed" hat block
void onevent_Controller1ButtonL2_pressed_1() {
  Intake.stop();
}

// "when I receive PidMove" hat block
void onevent_PidMove_0() {
}


// Used to find the format string for printing numbers with the
// desired number of decimal places
const char* printToBrain_numberFormat() {
  // look at the current precision setting to find the format string
  switch(Brain_precision){
    case 0:  return "%.0f"; // 0 decimal places (1)
    case 1:  return "%.1f"; // 1 decimal place  (0.1)
    case 2:  return "%.2f"; // 2 decimal places (0.01)
    case 3:  return "%.3f"; // 3 decimal places (0.001)
    default: return "%f"; // use the print system default for everthing else
  }
}

// "when I receive message1" hat block
void onevent_message1_0() {
  wait(0.3, seconds);
  Catapult.spin(forward);
  waitUntil(LimitSwitch.pressing());
  Catapult.stop();
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(printToBrain_numberFormat(), static_cast<float>(Drivetrain.rotation()));
    Brain.Screen.print(printToBrain_numberFormat(), static_cast<float>(derivative));
    wait(0.02, seconds);
  wait(5, msec);
  }
}

// "when I receive message1" hat block
void onevent_message1_1() {
  waitUntil(LimitSwitch.pressing());
  Catapult.stop();
}

// "when I receive message2" hat block
void onevent_message2_0() {
  Catapult.spin(forward);
  waitUntil((!LimitSwitch.pressing()));
  Catapult.stop();
}

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
  Intake.spin(forward);
}
void spinIntakeReverse() {
  Intake.spin(reverse);
}
void stopIntake() {
  Intake.stop();
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

// Begin project code

void preAutonomous(void) {
  
  // Calibrate the Drivetrain
  calibrateDrivetrain();

  // register event handlers
  PidMove(onevent_PidMove_0);
  message1(onevent_message1_0);
  message1(onevent_message1_1);
  message2(onevent_message2_0);

  wait(15, msec);
  // post event registration

  // set default print color to black
  printf("\033[30m");

  // wait for rotation sensor to fully initialize
  wait(30, msec);
  
  Catapult.setStopping(brake);
  Catapult.spinToPosition(90, degrees);
  Catapult.setMaxTorque(100, percent);
  Catapult.setVelocity(80, percent);

  Intake.setStopping(brake);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(85, percent);

  Drivetrain.setStopping(brake);
  leftMotorA.setVelocity(100, percent);
  leftMotorB.setVelocity(100, percent);
  leftMotorC.setVelocity(66.67, percent);
  rightMotorA.setVelocity(100, percent);
  rightMotorB.setVelocity(100, percent);
  rightMotorC.setVelocity(66.67, percent);
  
  Drivetrain.setStopping(coast);
  Intake.setVelocity(100.0, percent);
  MotorEnable = false;
  RemoteControlCodeEnabled = true;
  derivative = 100.0;
  catapultTimePerShot = 0.6;
  ki = 1.0;
  kd = 1.2;
  Drivetrain.setStopping(hold);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Moving");
  Brain.Screen.clearScreen();
  Brain.Screen.print("Pre Auton Code Done");
  wait(1, seconds);

}

void auton(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.print("Autonomous");
  
  message1.broadcast();
  Drivetrain.setRotation(-45.0, degrees);
  IntakePneu.set(true);
  WingPneu.set(false);
  myblockfunction_PStraight_dist_head_velo(17.0, -45.0, 60.0);
  WingPneu.set(true);
  myblockfunction_PStraight_dist_head_velo(-17.0, -45.0, -100.0);
  WingPneu.set(false);
  myblockfunction_PStraight_dist_head_velo(12.0, -45.0, 60.0);
  myblockfunction_PTurn_head(45.0);
  myblockfunction_PStraight_dist_head_velo(50.0, 45.0, 80.0);
  myblockfunction_PTurn_head(-90.0);
  IntakePneu.set(false);
  Intake.spin(reverse);
  myblockfunction_PTime_time_angle_velocity(1.0, -90.0, 100.0);
  myblockfunction_PStraight_dist_head_velo(-8.5, -90.0, 100.0);
  myblockfunction_PTurn_head(-1.0);
  Intake.stop();
  myblockfunction_PTime_time_angle_velocity(1.25, -1.0, -100.0);
  myblockfunction_PStraight_dist_head_velo(5.0, 0.0, 50.0);
  message2.broadcast();
  Drivetrain.turnFor(right, 120 - Drivetrain.rotation(), degrees, false);
  wait(1.0, seconds);
  myblockfunction_PStraight_dist_head_velo(36.0, 90.0, 100.0);
  autonIsNotRunning = true;
}

void userControl(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.print("Driver Control");

    Drivetrain.setStopping(brake);
    
    if (!isShooting) {
      Controller1.ButtonR2.pressed(shootCatapult);
    }

    Controller1.ButtonL1.pressed(spinIntakeForward); 
    Controller1.ButtonL1.released(stopIntake); 

    Controller1.ButtonL2.pressed(spinIntakeReverse);
    Controller1.ButtonL2.released(stopIntake); 

    Controller1.ButtonUp.pressed(toggleIntake);
    Controller1.ButtonLeft.pressed(toggleWings);

    Controller1.ButtonB.pressed(doMatchloads);
    Controller1.ButtonB.released(stopMatchloads);
  

  // place driver control in this while loop
  int driveSpeed = 1;
  while (autonIsNotRunning) {
    LeftDriveSmart.setVelocity(driveSpeed*Controller1.Axis3.position(), percent);
    RightDriveSmart.setVelocity(driveSpeed*Controller1.Axis2.position(), percent);
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);

    wait(5, msec);
  }
}

int main() {
  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods.
    //Comment this section out before competition
    Controller1.ButtonY.pressed(auton);
    Controller1.ButtonX.pressed(userControl);

  Competition.autonomous(auton);
  Competition.drivercontrol(userControl);

  // Run the pre-autonomous function.
  preAutonomous();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
