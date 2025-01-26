#include "vex.h"
int matchloadangle = 0;
int m = 1;

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 1800);
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

int LiftArm() {
  Arm.spinFor(reverse, 0.2, turns);
  return 0;
}

int moveArmFullyDown() {
  chassis.arm_to_angle(10);
  return 0;
}

int moveArmFullyUp() {
  chassis.arm_to_angle(110);
  return 0;
}

int pickUpMogo() {
  wait(1.5, seconds);
  MogoPneu.set(true);
  wait(0.5, seconds);
  Intake.spin(forward);
  Conveyer.spin(forward);
  wait(3, seconds);
  return 0;
}

int lowerArm() {
  Arm.spinTo(0, degrees);
  wait(5, seconds);
  return 0;
}

void Auton43Points(){
  Conveyer.setVelocity(100, percent);
  Intake.setVelocity(100, percent);
  Conveyer.spin(forward);
  wait(0.4, seconds);
  chassis.drive_distance(11.5);
  chassis.turn_to_angle(270);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(-15);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.drive_distance(-8);
  Intake.spin(forward);
  Conveyer.spin(forward);
  MogoPneu.set(true);
  wait(0.3, seconds);
  chassis.turn_to_angle(0);
  default_constants();
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  thread(loadArm).detach();
  chassis.drive_distance(25);
  wait(0.3, seconds);
  chassis.turn_to_angle(38);
  chassis.drive_distance(30.5);
  chassis.turn_to_angle(90);
  Intake.setVelocity(100, percent);
  Conveyer.setVelocity(100, percent);
  Intake.spin(forward);
  Conveyer.spin(forward);
  chassis.drive_distance(16, 90);
  wait(0.3, seconds);
  Arm.spinTo(730, degrees);
  wait(1, seconds);
  chassis.drive_distance(-11, 88);
  thread(lowerArm).detach();
  chassis.turn_to_angle(178);
  chassis.set_heading(180);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  //chassis.drive_distance(57);
  Intake.spin(forward);
  Conveyer.spin(forward);
  chassis.drive_distance(47.5);
  wait(0.5, seconds);
  chassis.drive_distance(10);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(140);
  default_constants();
  chassis.drive_distance(15);
  wait(0.3, seconds);
  chassis.turn_to_angle(335);
  chassis.drive_distance(-9);
  MogoPneu.set(false);
  Intake.stop();
  Conveyer.stop();
  chassis.drive_distance(5.25);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.set_turn_exit_conditions(0.5, 300, 5000);
  chassis.turn_to_angle(89);
  chassis.set_heading(90);
  chassis.drive_distance(-68, 90);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.drive_distance(-10, 90);
  MogoPneu.set(true);
  Intake.spin(forward);
  Conveyer.spin(forward);
  wait(0.3, seconds);
  chassis.turn_to_angle(0);
  default_constants();
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(24);
  chassis.turn_to_angle(270);
  chassis.drive_distance(25);
  chassis.turn_to_angle(180);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(33);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(225);
  chassis.drive_distance(14.5);
  wait(0.3, seconds);
  chassis.turn_to_angle(25);
  chassis.drive_distance(-8.5);
  MogoPneu.set(false);
  Intake.stop();
  Conveyer.stop();
  chassis.drive_distance(30);
  vex::task t3(loadIntake);
  chassis.turn_to_angle(0);
  chassis.drive_distance(48);
  chassis.turn_to_angle(45);
  chassis.drive_distance(36);
  chassis.turn_to_angle(270);
  // DoinkerPneu.set(true);
  // wait(0.3, seconds);
  // chassis.turn_to_angle(135);
  // chassis.turn_to_angle(270);
  chassis.set_drive_constants(6, 1.5, 0, 15, 0);
  t3.stop();
  vex::task t5(pickUpMogo);
  chassis.drive_distance(-51);
  //chassis.drive_distance(-36);
  //MogoPneu.set(true);
  //t3.stop();
  //Intake.spin(forward);
  //chassis.drive_distance(-15);
  default_constants();
  chassis.turn_to_angle(253);
  t5.stop();
  MogoPneu.set(false);
  wait(0.5, seconds);
  chassis.drive_distance(-32);
  chassis.drive_distance(37);
  chassis.turn_to_angle(295);
  chassis.drive_distance(100);
}

void Auton38Points(){
  default_constants();
}

void Auton26Points(){
  //s
}

//The following codes are test codes, avoid editing!
void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}