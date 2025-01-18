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
  Conveyer.spin(forward);
  wait(3, seconds);
  return 0;
}

int lowerArm() {
  chassis.arm_to_angle(40);
  wait(5, seconds);
  return 0;
}

void spinIntake() {
  Conveyer.setVelocity(70, percent);
  Intake.setVelocity(100, percent);
  Conveyer.spin(forward);
  Intake.spin(forward);
}

void stopIntake() {
  Conveyer.stop();
  Intake.stop();
}

void loadArm() {
  Arm.spinTo(156, degrees);
  /*while (true) {
    if (DistSensor.objectDistance(inches) < 1) {
      Intake.setVelocity(50, percent);
      Intake.spinFor(reverse, 12, turns);
      Intake.setVelocity(100, percent);
      break;
    }
    else  {
      Intake.setVelocity(100, percent);
      Intake.spin(forward);
    }

    wait(0.02, seconds);
  }*/
}

void NR(){
  default_constants();
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(-24);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.drive_distance(-8);
  MogoPneu.set(true);
  wait(0.3, seconds);
  default_constants();  
  chassis.turn_to_angle(114);
  spinIntake();
  chassis.drive_distance(20.5);
  wait(0.3, seconds);
  chassis.drive_distance(-15);
  chassis.turn_to_angle(60);
  MogoPneu.set(false);
  stopIntake();
  Intake.spin(forward);
  chassis.drive_distance(15);
  chassis.turn_to_angle(93);
  Intake.stop();
  MogoPneu.set(true);
  chassis.drive_distance(-62);
  chassis.drive_distance(5);
  chassis.turn_to_angle(150);
  chassis.set_drive_exit_conditions(1, 300, 1000);
  chassis.drive_distance(-11);
  spinIntake();
  wait(1.5, seconds);
  chassis.set_drive_constants(8, 0.75, 0, 10, 0);
  Arm.setVelocity(25, percent);
  chassis:Arm.spinToPosition(676, degrees, false);
  chassis.drive_distance(40);
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
  Conveyer.spin(forward);
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
  Conveyer.setVelocity(100, percent);
  Conveyer.spin(forward);
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
  Conveyer.spin(forward);
  chassis.drive_distance(47.5);
  t2.stop();
  wait(0.5, seconds);
  chassis.drive_distance(10);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(140);
  Conveyer.spin(forward);
  default_constants();
  chassis.drive_distance(15);
  wait(0.3, seconds);
  chassis.turn_to_angle(335);
  chassis.drive_distance(-9);
  MogoPneu.set(false);
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
  chassis.set_heading(180);
  chassis.arm_to_angle(60);
  chassis.drive_distance(6.5);
  chassis.arm_to_angle(20);
  Arm.stop();
  chassis.drive_distance(-11.5);
  chassis.turn_to_angle(270);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.drive_distance(-23);
  Conveyer.spin(forward);
  MogoPneu.set(true);
  wait(0.3, seconds);
  chassis.turn_to_angle(0);
  default_constants();
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  //vex::task t(loadArm);
  chassis.drive_distance(25);
  wait(0.3, seconds);
  chassis.turn_to_angle(38);
  chassis.drive_distance(30);
  chassis.turn_to_angle(90);
  chassis.arm_to_angle(110);
  //t.stop();
  Conveyer.setVelocity(100, percent);
  Conveyer.spin(forward);
  chassis.turn_to_angle(90);
  chassis.drive_distance(16, 90);
  wait(0.3, seconds);
  chassis.arm_to_angle(40);
  chassis.drive_distance(-11, 88);
  vex::task t2(moveArmFullyDown);
  chassis.turn_to_angle(178);
  chassis.set_heading(180);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  //chassis.drive_distance(57);
  chassis.drive_distance(47);
  t2.stop();
  wait(0.5, seconds);
  chassis.drive_distance(10);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(140);
  default_constants();
  Conveyer.spin(forward);
  chassis.drive_distance(15.5);
  wait(0.3, seconds);
  chassis.turn_to_angle(335);
  chassis.drive_distance(-9);
  MogoPneu.set(false);
  Conveyer.stop();
  chassis.drive_distance(6);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.set_turn_exit_conditions(0.5, 300, 5000);
  chassis.turn_to_angle(89);
  chassis.set_heading(90);
  chassis.drive_distance(-78, 90);
  MogoPneu.set(true);
  Conveyer.spin(forward);
  wait(0.3, seconds);
  chassis.turn_to_angle(0);
  default_constants();
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(24);
  chassis.turn_to_angle(270);
  chassis.drive_distance(25);
  chassis.turn_to_angle(180);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  chassis.drive_distance(33);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  wait(0.5, seconds);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(220);
  chassis.drive_distance(14);
  wait(0.3, seconds);
  chassis.turn_to_angle(25);
  chassis.drive_distance(-8);
  MogoPneu.set(false);
  Conveyer.stop();
  chassis.drive_distance(30);
  vex::task t3(loadIntake);
  chassis.turn_to_angle(0);
  chassis.drive_distance(48);
  chassis.turn_to_angle(45);
  chassis.drive_distance(36.5);
  chassis.turn_to_angle(270);
  // DoinkerPneu.set(true);
  // wait(0.3, seconds);
  // chassis.turn_to_angle(135);
  // chassis.turn_to_angle(270);
  chassis.set_drive_constants(6, 1.5, 0, 15, 0);
  chassis.drive_distance(-36);
  MogoPneu.set(true);
  t3.stop();
  Conveyer.spin(forward);
  chassis.drive_distance(-15);
  default_constants();
  chassis.turn_to_angle(258);
  MogoPneu.set(false);
  wait(0.5, seconds);
  chassis.drive_distance(-32);
  chassis.drive_distance(37);
  chassis.turn_to_angle(290);
  chassis.drive_distance(50);
}

