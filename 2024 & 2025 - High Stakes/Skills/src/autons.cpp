#include "vex.h"
int matchloadangle = 0;
int m = 1;

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 1200); // previously 1800, might be source of issues
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
  wait(3, seconds);
  return 0;
}

int lowerArm() {
  chassis.arm_to_angle(40);
  wait(5, seconds);
  return 0;
}

void spinIntake() {
  Conveyer.setVelocity(90, percent);
  Intake.setVelocity(100, percent);
  Conveyer.spin(forward);
  Intake.spin(forward);
}

void stopIntake() {
  Conveyer.stop();
  Intake.stop();
}

void loadArm() {
  chassis.arm_to_angle(22);
  Conveyer.setVelocity(90, percent);
  Intake.setVelocity(100, percent);
  Conveyer.spin(forward);
  Intake.spin(forward);
}

int loadArmTask() {
  loadArm();
  wait(3, seconds);
  return 0;
}

void allowDisksThrough() {
  Arm.setVelocity(30, percent);
  chassis.arm_to_angle(50);
  Arm.setVelocity(100, percent);
}

int grabFirstMogo() {
  wait(0.75, seconds);
  MogoPneu.set(true);
  wait(3, seconds);
  return 0;
}

int grabSecondMogo() {
  wait(2.75, seconds);
  MogoPneu.set(true);
  wait(3, seconds);
  return 0;
}

int grabThirdMogo() {
  wait(2.25, seconds);
  MogoPneu.set(true);
  wait(3, seconds);
  return 0;
}

int loadForWallStake() {
  loadArm();
  wait(3, seconds);
  stopIntake();
  allowDisksThrough();
  return 0;
}

int bringArmDown() {
  Arm.spin(reverse);
  wait(1.5, seconds);
  Arm.stop();
  return 0;
}

int placeWallStakeDisk() {
  chassis.arm_to_angle(125);
  wait(1, seconds);
  return 0;
}

int expelDisc() {
  bool blue = false;
  while (true) {
    if (Opt.hue() > 100) {
      blue = true;
    }
    if (DistSensor.objectDistance(inches) < 2 && blue) {
      wait(0.05, seconds);
      Conveyer.stop();
      blue = false;
      wait(0.05, seconds);
      spinIntake();
    }
  }
  return 0;
}

void auton() {
  default_constants();
  spinIntake();
  wait(0.5, seconds);
  chassis.drive_distance(15);
  chassis.turn_to_angle(270);
  vex::task gfm(grabFirstMogo);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(-24);
  chassis.turn_to_angle(0);
  loadArm();
  vex::task loadForStake1(loadForWallStake);
  chassis.drive_distance(20);
  chassis.turn_to_angle(30);
  chassis.drive_distance(33);
  chassis.turn_to_angle(90);
  spinIntake();
  chassis.drive_distance(18);
  vex::task scoreFirstWallStake(placeWallStakeDisk);
  chassis.drive_distance(-14);
  chassis.turn_to_angle(178);
  chassis.set_heading(180);
  loadForStake1.stop();
  scoreFirstWallStake.stop();
  vex::task resetArm(bringArmDown);
  chassis.drive_distance(61);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(140);
  chassis.drive_distance(15);
  wait(0.5, seconds);
  chassis.turn_to_angle(340);
  chassis.drive_distance(-11);
  MogoPneu.set(false);
  chassis.drive_distance(7);
  chassis.turn_to_angle(90);
  vex::task gsm(grabSecondMogo);
  chassis.drive_distance(-82, 90);
  chassis.turn_to_angle(0);
  chassis.drive_distance(25);
  chassis.turn_to_angle(270);
  chassis.drive_distance(23);
  wait(0.3, seconds);
  chassis.turn_to_angle(180);
  chassis.drive_distance(33);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(220);
  chassis.drive_distance(12);
  wait(0.5, seconds);
  chassis.turn_to_angle(15);
  chassis.drive_distance(-13);
  MogoPneu.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(11);
  chassis.turn_to_angle(0);
  resetArm.stop();
  gsm.stop();
  loadArm();
  vex::task loadForStake2(loadForWallStake);
  chassis.drive_distance(40);
  chassis.turn_to_angle(270);
  chassis.drive_distance(4);
  placeWallStakeDisk();
  chassis.drive_distance(-13);
  loadForStake2.stop();
  vex::task resetArm2(bringArmDown);
  chassis.turn_to_angle(45);
  Intake.spin(forward);
  chassis.drive_distance(35);
  chassis.turn_to_angle(220);
  vex::task gtm(grabThirdMogo);
  chassis.drive_distance(-40);
  wait(0.3, seconds);
  chassis.turn_to_angle(230);
  spinIntake();
  chassis.drive_distance(-60);
  MogoPneu.set(false);
}

void Auton43Points(){
  default_constants();
  chassis.set_heading(180);
  chassis.arm_to_angle(60);
  chassis.drive_distance(6.5);
  chassis.arm_to_angle(25);
  Arm.stop();
  chassis.drive_distance(-11.5);
  chassis.turn_to_angle(270);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(-15);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.drive_distance(-8);
  Intake.spin(forward);
  MogoPneu.set(true);
  wait(0.3, seconds);
  chassis.turn_to_angle(0);
  default_constants();
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  //vex::task t(loadArm);
  chassis.drive_distance(25);
  wait(0.3, seconds);
  chassis.turn_to_angle(38);
  chassis.drive_distance(30.5);
  chassis.turn_to_angle(90);
  vex::task t4(moveArmFullyUp);
  //t.stop();
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
  chassis.turn_to_angle(90);
  chassis.drive_distance(16, 90);
  wait(0.3, seconds);
  vex::task moveArmDown(lowerArm);
  wait(1, seconds);
  moveArmDown.stop();
  t4.stop();
  chassis.drive_distance(-11, 88);
  vex::task t2(moveArmFullyDown);
  chassis.turn_to_angle(178);
  chassis.set_heading(180);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  //chassis.drive_distance(57);
  Intake.spin(forward);
  chassis.drive_distance(47.5);
  t2.stop();
  wait(0.5, seconds);
  chassis.drive_distance(10);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(140);
  Intake.spin(forward);
  default_constants();
  chassis.drive_distance(15);
  wait(0.3, seconds);
  chassis.turn_to_angle(335);
  chassis.drive_distance(-9);
  MogoPneu.set(false);
  Intake.stop();
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