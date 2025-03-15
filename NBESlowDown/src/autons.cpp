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

void ArmDown1(){
  Arm.spinFor(forward, 0.95, seconds);
}
void ArmDown(){
  wait(0.05, seconds);
  //wait(0.6, seconds);
  MogoPneu.set(true);
}

void ArmUp(){
  Arm.spinTo(-850, degrees);
}

void MogoDown1(){
  wait(0.7, seconds);
  MogoPneu.set(true);
}
void LeftDoinker(){
  wait(0.24, seconds);
  RightDoinkerPneu.set(false);
}
void DoinkersDown(){
  wait(0.23, seconds);
  LeftDoinkerPneu.set(true);
  wait(0.46, seconds);
  RightDoinkerPneu.set(true);
}

void wallstake(){
  int d=45;
  thread(ArmUp).detach();
  wait(0.75, seconds);
  chassis.set_drive_exit_conditions(0.3, 300, 170);
  chassis.drive_distance(-5);
  thread(ArmDown1).detach();
  chassis.set_turn_exit_conditions(1, 300, 500);
  chassis.turn_to_angle(1+d);
  chassis.set_drive_exit_conditions(0.3, 300, 1000);
  //chassis.drive_distance(-14);
  chassis.set_drive_constants(12, 0.5, 0, 10, 0);
  chassis.drive_distance(-40); //-15
  MogoPneu.set(true);
  wait(0.45, seconds);
  chassis.turn_to_angle(-129.5+d);
  Intake.setVelocity(50, percent);
  Intake.spin(reverse);
  chassis.set_drive_exit_conditions(0.3, 300, 800);
  chassis.drive_distance(22.6);
  chassis.set_swing_exit_conditions(1, 300, 500);
  chassis.left_swing_to_angle(-80+d);
  chassis.set_drive_exit_conditions(0.3, 300, 250);
  chassis.set_drive_constants(12, 5, 0, 10, 0);
  chassis.drive_distance(13);
  chassis.drive_distance(-3);
  chassis.set_drive_exit_conditions(0.3, 300, 250);
  wait(0.1, seconds);
  //chassis.drive_distance(-2);
  chassis.set_drive_exit_conditions(0.3, 300, 250);
  //chassis.drive_distance(3);
  //wait(0.2, seconds);
  chassis.turn_to_angle(-165+d);
  RightDoinkerPneu.set(true);
  wait(0.2, seconds);
  chassis.right_swing_to_angle(-150+d);
  LeftDoinkerPneu.set(true);
  wait(0.2, seconds);
  //chassis.drive_distance(6.7, -130+d);
  chassis.turn_to_angle(60+d);
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
  Conveyer.spin(forward);
  LeftDoinkerPneu.set(false);
  wait(0.2, seconds);
  thread(LeftDoinker).detach();
  chassis.set_drive_exit_conditions(0.3, 300, 800);
  chassis.set_drive_constants(9, 1, 0, 10, 0);
  chassis.drive_distance(-33, -60+d);
  chassis.drive_distance(20, -280+d);

}
void BarTouch(){
  Arm.setVelocity(50, percent);
  Arm.spinTo(630, degrees);
}
void MogoDown(){
  wait(0.0925, seconds);
  MogoPneu.set(true);
}
void DoinkerMid(){
  wait(0.2, seconds);
  RightDoinkerPneu.set(false);
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
void DoinkerDown(){
  wait(0.1, seconds);
  RightDoinkerPneu.set(true);
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
  wait(0.52, seconds);
  Conveyer.stop();
}
void rushmid(){
  //wait(2, seconds);
  int d = matchloadangle;
  Intake.spin(forward);
  chassis.set_drive_exit_conditions(0.3, 300, 710);
  chassis.set_drive_constants(12, 10, 0, 10, 0); //12
  chassis.drive_distance(24.6); //42, -166+d in sped up
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  chassis.set_drive_exit_conditions(0.3, 300, 1200);
  chassis.set_turn_exit_conditions(1, 300, 300);
  chassis.turn_to_angle(-156.8+d);
  chassis.set_drive_exit_conditions(0.3, 300, 300);
  chassis.set_drive_constants(12, 1000, 0, 10, 0);
  chassis.drive_distance(13.8, -160+d);
  chassis.set_drive_exit_conditions(0.3, 300, 1200);
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 400); //800
  wait(0.15, seconds);
  Conveyer.spin(forward);
  thread(ConveyerStop).detach();
  thread(DoinkerDown).detach();
  //chassis.drive_distance(-6); //testing this comment out
  chassis.set_swing_exit_conditions(1, 300, 400); //400 in sped up
  chassis.right_swing_to_angle(-120.6+d); //left swing to angle with the previous drive distance back
  //chassis.drive_distance(-8.7, -125.6+d); //-120.8, -120.3; -6.1, -120.5+d is the sped up version
  chassis.set_drive_constants(11, 2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 620); //650 in sped up
  chassis.drive_distance(-17); //-12.2, -121+d in sped up
  thread(ArmDown).detach();
  wait(0.45, seconds);
  chassis.set_swing_exit_conditions(1, 100, 550);
  thread(DoinkerMid).detach();
  chassis.left_swing_to_angle(-87+d); //-70+d
  chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  Conveyer.spin(forward);
  chassis.drive_distance(21, -87+d); // 14,-90+d
  chassis.set_swing_exit_conditions(1, 300, 300);
  chassis.set_drive_exit_conditions(1.5, 300, 700);
  //Intake.stop();
  //Conveyer.stop();
  chassis.set_turn_exit_conditions(1, 300, 660);
  chassis.turn_to_angle(0+d);
  //Intake.spin(forward);
  //Conveyer.spin(forward);
  chassis.drive_distance(24.3, 0+d); //24.3 in sped up
  //wait(0.1, seconds);
  chassis.set_swing_exit_conditions(1, 100, 350);
  thread(expelDiscBlue).detach();
  Conveyer.spin(forward);
  Intake.spin(forward);
  chassis.set_drive_constants(10, 4, 0, 10, 0);
  chassis.right_swing_to_angle(-45+d);
  chassis.set_drive_exit_conditions(1.5, 300, 750);
  chassis.drive_distance(100);
  wait(0.26, seconds);
  chassis.set_drive_constants(10, 2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 450);
  chassis.drive_distance(-15, -49+d);
  chassis.set_drive_exit_conditions(1.5, 300, 650);
  chassis.drive_distance(100, -49+d);
  wait(0.26, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 450);
  chassis.drive_distance(-15, -49+d);
  //wait(0.1, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 650);
  chassis.drive_distance(100, -49+d);
  wait(0.26, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 450);
  chassis.drive_distance(-15, -49+d);
  // chassis.set_drive_exit_conditions(1.5, 300, 500);
  // chassis.drive_distance(-10, -49+d);
  // //wait(0.1, seconds);
  // chassis.set_drive_exit_conditions(1.5, 300, 400);
  // chassis.drive_distance(100, -49+d);
  // wait(0.37, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 650);
  chassis.drive_distance(100, -49+d);
  wait(0.26, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 450);
  chassis.drive_distance(-15, -49+d);
  chassis.set_drive_exit_conditions(1.5, 300, 650);
  chassis.drive_distance(100, -49+d);
  wait(0.11, seconds);
  chassis.set_drive_constants(12, 20, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 1500);

  //good partners
  //chassis.set_drive_exit_conditions(1.5, 300, 1200);
  //chassis.drive_distance(-60, -90+d);
  //chassis.drive_distance(-60,-70+d);

  wait(15, seconds);

}
