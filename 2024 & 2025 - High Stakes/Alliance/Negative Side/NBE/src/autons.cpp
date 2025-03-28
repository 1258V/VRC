#include "vex.h"
int matchloadangle = 167;

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .3, .03, 2, 15); 
  //previous values for TURN CONSTANTS (not swing) were 2.5 instead of 0.3 and 3 instead of the 2
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  chassis.set_turn_exit_conditions(1, 300, 1800);
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}
void hs(){
  chassis.set_drive_exit_conditions(1.5, 300, 200);
  chassis.drive_distance(1.3);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
}

void wallstake(){
  chassis.drive_distance(38);
  chassis.set_swing_exit_conditions(1, 300, 500);
  chassis.right_swing_to_angle(-39);
  chassis.set_swing_exit_conditions(1, 300, 1000);
  //thread(hs).detach();
  Arm.spinTo(590, degrees); //585
  //thread(hs).detach();
  wait(0.4, seconds);
  Arm.spinTo(-100, degrees);
  chassis.right_swing_to_angle(36);
  Intake.spin(forward);
  Conveyer.spin(forward);
  chassis.drive_distance(11);
  wait(0.2, seconds);
  Conveyer.stop();
  chassis.drive_distance(-10);
  chassis.left_swing_to_angle(60);
  chassis.drive_distance(13);
  
}
void BarTouch(){
  Arm.setVelocity(50, percent);
  Arm.spinTo(630, degrees);
}
void ArmDown(){
  wait(0.3, seconds);
  MogoPneu.set(true);
}
void rushmid(){
  //wait(2, seconds);
  int d = matchloadangle;
  chassis.drive_distance(42, -167+d);
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  Intake.spin(forward);
  //IntakeBack.spin(forward);
  //wait(0.1, seconds);
  //IntakeFront.stop();
  chassis.drive_distance(8, -167+d);
  //IntakeBack.spin(forward);
  //wait(0.4, seconds);
  //IntakeBack.stop();
  //Below is when doinker is added
  //chassis.left_swing_to_angle(-160+d);
  //DoinkerPneu.set(true);
  //chassis.drive_distance(3);
  //DoinkerPneu.set(false);
  //this is for weird pickup
  //chassis.drive_distance(-6, -160+d); //-10
  //chassis.set_turn_constants(12, 1, .03, 3, 15);
  //chassis.right_swing_to_angle(-97+d);
  //chassis.set_drive_constants(11, 0.6, 0, 10, 0);
  //chassis.drive_distance(-6, -103+d);
  //this is normal pickup on far side
  //chassis.drive_distance(-8, -160+d); //-10
  chassis.set_turn_constants(12, 2, .03, 0.5, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 400); //800
  chassis.drive_distance(-12, -167+d);
  Intake.stop();
  chassis.set_swing_exit_conditions(1, 300, 700);
  chassis.left_swing_to_angle(-118+d);
  Conveyer.spin(forward);
  wait(0.3, seconds);
  Conveyer.stop();
  Intake.spin(forward);
  chassis.set_swing_exit_conditions(1, 300, 1000);
  //thi sis for pickup on closer side to middle
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  chassis.drive_distance(9.2);
  //IntakeFront.stop();
  //chassis.left_swing_to_angle(-127+d); //-135
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  chassis.drive_distance(-17.0); //19
  chassis.set_drive_constants(5, 1.2, 0, 10, 0);
  //chassis.right_swing_to_angle(-110+d);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-13);
  thread(ArmDown).detach();
  wait(0.3, seconds);
  chassis.set_swing_exit_conditions(1, 100, 500);
  chassis.left_swing_to_angle(-86+d); //-70+d
  chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  Conveyer.spin(forward);
  //IntakeFront.spin(forward);
  chassis.drive_distance(18.5, -86+d); // 14,-90+d
  //wait(0.5, seconds);
  chassis.set_turn_exit_conditions(1, 100, 400);
  chassis.set_swing_exit_conditions(1, 100, 500);
  //below is for going to corner
  // chassis.left_swing_to_angle(-23+d);
  // chassis.set_drive_constants(11, 3.5, 0, 10, 0);
  // chassis.set_drive_exit_conditions(1.5, 300, 1050);
  // chassis.drive_distance(38);
  // Intake.stop();
  // chassis.set_drive_exit_conditions(1.5, 300, 600);
  // chassis.drive_distance(30);
  // wait(0.2, seconds);
  // chassis.set_drive_constants(11, 2, 0, 10, 0);
  // Intake.spin(forward);
  // chassis.drive_distance(-10);
  // DoinkerPneu.set(true);
  // wait(0.2, seconds);
  // chassis.drive_distance(6.5);
  // Intake.stop();
  // chassis.turn_to_angle(30+d);
  // DoinkerPneu.set(false);
  // chassis.turn_to_angle(-18+d);
  // wait(0.1, seconds);
  // Intake.spin(forward);
  // chassis.drive_distance(15, -20+d);
  chassis.right_swing_to_angle(13+d);
  chassis.drive_distance(13);
  //wait(0.1, seconds);
  chassis.right_swing_to_angle(-49+d);
  chassis.set_drive_constants(11, 12, 0, 10, 0);
  chassis.drive_distance(35, -42+d);
  Intake.stop();
  wait(2, seconds);
  Conveyer.stop();
  wait(10, seconds);
  //chassis.drive_distance(-10);
  // DoinkerPneu.set(true);
  // chassis.set_turn_exit_conditions(1, 100, 800);
  // wait(0.1, seconds);
  // chassis.turn_to_angle(45+d);
  // wait(0.1, seconds);
  // DoinkerPneu.set(false);
  // wait(0.1, seconds);
  // chassis.turn_to_angle(-45+d);
  // chassis.set_drive_constants(11, 1, 0, 10, 0);
  // chassis.set_drive_exit_conditions(1.5, 300, 10000);
  // chassis.drive_distance(-55, -45+d);
  // thread(BarTouch).detach();
  // wait(0.4, seconds);
  // chassis.set_drive_exit_conditions(1.5, 300, 600);
  // chassis.drive_distance(-15);
  // chassis.set_drive_exit_conditions(1.5, 300, 1000);
  // chassis.drive_distance(100);

}


//The following codes are test codes, avoid editing!
