#include "vex.h"
int matchloadangle = 180;

void default_constants(){
  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_arm_constants(.4, 0, 2, 0);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(0.3, 300, 1200);
  chassis.set_turn_exit_conditions(1, 300, 1000); //reduced from 1800 to 1000
  chassis.set_swing_exit_conditions(1, 300, 1000);
  chassis.set_arm_exit_conditions(1, 100, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 0;
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
    if (DistSensor.objectDistance(inches) < 2 && red && counter==0) {
      wait(0.147, seconds); //0.154 for home
      Conveyer.stop();
      red = false;
      wait(0.05, seconds);
      Conveyer.spin(forward);
      counter+=1;
    }
    else if(DistSensor.objectDistance(inches) < 2 && red && counter==1) {
      wait(0.147, seconds); //0.146 for home
      Conveyer.stop();
      red = false;
      wait(0.05, seconds);
      Conveyer.spin(forward);
      counter+=1;
    }
  }
}

void wallstake(){
  // chassis.drive_distance(38);
  // chassis.set_swing_exit_conditions(1, 300, 500);
  // chassis.right_swing_to_angle(-39);
  // chassis.set_swing_exit_conditions(1, 300, 1000);
  // //thread(hs).detach();
  // Arm.spinTo(590, degrees); //585
  // //thread(hs).detach();
  // wait(0.4, seconds);
  // Arm.spinTo(-100, degrees);
  // chassis.right_swing_to_angle(36);
  // Intake.spin(forward);
  // Conveyer.spin(forward);
  // chassis.drive_distance(11);
  // wait(0.2, seconds);
  // Conveyer.stop();
  // chassis.drive_distance(-10);
  // chassis.left_swing_to_angle(60);
  // chassis.drive_distance(13);
  chassis.turn_to_angle(90);
  wait(15, seconds);
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
  wait(0.0925, seconds);
  MogoPneu.set(true);
}
void DoinkerMid(){
  wait(0.1, seconds);
  RightDoinkerPneu.set(true);
}
void getBlueArm(){
  int counter=0;
  bool red=false;
  while (true) {
    if (Opt.hue() <= 30 || Opt.hue() >= 330 ) {
      if(counter==0){
        wait(0.39, seconds);
        Conveyer.stop();
        Intake.stop();
        chassis.arm_to_angle(-29.8);
        Intake.spin(forward);
        Conveyer.spin(forward);
      }
    }
  }
}
void ConveyerStop(){
  //sped up version
  // int counter=0;
  // bool red = false;
  // while (true) {
  //   if (Opt.hue() >= 100) {
  //     red = true;
  //   }
  //   if (DistSensor.objectDistance(inches) < 2 && red && counter!=1) {
  //     wait(0.05, seconds);
  //     Conveyer.stop();
  //     counter+=1;
  //   }
  // }
  //slowed down
  wait(0.32, seconds);
  Conveyer.stop();
}
void rushmid(){
  //wait(2, seconds);
  int d = matchloadangle;
  Intake.spin(forward);
  chassis.set_drive_exit_conditions(0.3, 300, 900);
  chassis.set_drive_constants(12, 10, 0, 10, 0); //12
  chassis.drive_distance(24.6); //42, -166+d in sped up
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  chassis.set_drive_exit_conditions(0.3, 300, 1200);
  chassis.set_turn_exit_conditions(1, 300, 430);
  chassis.turn_to_angle(-156+d);
  thread(DoinkerMid).detach();
  chassis.set_drive_exit_conditions(0.3, 300, 300);
  chassis.set_drive_constants(12, 1000, 0, 10, 0);
  chassis.drive_distance(15, -162+d);
  wait(0.1, seconds);
  chassis.set_drive_exit_conditions(0.3, 300, 1200);
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  //Intake.spin(forward);
  //IntakeBack.spin(forward);
  //wait(0.1, seconds);
  //IntakeFront.stop();
  // this is only in sped up version - chassis.set_drive_exit_conditions(1.5, 300, 200);
  //chassis.drive_distance(3, -167+d); //-166+d in sped up
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
  wait(0.1, seconds);
  //the following line is COMMENTED OUT in sped up
  Conveyer.spin(forward);
  thread(ConveyerStop).detach();
  chassis.drive_distance(-6, -165+d);
  chassis.set_swing_exit_conditions(1, 300, 400); //400 in sped up
  //sped up is right swing
  chassis.left_swing_to_angle(-125.6+d); //-119.6 in sped up
  chassis.drive_distance(-8.7, -126.6+d); //-120.8, -120.3; -6.1, -120.5+d is the sped up version
  //could put arm down here and add wait before turning
  chassis.set_drive_constants(5, 1.2, 0, 10, 0);
  //chassis.right_swing_to_angle(-110+d);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //600 in sped up
  //this wait was NOT in the safe code
  //wait(0.02, seconds);
  chassis.drive_distance(-11.1); //-12.2, -121+d in sped up
  thread(ArmDown).detach();
  wait(0.45, seconds);
  chassis.set_swing_exit_conditions(1, 100, 550);
  chassis.left_swing_to_angle(-87+d); //-70+d
  RightDoinkerPneu.set(false);
  chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  Conveyer.spin(forward);
  //IntakeFront.spin(forward);
  chassis.drive_distance(21, -87+d); // 14,-90+d
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
  chassis.set_drive_exit_conditions(1.5, 300, 1200);
  Intake.stop();
  Conveyer.stop();
  chassis.turn_to_angle(0+d);
  Intake.spin(forward);
  Conveyer.spin(forward);
  chassis.drive_distance(33, 0+d); //24.3 in sped up
  //wait(0.1, seconds);
  chassis.set_swing_exit_conditions(1, 100, 350);
  //commented out in sped up code
  //chassis.right_swing_to_angle(-41+d);
  thread(expelDiscBlue).detach();
  Conveyer.spin(forward);
  Intake.spin(forward);
  chassis.set_drive_constants(12, 5, 0, 10, 0);
  chassis.right_swing_to_angle(-90+d);
  //chassis.set_drive_exit_conditions(1.5, 300, 300); //300 in safe
  //chassis.drive_distance(-10, -90+d);
  chassis.set_drive_exit_conditions(1.5, 300, 600);
  chassis.drive_distance(100); //-36 in sped up (curves) //used to be -45
  wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 600);
  chassis.right_swing_to_angle(-49+d);
  wait(0.1, seconds);
  //wait(1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(100, -49+d);
  wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 600);
  chassis.drive_distance(-15, -49+d);
  wait(0.1, seconds);
  //wait(1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(100, -49+d);
  wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 600);
  chassis.drive_distance(-10, -49+d);
  wait(0.1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
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
  chassis.set_drive_exit_conditions(1.5, 300, 1500);

  //good partners
  chassis.set_drive_exit_conditions(1.5, 300, 1200);
  chassis.drive_distance(-60, -90+d);
  chassis.drive_distance(-60,-70+d);

  //chassis.drive_distance(-60,-70+d);
  // bad partners
  //Intake.spin(forward);
  //Conveyer.spin(forward);
  //chassis.set_turn_exit_conditions(1, 300, 800);
  //chassis.turn_to_angle(104+d);
  //chassis.drive_distance(40, 100+d);
  //wait(0.1, seconds);
  //chassis.set_drive_constants(8, 1, 0, 10, 0);
  //thread(getBlueArm).detach();
  //chassis.drive_distance(40, 100+d);
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
