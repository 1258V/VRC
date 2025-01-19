#include "vex.h"
int d = 180;

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 0);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 0, 5000);
  chassis.set_turn_exit_conditions(1, 0, 600);
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test(){
  //Pre-Auton
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_exit_conditions(1, 0, 600);
  Intake.setVelocity(100, percent);
  Catapult.setVelocity(100, percent);
  Catapult.spin(forward);
  chassis.set_drive_exit_conditions(1.5, 0, 400);
  chassis.drive_distance(-1000);
  chassis.set_drive_exit_conditions(1.5, 0, 600);
  chassis.drive_distance(4);

  Catapult.stop();
  chassis.turn_to_angle(-90+d);
  Intake.spin(forward);
  chassis.set_drive_exit_conditions(1.5, 0, 5000);
  chassis.drive_distance(16.5);
  chassis.drive_distance(-14);

  chassis.turn_to_angle(0+d);
  Intake.setVelocity(30, percent);
  Intake.spin(reverse);
  chassis.drive_distance(27, 0+d, 6, 6);
  Catapult.stop();
  chassis.drive_distance(-3, 0+d, 11, 11);

  Intake.stop();
  Intake.setVelocity(100, percent);
  chassis.set_turn_exit_conditions(1, 0, 1200);
  chassis.turn_to_angle(-90+d);
  chassis.set_turn_exit_conditions(1, 0, 600);
  Catapult.stop();

  /*chassis.set_drive_exit_conditions(1, 0, 800);
  Intake.spin(reverse);
  wait(0.5, seconds);
  chassis.drive_distance(1000);

  chassis.left_swing_to_angle(70);
  Catapult.spin(forward);
  chassis.drive_distance(-6);
  chassis.turn_to_angle(-105);
  Catapult.stop();*/
  Intake.spin(forward);
  chassis.set_drive_exit_conditions(1.5, 0, 1000);
  chassis.drive_distance(17);
  chassis.set_drive_exit_conditions(1.5, 0, 5000);

  chassis.drive_distance(-6);
  chassis.set_turn_exit_conditions(1.5, 0, 800);
  chassis.turn_to_angle(57.5+d);
  chassis.set_turn_exit_conditions(1.5, 0, 600);
  Intake.setVelocity(100, percent);
  Intake.setMaxTorque(100, percent);
  Intake.spin(reverse);
  chassis.drive_distance(2);
  wait(0.5, seconds);
  chassis.drive_distance(-2);
  Intake.stop();

  chassis.turn_to_angle(-28+d);
  Intake.spin(forward);
  chassis.drive_distance(12);
  chassis.right_swing_to_angle(-90+d);
  
  //Intake.stop();
  WingPneu.set(true);
  //Intake.stop();
  chassis.set_drive_exit_conditions(1, 0, 1000);
  chassis.drive_distance(-1000);

  chassis.drive_distance(4);
  chassis.set_turn_exit_conditions(1.5, 0, 1000);
  chassis.turn_to_angle(90+d); 
  Intake.spin(reverse);
  chassis.drive_distance(-5);
  chassis.set_drive_exit_conditions(1, 0, 500);
  chassis.drive_distance(1000);
  chassis.drive_distance(-5);
  chassis.drive_distance(1000);
}

/*void drive_test(){
  int d = matchloadangle;
  Catapult.spin(forward);
  Brain.resetTimer();
  WingPneu.set(true);
  waitUntil(!LimitSwitchC.pressing());
  waitUntil(LimitSwitchC.pressing());
  WingPneu.set(false);
  waitUntil(Brain.Timer.value() > 0.699);
  Catapult.stop();

  for(int i = 0; i<44; i++){
    Catapult.spin(forward);
    Brain.resetTimer();
    waitUntil(!LimitSwitchC.pressing());
    waitUntil(LimitSwitchC.pressing());
    waitUntil(Brain.Timer.value() > 0.699);
    Catapult.stop();
  }
  //}

  //void drive_test(){
  chassis.left_swing_to_angle(-150+d);
  chassis.drive_distance(-12);
  chassis.turn_to_angle(90+d);

  chassis.set_drive_exit_conditions(1.5, 0, 800);
  chassis.drive_distance(100);
  chassis.left_swing_to_angle(45+d);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);

  chassis.drive_distance(-23);
  chassis.turn_to_angle(0+d);
  chassis.drive_distance(-42);
  chassis.left_swing_to_angle(-45+d);
  
  chassis.drive_distance(-17);
  chassis.right_swing_to_angle(-80+d);
  chassis.set_drive_exit_conditions(1.5, 0, 800);
  chassis.drive_distance(-100);

  chassis.set_drive_exit_conditions(1.5, 300, 2100);
  chassis.left_swing_to_angle(10+d);
  chassis.drive_distance(34);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);

  chassis.left_swing_to_angle(-90+d);
  WingPneu.set(true);
  chassis.drive_distance(-18);
  chassis.left_swing_to_angle(0+d);

  chassis.set_drive_exit_conditions(1.5, 0, 1800);
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
