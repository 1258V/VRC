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

void regular(){
  Intake.spin(forward);
  Conveyer.spin(forward);
  chassis.drive_distance(40);
  wait(2, seconds);
  chassis.drive_distance(-10);
  chassis.drive_distance(10);
}
void ArmDown(){
  MogoPneu.set(true);
}

void mirrored(){
  //wait(2, seconds);
  int d = matchloadangle;
  chassis.drive_distance(49, -167+d);
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
  chassis.drive_distance(-10, -167+d);
  Intake.stop();
  chassis.set_swing_exit_conditions(1, 300, 700);
  chassis.left_swing_to_angle(-118+d);
  Conveyer.spin(forward);
  wait(0.35, seconds);
  Conveyer.stop();
  chassis.set_swing_exit_conditions(1, 300, 1000);
  //thi sis for pickup on closer side to middle
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  chassis.drive_distance(9);
  Intake.spin(forward);
  //IntakeFront.stop();
  chassis.left_swing_to_angle(-127+d); //-135
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  chassis.drive_distance(-18.0); //19
  chassis.set_drive_constants(5, 1.2, 0, 10, 0);
  //chassis.right_swing_to_angle(-110+d);
  chassis.set_drive_exit_conditions(1.5, 300, 170);
  chassis.drive_distance(-7);
  thread(ArmDown).detach();
  //wait(0.3, seconds);
  chassis.set_swing_exit_conditions(1, 100, 500);
  chassis.left_swing_to_angle(-70+d); //-90+d
  chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  Conveyer.spin(forward);
  //IntakeFront.spin(forward);
  chassis.drive_distance(11, -70+d); // 14,-90+d
  //wait(0.5, seconds);
  chassis.set_turn_exit_conditions(1, 100, 450);
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
  chassis.right_swing_to_angle(8+d);
  chassis.drive_distance(24);
  //wait(0.1, seconds);
  chassis.right_swing_to_angle(-45+d);
  chassis.set_drive_constants(11, 12, 0, 10, 0);
  chassis.drive_distance(45, -42+d);
  wait(0.4, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 600);
  chassis.drive_distance(-15);
  chassis.set_drive_exit_conditions(1.5, 300, 1000);
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