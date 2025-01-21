#include "vex.h"
int matchloadangle = -45;

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
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

void drive_test(){
  //Pre-auton
  int d = matchloadangle;
  Intake.setVelocity(100, percent);
  Intake.stop();
  chassis.set_heading_constants(6, .12, 0, 1, 0);
  Intake.spin(reverse);
  chassis.drive_distance(25, 90+d, 11, 11);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  
  chassis.drive_distance(-4, 90+d, 11, 11);
  chassis.set_drive_exit_conditions(1.5, 0, 600);
  chassis.drive_distance(1000, 90+d, 11, 11);
  chassis.set_drive_exit_conditions(1.5, 0, 5000);

  chassis.drive_distance(-14, 45+d, 11, 11);
  chassis.turn_to_angle(-23.5+d);
  Catapult.spin(forward);
  chassis.drive_distance(6);
  Brain.resetTimer();
  //WingPneu.set(true);
  waitUntil(!LimitSwitchC.pressing());
  waitUntil(LimitSwitchC.pressing());
  //WingPneu.set(false);
  waitUntil(Brain.Timer.value() > 0.699);
  Catapult.stop();


  for(int i = 0; i<48; i++){
    Catapult.spin(forward);
    Brain.resetTimer();
    waitUntil(!LimitSwitchC.pressing());
    waitUntil(LimitSwitchC.pressing());
    waitUntil(Brain.Timer.value() > 0.699);
    Catapult.stop();
  }

  chassis.right_swing_to_angle(30+d);
  chassis.drive_distance(-8);
  chassis.turn_to_angle(0+d);
  chassis.drive_distance(-42);
  chassis.left_swing_to_angle(-45+d);

  //Reduce the timeout for the pushing section
  chassis.set_drive_exit_conditions(1.5, 300, 1800);
  
  chassis.drive_distance(-17);
  chassis.right_swing_to_angle(-80+d);
  chassis.set_drive_exit_conditions(1.5, 0, 800);
  chassis.drive_distance(-100);

  chassis.set_drive_exit_conditions(1.5, 300, 2100);
  chassis.left_swing_to_angle(10+d);
  chassis.drive_distance(28);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);

  chassis.turn_to_angle(-90+d);
  chassis.drive_distance(-18);
  chassis.left_swing_to_angle(0+d);
  WingPneu.set(true);
  
  chassis.set_drive_exit_conditions(1.5, 0, 1000);
  chassis.drive_distance(-100);
  WingPneu.set(false);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);

  chassis.left_swing_to_angle(20);
  chassis.drive_distance(20);
  chassis.left_swing_to_angle(0);
  WingPneu.set(true);

  chassis.set_drive_exit_conditions(1.5, 0, 1000);
  chassis.drive_distance(-100);
}

/*void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}*/

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

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

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}
