#include "vex.h"
int matchloadangle = 45;
int m = 1;

void alter(){
  m = 0 - m;
  if(m < 0){
    controller(primary).Screen.setCursor(0, 0);
    controller(primary).Screen.print("Blue - Mirrored");
  }
  else{
    controller(primary).Screen.setCursor(0, 0);
    controller(primary).Screen.print("Red - Regulated");
  }
}

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(11, .4, .03, 3, 15);
  chassis.set_swing_constants(11, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(0.3, 300, 1200);
  chassis.set_turn_exit_conditions(1, 300, 1800); // originally 1800
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 0;
}

void TouchBar(){
  chassis.turn_to_angle(175);
  chassis.drive_distance(40);
}

void ArmPickup(){
  Intake.spin(forward);
  while (true) {
    if (DistSensor.objectDistance(inches) < 1) {
      MogoPneu.set(false);
      chassis.drive_distance(-4);
      MogoPneu.set(true);
      wait(0.5, seconds);
      TouchBar();
      /*while (true) {
        if (DistSensor.objectDistance(inches) < 1) {
         /* Intake.setVelocity(0, percent);
          Intake.spinFor(reverse, 1, turns);
          Intake.setVelocity(100, percent);
          break;
        }
        else {
          Intake.setVelocity(100, percent);
          Intake.spin(forward);
        }
      wait(0.02, seconds);
      }*/
      break;
    }
    else  {
      Intake.setVelocity(100, percent);
      Intake.spin(forward);
    }

    wait(0.02, seconds);
  }
}

void ArmPick(){
  wait(0.6, seconds);
  FrontIntake.spin(forward);
  Intake.spin(forward);
  while(!(Optical6.hue() < 25 || Optical6.hue() > 15)){
    wait(10, msec);
  }
  Intake.stop();
}

void ArmDown(){
  MogoPneu.set(true);
}
void ArmUp(){
  wait(0.3, seconds);
  Intake.spin(forward);
}

void task1(){
  Arm.spinTo(-100, degrees);
}

void task2(){
  wait(0.5, seconds);
  Intake.spin(forward);
}

void task3(){
  wait(0.8, seconds);
  Intake.stop();
}

void task4(){
  wait(1, seconds);
  Intake.stop();
}

void task5(){
  wait(1.3, seconds);
  Intake.spin(forward);
}

void doinkerRush(){
  wait(0.85, seconds);
  DoinkerPneu.set(true);
}

void doinkerInDelay(){
  wait(0.4, seconds);
  DoinkerPneu.set(false);
}

void getWallStake(){
  Arm.spinTo(-680, degrees);
}

void corner(){
  Intake.spin(forward);
  FrontIntake.spin(forward);
  
  chassis.set_drive_exit_conditions(1.5, 300, 1200);
  chassis.drive_distance(1000, 47);
  chassis.drive_with_voltage(-12, -12);
  wait(0.3, seconds);
  chassis.drive_with_voltage(0, 0);
  wait(0.3, seconds);

  repeat(8){
    chassis.drive_with_voltage(12, 12);
    wait(0.7, seconds);
    chassis.drive_with_voltage(-12, -12);
    wait(0.3, seconds);
    chassis.drive_with_voltage(0, 0);
    wait(0.3, seconds);
  }

  //Commented out bottom due to not enough time
  
  /*chassis.drive_with_voltage(-12, -12);
  wait(0.3, seconds);
  chassis.drive_with_voltage(0, 0);
  wait(0.3, seconds);
  chassis.drive_with_voltage(12, 12);
  wait(0.6, seconds);*/
  
/*
  chassis.set_drive_constants(11, 10, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 1200);
  chassis.drive_distance(1000, d);
  wait(0.5, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 300);
  chassis.drive_distance(-1000, d);
  //wait(1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 400);
  chassis.drive_distance(1000, d);
  wait(0.5, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 300);
  chassis.drive_distance(-1000, d);
  //wait(1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 400);
  chassis.drive_distance(1000, d);/*
  wait(0.5, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-10, d);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(100, d);
  wait(0.5, seconds);/*
  chassis.set_drive_exit_conditions(1.5, 300, 1200);
  thread(task1).detach();
  chassis.drive_distance(-10000, 47);
  wait(15, seconds);*/
}

