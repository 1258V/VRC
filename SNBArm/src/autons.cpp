#include "vex.h"
int matchloadangle = 167;

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

void pickBlueMid() {
  int counter=0;
  bool red = false;
  while (true) {
    if (Opt.hue() >=100) {
      if (counter==0){
        red = true;
        Intake.stop();
        Conveyer.stop();
        counter+=1;
      }
    }
  }
}
void expelRed() {
  int counter=0;
  bool blue = false;
  while (true) {
    if (Opt.hue() <= 30 || Opt.hue() >=330) {
      blue = true;
    }
    if (DistSensor.objectDistance(inches) < 2 && blue && counter==0) {
      MogoPneu.set(false);
      counter+=1;
    }
  }
}
void byebyemogo() {
  int counter=0;
  bool red = false;
  while (true) {
    if (Opt.hue() <= 30 || Opt.hue() >= 330) {
      red = true;
    }
    if (DistSensor.objectDistance(inches) < 2 && red && counter!=1) {
      wait(1, seconds);
      MogoPneu.set(false);
      red = false;
      counter+=1;
    }
  }
}

void byemogo(){
  wait(1, seconds);
  MogoPneu.set(false);
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

void BarTouch(){
  Arm.setVelocity(50, percent);
  Arm.spinTo(630, degrees);
}
void ArmDown(){
  wait(0.3, seconds);
  MogoPneu.set(true);
}
void ArmUp(){
  Arm.setVelocity(40, percent);
  Arm.spinTo(-620, degrees);
}
void IntakeStop(){
  wait(0.18, seconds);
  Intake.stop();
  Conveyer.stop();
  wait(0.18, seconds);
  MogoPneu.set(false);
}
void IntakeStop1(){
  Intake.stop();
  Conveyer.stop();
}
void MogoDown(){
  MogoPneu.set(true);
}
void ConveyerStop(){
  wait(0.24, seconds);
  Conveyer.stop();
}
void rushmid(){
  //wait(2, seconds);
  int d = matchloadangle;
  chassis.drive_distance(43, -13+d);
  chassis.set_drive_constants(11, 1, 1, 10, 0);
  Intake.spin(forward);
  //IntakeBack.spin(forward);
  //wait(0.1, seconds);
  //IntakeFront.stop();
  chassis.drive_distance(8, -13+d);
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
  chassis.set_drive_exit_conditions(1.5, 300, 400); //800
  wait(0.2, seconds);
  chassis.drive_distance(-12, -13+d);
  Conveyer.spin(forward);
  thread(ConveyerStop).detach();
  chassis.set_swing_exit_conditions(1, 300, 700);
  chassis.right_swing_to_angle(-62+d);
  chassis.set_swing_exit_conditions(1, 300, 1000);
  //thi sis for pickup on closer side to middle
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  chassis.drive_distance(7.7);
  //IntakeFront.stop();
  //chassis.left_swing_to_angle(-127+d); //-135
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  wait(0.4, seconds);
  chassis.drive_distance(-12.7,-64+d); //19
  chassis.set_drive_constants(5, 1.2, 0, 10, 0);
  //chassis.right_swing_to_angle(-110+d);
  chassis.set_drive_exit_conditions(1.5, 300, 500);
  chassis.drive_distance(-12);
  thread(ArmDown).detach();
  wait(0.4, seconds);
  chassis.set_swing_exit_conditions(1, 100, 500);
  chassis.right_swing_to_angle(-93+d); //-70+d
  chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  Conveyer.spin(forward);
  //IntakeFront.spin(forward);
  chassis.drive_distance(20.2, -93+d); // 14,-90+d
  //wait(0.2, seconds);
  //wait(0.5, seconds);
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
  wait(0.38, seconds);
  Conveyer.stop();
  chassis.turn_to_angle(140+d);
  Conveyer.spin(forward);
  chassis.drive_distance(24);
  chassis.right_swing_to_angle(102+d);

  thread(IntakeStop).detach();
  chassis.set_drive_exit_conditions(1.5, 400, 1100);
  chassis.drive_distance(37);
  //thread(MogoDown).detach();
  chassis.turn_to_angle(-2.6+d);
  chassis.set_drive_exit_conditions(1.5, 300, 600);
  chassis.drive_distance(-13.3);
  Intake.spin(forward);
  Conveyer.spin(forward);
  wait(0.9, seconds);
  //Arm.setVelocity(50, percent);
  //thread(ArmUp).detach();
  thread(IntakeStop1).detach();
  chassis.set_drive_exit_conditions(1.5, 300, 1600);
  chassis.set_drive_constants(9, 0.9, 0, 10, 0);
  //thread(ArmUp).detach();
  chassis.drive_distance(37);


}


void solosig(){
  int d=-90; //-90
  Conveyer.setVelocity(100, percent);
  chassis.set_swing_exit_conditions(1, 300, 600);
  chassis.left_swing_to_angle(-90);
  Conveyer.spin(forward);
  wait(0.3, seconds);
  chassis.set_drive_constants(5, 1.5, 0, 10, 0);
  thread(pickBlueMid).detach();
  Intake.spin(forward);

  chassis.drive_distance(15, -90);
  wait(0.2, seconds);
  chassis.drive_distance(8, -90);
  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  chassis.set_turn_exit_conditions(1, 300, 800);
  chassis.turn_to_angle(-214);
  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 650);
  chassis.drive_distance(-18.5);
  chassis.set_drive_constants(6.5, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 450);
  chassis.drive_distance(-8);
  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  thread(ArmDown).detach();
  wait(0.4, seconds);
  // chassis.set_turn_exit_conditions(1, 300, 750);
  // chassis.set_drive_constants(11, 1.2, 0, 10, 0);
  // chassis.drive_distance(-12, 178+d);
  // chassis.set_drive_exit_conditions(1.5, 300, 950);
  // chassis.drive_distance(-16, 178+d);
  // chassis.set_drive_constants(6, 1.2, 0, 10, 0);
  // chassis.set_drive_exit_conditions(1.5, 300, 700);
  // chassis.drive_distance(-12.5);
  // thread(ArmDown).detach();
  // wait(0.4, seconds);
  chassis.set_swing_exit_conditions(1, 100, 500);
  chassis.set_turn_exit_conditions(1, 100, 500);
  chassis.turn_to_angle(92+d); //-75+d
  chassis.set_drive_constants(12, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  Intake.spin(forward);
  Conveyer.spin(forward);
  //IntakeFront.spin(forward);
  chassis.drive_distance(20.2, 92+d); // 23.2,-75+d
  //wait(0.2, seconds);
  //wait(0.5, seconds);
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
  wait(0.09, seconds);
  Conveyer.stop();
  chassis.turn_to_angle(-140+d);
  thread(expelRed).detach();
  Conveyer.spin(forward);
  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  chassis.drive_distance(18.5, -140+d); //22.5
  thread(byemogo).detach();
  chassis.left_swing_to_angle(-88+d);
  chassis.set_drive_exit_conditions(1.5, 300, 980);
  wait(15, seconds);
  chassis.drive_distance(36.9);
  chassis.turn_to_angle(-207+d);
  //chassis.set_drive_exit_conditions(1.5, 300, 550);
  //chassis.drive_distance(-12, 180+d);
  chassis.set_drive_constants(6, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 600);
  thread(ArmUp).detach();
  MogoPneu.set(false);
  chassis.drive_distance(-14);
  thread(ArmDown).detach();
  wait(0.4, seconds);
  Intake.spin(forward);
  Conveyer.spin(forward);
  chassis.set_turn_exit_conditions(1, 100, 550);
  chassis.turn_to_angle(-72+d); //-70+d
  chassis.set_drive_constants(12, 1.2, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  //IntakeFront.spin(forward);
  chassis.drive_distance(22.5, -72+d); // 14,-90+d
  wait(0.09, seconds);
  Conveyer.stop();
  Intake.stop();
  chassis.set_turn_exit_conditions(1, 100, 750);
  chassis.turn_to_angle(63+d);
  Conveyer.spin(forward);
  Intake.spin(forward);
  chassis.drive_distance(27.5);
  Intake.stop();
  Conveyer.stop();
  wait(15, seconds);
}
