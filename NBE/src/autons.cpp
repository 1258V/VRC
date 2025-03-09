#include "vex.h"
int matchloadangle = 167;

void default_constants(){
  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
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
void expelDiscBlue() {
  int counter=0;
  bool red = false;
  while (true) {
    if (Opt.hue() <= 30 || Opt.hue() >= 330) {
      red = true;
    }
    if (DistSensor.objectDistance(inches) < 2 && red) {
      wait(0.13, seconds); //0.159 for home
      red = false;
      Intake.stop();
      Conveyer.stop();
      wait(0.5, seconds);
      Intake.spin(reverse);
      Conveyer.spin(reverse);
      //counter+=1;
    }
  }
}

void wallstake(){
  int d=49;
  MogoPneu.set(true);
  wait(2, seconds);
  Intake.spin(forward);
  Conveyer.spin(forward);
  thread(expelDiscBlue).detach();
  chassis.set_drive_exit_conditions(1.5, 300, 300);
  chassis.drive_distance(100, -49+d);
  wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-18, -49+d);
  wait(0.1, seconds);
  //wait(1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 300);
  chassis.drive_distance(100, -49+d);
  wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-15, -49+d);
  wait(0.1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 300);
  chassis.drive_distance(100, -49+d);
  wait(0.37, seconds);
  thread(expelDiscBlue).detach();
}
void BarTouch(){
  Arm.setVelocity(50, percent);
  Arm.spinTo(630, degrees);
}
void ArmDown(){
  wait(0.05, seconds);
  //wait(0.6, seconds);
  MogoPneu.set(true);
}
void MogoDown(){
  wait(0.4, seconds);
  MogoPneu.set(false);
}
void getBlueArm(){
  int counter=0;
  bool red=false;
  while (true) {
    if (Opt.hue() <= 30 || Opt.hue() >= 330 ) {
      if(counter==0){
        wait(0.37, seconds);
        Conveyer.stop();
        Intake.stop();

      }
    }
  }
}
void ConveyerStop(){
  int counter=0;
  bool red = false;
  while (true) {
    if (Opt.hue() >= 100 && counter==0) {
      red = true;
      wait(0.07, seconds);
      Conveyer.stop();
      counter+=1;
    }
  }
}
void ConveyerSpin(){
  wait(0.35, seconds);
  Conveyer.spin(forward);
}
void rushmid(){
  //wait(2, seconds);
  int d = matchloadangle;
  Intake.spin(forward);
  chassis.drive_distance(40, -166+d); //42, -166+d in sped up
  chassis.set_drive_constants(12, 1, 0, 10, 0);
  //IntakeBack.spin(forward);
  //wait(0.1, seconds);
  //IntakeFront.stop();
  // this is only in sped up version - chassis.set_drive_exit_conditions(1.5, 300, 200);
  //chassis.drive_distance(8, -167+d); //-166+d in sped up
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
  //chassis.drive_distance(-8, -160+d);
  chassis.set_drive_exit_conditions(1.5, 300, 400); //800
  wait(0.2, seconds);
  //the following line is COMMENTED OUT in sped up
  //chassis.drive_distance(-12, -167+d);
  Conveyer.spin(forward);
  thread(ConveyerStop).detach();
  chassis.set_swing_exit_conditions(1, 300, 600); //400 in sped up
  //sped up is right swing
  chassis.right_swing_to_angle(-119.9+d); //-119.6 in sped up
  chassis.set_swing_exit_conditions(1, 300, 1000);
  //thi sis for pickup on closer side to middle
  chassis.set_drive_constants(12, 4, 0, 10, 0); //11,4,0,10,0 in sped up
  chassis.drive_distance(8.15, -117.0+d); //7.8 in sped up
  //IntakeFront.stop();
  //chassis.left_swing_to_angle(-127+d); //-135
  wait(0.7, seconds); //0.4
  chassis.set_drive_exit_conditions(1.5, 300, 200);
  chassis.drive_distance(-6.1, -120+d); //-120.8, -120.3; -6.1, -120.5+d is the sped up version
  //could put arm down here and add wait before turning
  chassis.set_drive_constants(7, 1.4, 0, 10, 0);
  //chassis.right_swing_to_angle(-110+d);
  chassis.set_drive_exit_conditions(1.5, 300, 600); //600 in sped up
  //this wait was NOT in the safe code
  //wait(0.02, seconds);
  chassis.drive_distance(-12.2, -120.9+d); //-12.2, -121+d in sped up
  thread(ArmDown).detach();
  wait(0.4, seconds);
  chassis.set_swing_exit_conditions(1, 100, 550);
  chassis.left_swing_to_angle(-83+d); //-70+d
  chassis.set_drive_constants(12, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  Conveyer.spin(forward);
  //IntakeFront.spin(forward);
  chassis.drive_distance(19.9, -81+d); // 14,-90+d
  //wait(0.5, seconds);
  // chassis.set_turn_exit_conditions(1, 100, 400);
  chassis.set_swing_exit_conditions(1, 300, 300);
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
  chassis.set_drive_exit_conditions(1.5, 300, 1100);
  wait(0.1, seconds);
  Intake.stop();
  Conveyer.stop();
  chassis.right_swing_to_angle(0+d);
  Intake.spin(forward);
  Conveyer.spin(forward);
  chassis.drive_distance(25, 0+d); //24.3 in sped up
  //wait(0.1, seconds);
  chassis.set_swing_exit_conditions(1, 100, 350);
  //commented out in sped up code
  chassis.right_swing_to_angle(-34+d);
  thread(expelDiscBlue).detach();
  Conveyer.spin(forward);
  Intake.spin(forward);
  chassis.set_drive_exit_conditions(1.5, 300, 450); //300 in safe
  chassis.drive_distance(100, -40+d); //-36 in sped up (curves)
  //wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-18, -44+d);
  wait(0.1, seconds);
  //wait(1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 300);
  chassis.drive_distance(100, -49+d);
  wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-18, -49+d);
  wait(0.1, seconds);
  //wait(1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 300);
  chassis.drive_distance(100, -49+d);
  wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-15, -49+d);
  wait(0.1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 300);
  chassis.drive_distance(100, -49+d);
  wait(0.37, seconds);
  //add this push back if needed *will not make it to other side*
  // chassis.set_drive_exit_conditions(1.5, 300, 600);
  // chassis.drive_distance(-10, -49+d);
  // wait(0.1, seconds);
  // chassis.set_drive_exit_conditions(1.5, 300, 300);
  // chassis.drive_distance(100, -49+d);
  // wait(0.37, seconds);
  chassis.set_drive_constants(12, 20, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  //good partners
  chassis.set_drive_exit_conditions(1.5, 300, 1200);
  chassis.drive_distance(-40, -90+d);
  chassis.drive_distance(-40,-110+d);
  // bad partners
  //Intake.spin(forward);
  //Conveyer.spin(forward);
  //chassis.set_turn_exit_conditions(1, 300, 800);
  //Intake.stop();
  //Conveyer.stop();
  //chassis.turn_to_angle(100+d);
  //Intake.spin(forward);
  //Conveyer.spin(forward);
  //thread(MogoDown).detach();
  //chassis.drive_distance(33, 100+d);
  //wait(0.1, seconds);
  //chassis.set_drive_constants(8, 1, 0, 10, 0);
  //thread(getBlueArm).detach();
  //chassis.set_drive_exit_conditions(1.5, 300, 700);
  //chassis.drive_distance(15, 109+d);
  //chassis.drive_distance(20, 120+d);
  // chassis.set_drive_constants(12, 20, 0, 10, 0);
  // chassis.set_drive_exit_conditions(1.5, 300, 250);
  // chassis.drive_distance(-5, 109+d);
  // chassis.turn_to_angle(180+d);
  // chassis.set_drive_exit_conditions(1.5, 300, 1500);
  // thread(ConveyerSpin).detach();
  // chassis.drive_distance(-100, 180+d);
  wait(15, seconds);
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