void auton_task(){
  double d = -5;

  thread(doinkerRush).detach();
  chassis.drive_distance(42);
  thread(doinkerInDelay).detach();
  chassis.drive_distance(-12);
  
  chassis.set_turn_constants(6, .4, .03, 3, 15);
  chassis.turn_to_angle(163 - d);
  chassis.set_turn_constants(11, .4, .03, 3, 15);
  chassis.drive_distance(-12);

  thread(ArmDown).detach();
  chassis.drive_distance(-2);
  chassis.turn_to_angle(140 - d + 77.5);
  Intake.spin(forward);

  FrontIntake.spin(forward);
  thread(task3).detach();
  chassis.drive_distance(12);
  MogoPneu.set(false);

  chassis.turn_to_angle(77.5 - d + 360);
  chassis.drive_distance(-28);
  thread(ArmDown).detach();
  chassis.drive_distance(-2);

  chassis.drive_distance(6);  
  chassis.turn_to_angle(47);
  corner();
  /*

  chassis.turn_to_angle(-132 - d);
  Intake.spin(forward);
  chassis.drive_distance(21);
  FrontIntake.spin(forward);

  //MogoPneu.set(false);
  chassis.drive_distance(32);
  chassis.drive_distance(-60);
  /* //16.5
  chassis.right_swing_to_angle(0);
  thread(task2).detach();

  chassis.drive_distance(-9);
  
  /*
  double d = 0;
  thread(doinkerRush).detach();

  chassis.set_heading_constants(6, .06, 0, 1, 0);
  FrontIntake.spin(forward);
  chassis.drive_distance(42, 45);
  thread(doinkerInDelay).detach();

  chassis.drive_distance(-22);/*
  chassis.turn_to_angle(-4 + 180 - d);

  chassis.drive_distance(-12);
  thread(ArmDown).detach();
  Intake.spin(forward);
  chassis.drive_distance(-2);
  /*
  
  chassis.set_turn_constants(6, .4, .03, 3, 15);
  chassis.turn_to_angle(162 - d);
  chassis.set_turn_constants(11, .4, .03, 3, 15);
  chassis.drive_distance(-12);

  thread(ArmDown).detach();
  Intake.spin(forward);
  chassis.drive_distance(-2);
  chassis.turn_to_angle(90 + 162 - d);

  FrontIntake.spin(forward);
  chassis.drive_distance(12);




  /*
  chassis.turn_to_angle(140 - d + 77.5);
  Intake.spin(forward);

  FrontIntake.spin(forward);
  thread(task3).detach();
  chassis.drive_distance(12);
  MogoPneu.set(false);

  chassis.turn_to_angle(57.5 - d);
  chassis.drive_distance(-30);
  thread(ArmDown).detach();
  chassis.drive_distance(-2);

  chassis.turn_to_angle(77.5 - d + 90 + 45 + 30);
  chassis.drive_distance(30);
  chassis.set_turn_constants(6, .4, .03, 3, 15);
  FrontIntake.spin(forward);
  Intake.spin(forward);

  chassis.drive_distance(14);
  chassis.turn_to_angle(0 - d);
  Intake.spin(forward);
  chassis.drive_distance(-24);
  /*
  chassis.drive_distance(5);
  chassis.turn_to_angle(52 - d);
  /*
  chassis.right_swing_to_angle(45);
  //chassis.drive_distance(-12);

 // chassis.left_swing_to_angle(45 - d);
  *//*thread(getWallStake).detach();
  chassis.drive_distance(6);
  wait(0.5, seconds);
  thread(task1).detach();

  chassis.drive_distance(-9);
  chassis.turn_to_angle(-107.5 - d);
  FrontIntake.spin(forward);
  Intake.spin(forward);

  chassis.drive_distance(10);
  chassis.turn_to_angle(-195 - d);
  chassis.drive_distance(60);
  /*
  thread(task5).detach();
  chassis.left_swing_to_angle(-90);
  wait(1, seconds);
  chassis.set_drive_constants(7, 1.5, 0, 10, 0);

  FrontIntake.spin(forward);
  thread(task4).detach();
  chassis.drive_distance(34, -100);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);

  chassis.turn_to_angle(-213);
  chassis.set_drive_constants(7, 1.5, 0, 10, 0);
  FrontIntake.stop();
  chassis.drive_distance(-36);

  thread(ArmDown).detach();
  chassis.drive_distance(-2);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.turn_to_angle(0);
  
  Intake.spin(forward);
  FrontIntake.spin(forward);
  chassis.drive_distance(24);
  chassis.turn_to_angle(63.4349488 + 6);
  chassis.drive_distance(36);/* 
  //Add corner items here

  thread(task1).detach();
  thread(task4).detach();
  chassis.drive_distance(-78, 45);
  /*chassis.set_heading_constants(6, .0635, 0, 1, 0);
  chassis.drive_distance(-46, 30);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  thread(ArmDown).detach();
  chassis.drive_distance(-2);

  Intake.spin(forward);
  chassis.turn_to_angle(-13);
  Intake.stop();
  FrontIntake.spin(forward);

  chassis.drive_distance(11.75);
  MogoPneu.set(false);
  chassis.turn_to_angle(-95);
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);

  chassis.drive_distance(-22);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  thread(ArmDown).detach();
  chassis.drive_distance(-4);

  Intake.spin(forward);
  chassis.turn_to_angle(40);
  chassis.set_drive_constants(7, 1.5, 0, 10, 0);
  thread(task4).detach();

  chassis.drive_distance(34);
  MogoPneu.set(false);
  wait(0.4, seconds);

  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  Intake.stop();
  chassis.drive_distance(16);
  chassis.drive_distance(-15);

  chassis.set_turn_exit_conditions(1, 300, 900);
  chassis.turn_to_angle(178);
  thread(ArmUp).detach();
  chassis.drive_distance(-15);

  thread(task1).detach();
  chassis.drive_distance(28);



  /*

  thread(task3).detach();
  chassis.drive_distance(34);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-20 - 13.5);

  chassis.left_swing_to_angle(180);
  thread(ArmUp).detach();
  chassis.set_drive_exit_conditions(0.3, 300, 900);
  chassis.drive_distance(-9);
  


  /*
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);
  chassis.drive_distance(-18.75);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.turn_to_angle(-90);
  thread(ArmUp).detach();

  chassis.set_drive_exit_conditions(0.3, 300, 900);
  chassis.drive_distance(-6.25);
  chassis.set_drive_exit_conditions(0.3, 300, 700);
  FrontIntake.spin(forward);
  
  chassis.right_swing_to_angle(-27 - 90);
  chassis.drive_distance(15);
  wait(0.05, seconds);
  thread(task3).detach();
  chassis.drive_distance(10);

  chassis.set_drive_exit_conditions(0.3, 300, 1200);
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);
  chassis.drive_distance(-24.75);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.turn_to_angle(-54 - 180);

  chassis.set_drive_exit_conditions(0.3, 300, 2000);
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);
  chassis.drive_distance(-42);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(0.3, 300, 1200);
  thread(task2).detach();

  MogoPneu.set(true);
  wait(0.5, seconds);
  chassis.turn_to_angle(-360);
  thread(task2).detach();

  FrontIntake.spin(forward);
  chassis.drive_distance(20);
  thread(task3).detach();
  chassis.turn_to_angle(-360 - 135);
  thread(task1).detach();
  chassis.drive_distance(20);



  /*
  chassis.set_drive_constants(11, 1.1, 0, 10, 0);
  chassis.drive_distance(-50);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  thread(ArmDown).detach();

  chassis.drive_distance(-2);
  chassis.turn_to_angle(-37.1371653);
  Intake.spin(forward);
  FrontIntake.spin(forward);

  chassis.drive_distance(19.0416565);
  wait(1, seconds);
  Intake.stop();
  MogoPneu.set(false);
/*
  chassis.turn_to_angle(-90 - 28.0724869);
  chassis.set_drive_constants(8, 0.7, 0, 10, 0);
  chassis.drive_distance(-22);
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);

  thread(ArmDown).detach();
  chassis.drive_distance(-2);
  chassis.turn_to_angle(16.9275131);
  spinIntakeForward();

  chassis.set_drive_constants(8, 0.7, 0, 10, 0);
  chassis.drive_distance(27);
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);
  chassis.drive_distance(16);

  wait(0.5, seconds);
  chassis.drive_distance(-27 - 16);
  chassis.turn_to_angle(16.9275131 + 90);
  thread(ArmUp).detach();

  chassis.drive_distance(17);

  

 /* thread(ArmUp).detach();
  Arm.spinFor(reverse, 325, degrees);
  chassis.drive_distance(10.5);
  Arm.spinFor(forward, 175, degrees);

  chassis.left_swing_to_angle(-4.5);
  chassis.set_drive_constants(11, 0.5, 0, 10, 0);
  chassis.drive_distance(-36);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);

  thread(ArmDown).detach();
  chassis.drive_distance(-2);
  chassis.set_drive_exit_conditions(0.3, 0, 1000);
  chassis.turn_to_angle(-134);
  Intake.spin(forward);

  chassis.drive_distance(24);
  wait(0.4, seconds);
  chassis.turn_to_angle(34 - 1); //34 from earlier
  chassis.drive_distance(31.125 + 3.5);

  chassis.set_turn_constants(5, .4, .03, 3, 15);
  DoinkerPneu.set(true);
  chassis.turn_to_angle(76.75);
  DoinkerPneu.set(false);
  chassis.turn_to_angle(65);

  Intake.spin(forward);
  chassis.drive_distance(20);
  chassis.right_swing_to_angle(167.5 - 35);
  chassis.drive_distance(18);
  chassis.set_drive_exit_conditions(0.3, 300, 400);
  Arm.spinFor(reverse, 100, degrees);
  
  /*
  MogoPneu.set(true);
  wait(0.5, seconds);
  thread(ArmPickup).detach();
  chassis.set_drive_constants(11, 0.5, 0, 10, 0);

  chassis.drive_distance(42);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.drive_distance(18);
  *//*
  thread(ArmUp).detach();
  Arm.spinFor(reverse, 325, degrees);
  chassis.drive_distance(10.5);
  Arm.spinFor(forward, 175, degrees);

  chassis.left_swing_to_angle(-4.5);
  chassis.set_drive_constants(11, 0.5, 0, 10, 0);
  chassis.drive_distance(-36);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);

  thread(ArmDown).detach();
  chassis.drive_distance(-2);
  chassis.set_drive_exit_conditions(0.3, 0, 1000);
  chassis.turn_to_angle(-135 + 2.5);
  Intake.spin(forward);

  chassis.drive_distance(28.75);
  chassis.turn_to_angle(60 - 26.7915155 + 3);
  chassis.set_drive_constants(11, 0.5, 0, 10, 0);
  chassis.drive_distance(56.5729617 - 5);
  
  thread(ArmPickup).detach();
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.drive_distance(18 + 5 + 18);/*
  wait(0.6, seconds);
  chassis.drive_distance(-30);

  chassis.right_swing_to_angle(167.5 - 35);
  Arm.spinFor(reverse, 100, degrees);
  chassis.drive_distance(18);
  /*
  thread(ArmPickup).detach();
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.drive_distance(45);
  chassis.drive_distance(-7.625 - 4.5);

  chassis.turn_to_angle(-91);
  chassis.set_drive_constants(11, 0.5, 0, 10, 0);
  chassis.drive_distance(-27);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);

  thread(ArmDown).detach();
  chassis.drive_distance(-2);
*/
  /*wait(0.4, seconds);
  chassis.turn_to_angle(34);
  thread(ArmPickup).detach();
  chassis.drive_distance(31.125 + 3.5 + 30);


  /*DoinkerPneu.set(true);
  chassis.turn_to_angle(76.75);
  DoinkerPneu.set(false);
  chassis.turn_to_angle(65);

  Intake.spin(forward);
  chassis.drive_distance(14);
  chassis.right_swing_to_angle(167.5 - 35);
  Arm.spinFor(reverse, 100, degrees);
  chassis.drive_distance(18);
  
  /*
  Arm.spinFor(reverse, 100, degrees);
  chassis.left_swing_to_angle(105);
  chassis.drive_distance(25);

  /*
  chassis.drive_distance(-12.5-7.5);
  
  chassis.left_swing_to_angle(-30);
  chassis.right_swing_to_angle(0);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(-8);
  /*chassis.drive_distance(-8.75);
  chassis.turn_to_angle(0);
  chassis.drive_distance(-7-1.5);

  MogoPneu.set(true);
  wait(0.4, seconds);
  chassis.turn_to_angle(-131);
  Intake.spin(forward);

  double resist = 4.0;
  chassis.drive_distance(27 - resist);
  wait(0.6, seconds);
  chassis.drive_distance(11 - 27 + resist);

  chassis.turn_to_angle(105);
  chassis.drive_distance(20);

  
  /*wait(0.3, seconds);
  chassis.turn_to_angle(-190);
  Intake.spin(forward);

  double firstRingDist = 21.75 - 4;
  chassis.drive_distance(firstRingDist);
  chassis.drive_distance(11 - firstRingDist);
  chassis.turn_to_angle(105);

  chassis.drive_distance(24 - 7.5);
  /*Pre-auton
  int d = matchloadangle;
  double firstMogoError = 0.0825;
  int firstRingAngle = -112;
  double secondRingBite = 50.375+7.5;
  double secondRingResist = 18;

  /*Auton goes here
  ArmPickup();
  
  /*Add arm placement of preload here
  chassis.set_drive_constants(7, 1.5, 0, 10, 0);
  thread(ArmUp).detach();
  chassis.drive_distance(-10+firstMogoError*1.73205081);
  chassis.turn_to_angle(-30*m);
  chassis.set_drive_exit_conditions(0.2, 0, 1000);

  chassis.drive_distance(-14-firstMogoError*2);
  MogoPneu.set(true);
  chassis.set_drive_exit_conditions(0.3, 300, 1000);
  Intake.spin(forward);

  wait(0.6, seconds);
  chassis.turn_to_angle(firstRingAngle*m);
  chassis.drive_distance(16.25);
  wait(1, seconds);

  chassis.turn_to_angle(63.5*m);
  IntakePneu.set(true);
  Intake.spin(forward);
  chassis.drive_distance(secondRingBite - secondRingResist);

  wait(1, seconds);
  chassis.drive_distance(secondRingResist - secondRingBite + 13);
  chassis.turn_to_angle(135*m);
  chassis.drive_distance(20);
  /*thread(ArmDown).detach();
  wait(1, seconds);
  chassis.right_swing_to_angle(0);

  thread(ArmUp).detach();
  wait(1, seconds);
  chassis.drive_distance(3);
  Arm.spinFor(forward, 400, degrees);
  chassis.drive_distance(-17.5);  /*
  chassis.turn_to_angle(45);

  chassis.drive_distance(-secondRingBite + 12.5);
  chassis.turn_to_angle((90+d)*m);
  chassis.drive_distance(24);
  ArmUp();

  /*chassis.drive_distance(-8, 0+d);
  chassis.set_drive_constants(11, 0.7, 0, 10, 0);
  chassis.turn_to_angle(-30+d);  
  chassis.drive_distance(-16.5, 3-30+d);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0); 
  MogoPneu.set(true);

  wait(0.3, seconds);
  Intake.spin(forward);
  chassis.left_swing_to_angle(-93.5+d);
  chassis.drive_distance(24);

  chassis.turn_to_angle(67.5+d);
  Claw.set(true);
  chassis.set_drive_exit_conditions(1.5, 300, 817);
  chassis.drive_distance(61.8);
  wait(0.3, seconds);
  MogoPneu.set(false);

  chassis.turn_to_angle(180+d);
  chassis.set_drive_constants(11, 0.7, 0, 10, 0);  
  chassis.drive_distance(-22);/**/
}
void regular(){
  chassis.regulate();
  auton_task();
}
void mirrored(){
  chassis.mirror();
  auton_task(); 
}

void macroArm(){
  while (true) {
    if (DistSensor.objectDistance(inches) < 1) {
      Intake.spinFor(reverse, 10, turns);
      break;
    }
    else  {
      Intake.spin(forward);
    }

    wait(0.02, seconds);
  }
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

void reglar/*tank_odom_test*/(){
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