void Auton26Points(){
  vex::task t(LiftArm);
  chassis.set_drive_constants(4, 1.5, 0, 15, 0);
  chassis.drive_distance(13);  
  chassis.turn_to_angle(-90);
  chassis.drive_distance(-14);
  chassis.set_drive_constants(2, 1.5, 0, 15, 0);
  chassis.drive_distance(-12);
  MogoPneu.set(true);
  wait(0.3, seconds);
  Conveyer.spin(forward);
  wait(0.3, seconds);
  chassis.set_drive_constants(5, 1.5, 0, 15, 0);
  chassis.turn_to_angle(17);
  wait(0.2, seconds);
  chassis.drive_distance(30);
  wait(0.2, seconds);
  chassis.turn_to_angle(90);
  wait(0.2, seconds);
  chassis.drive_distance(28);
  wait(0.2, seconds);
  chassis.turn_to_angle(180);
  wait(0.2, seconds);
  chassis.drive_distance(19);
  //wait(0.5, seconds);
  chassis.drive_distance(13);  
  wait(0.2, seconds);
  chassis.drive_distance(-23);
  wait(0.2, seconds);
  chassis.turn_to_angle(140);
  wait(0.3, seconds);
  chassis.drive_distance(12);  
  wait(0.5, seconds);
  chassis.turn_to_angle(-10);
  wait(0.2, seconds);
  chassis.drive_distance(-15);
  Conveyer.spinFor(reverse, 2, turns, false);
  wait(0.2, seconds);
  Conveyer.stop();
  MogoPneu.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(7.5);
  wait(0.2, seconds);
  chassis.turn_to_angle(-90);
  wait(0.2, seconds);
  chassis.set_drive_constants(4, 1.5, 0, 15, 0);
  chassis.drive_distance(20);
  chassis.drive_distance(20);
  chassis.drive_distance(21);
  chassis.turn_to_angle(90);
  wait(0.2, seconds);
  chassis.set_drive_constants(2, 1.5, 0, 15, 0);
  chassis.drive_distance(-44);
  wait(0.2, seconds);
  MogoPneu.set(true);
  wait(0.3, seconds);
  chassis.set_drive_constants(5, 1.5, 0, 15, 0);
  Conveyer.spin(forward);
  chassis.turn_to_angle(-25);
  wait(0.2, seconds);
  chassis.drive_distance(30);
  wait(0.2, seconds);
  chassis.turn_to_angle(-52);
  wait(0.2, seconds);
  chassis.drive_distance(20);
  chassis.drive_distance(20);
  wait(0.2, seconds);
  chassis.drive_distance(-12);
  wait(0.2, seconds);
  chassis.turn_to_angle(180);
  wait(0.2, seconds);
  chassis.drive_distance(20);
  wait(0.3, seconds);
  chassis.drive_distance(15);
  wait(0.3, seconds);
  chassis.drive_distance(15);
  wait(1, seconds);
  chassis.drive_distance(-15);
  chassis.drive_distance(-10);
  wait(0.2, seconds);
  chassis.turn_to_angle(-145);
  wait(0.2, seconds);
  chassis.drive_distance(20);
  wait(0.5, seconds);
  chassis.drive_distance(-5);
  wait(0.5, seconds);
  chassis.turn_to_angle(-90);
  wait(0.2, seconds);
  chassis.turn_to_angle(30);
  wait(0.2, seconds);
  chassis.drive_distance(-10);
  wait(0.5, seconds);
  Conveyer.spinFor(reverse, 2, turns, false);
  wait(0.2, seconds);
  Conveyer.stop();
  MogoPneu.set(false);
  wait(0.2, seconds);
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