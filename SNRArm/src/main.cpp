#include "vex.h"
bool runningSkills = false;
//Part of the code below (mainly the drivetrain constrictors) is used from the LemLib drive template, which is why you will notice a unique drivetrain setup
//This drivetrain setup is specifically made to allow the most efficient drive possible, using LemLib's battery saving technique while still providing high strength
//The drivetrain will stay on Ecos mode for most of the High Stakes challenge

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DigitalOutF          digital_out   F               
// LeftFront            motor         1               
// LeftBack             motor         12              
// RightFront           motor         8               
// RightBack            motor         20              
// Left6th              motor         14              
// Right6th             motor         18              
// Inertial13           inertial      13              
// WingPneu             digital_out   D               
// DoinkerPneu           digital_out   E               
// LimitSwitchC         limit         C               
// Catapult             motor         9               
// Intake               motor         11              
// MotorGroup17         motor_group   17, 16          
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                              LemLib Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Specify your drive setup below. There are seven options:
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".


//Left Motors:
motor_group(LeftFront, LeftBack, Left6th),

//Right Motors:
motor_group(RightFront, RightBack, Right6th),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT21,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
2.75,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

//Automatic Drivetrain Selector
motor_group Drivetrain = motor_group(LeftBack, LeftFront, RightFront, RightBack, Right6th, Left6th);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void) {
    //DO NOT REMOVE THE FOLLOWING TWO FUNCTIONS! The entire code will break!
    vexcodeInit();
    default_constants();

    Drivetrain.setStopping(coast);
    Inertial13.calibrate();
    Opt.setLightPower(100, percent);
    
    Arm.setStopping(hold);
    Arm.setMaxTorque(100, percent);
    Arm.setVelocity(100, percent);

    DoinkerPneu.set(false);
    HangPneu.set(false);

    Conveyer.setStopping(coast);
    Conveyer.setMaxTorque(100, percent);
    Conveyer.setVelocity(70, percent);
    
    Intake.setStopping(coast);
    Intake.setMaxTorque(100, percent);
    Intake.setVelocity(100, percent);

    LeftFront.setMaxTorque(100, percent);
    LeftBack.setMaxTorque(100, percent);
    Left6th.setMaxTorque(100, percent);
    RightBack.setMaxTorque(100, percent);
    RightFront.setMaxTorque(100, percent);
    Right6th.setMaxTorque(100, percent);

    LeftFront.setVelocity(100, percent);
    LeftBack.setVelocity(100, percent);
    Left6th.setVelocity(100, percent);
    RightFront.setVelocity(100, percent);
    RightBack.setVelocity(100, percent);
    Right6th.setVelocity(100, percent);
    Intake.setVelocity(100.0, percent);

    ArmRotation.setReversed(true);
    ArmRotation.resetPosition();

    Opt.setLightPower(100, percent);
  }

void autonomous(void) {
  //wallstake();
  //rushmid();
  solosig();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
bool mobilePneu = false;


void spinIntakeForwardSpec() {
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
  Conveyer.setVelocity(100, percent);
  Conveyer.spin(forward);
  wait(0.4, seconds);
  while(true){
    if(Conveyer.velocity(percent) < 5){
      Conveyer.stop();
      Intake.stop();
      break;
    }
  }
}

void loadArm() {
  Arm.setVelocity(100, percent);
  Arm.setMaxTorque(100, percent);
  chassis.arm_to_angle(-30);
  spinIntakeForwardSpec();
  
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

void spinIntakeForward() {
  Conveyer.setVelocity(100, percent);
  Conveyer.spin(forward);
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
  /*while(true){
    if(DistSensor.objectDistance(inches) < 1.5){
      Intake.stop();
    }
    else if(Optical6.hue() > 200 && Optical6.hue() < 300){
      //Intake.stop();
    }
    wait(10, msec);
  }*/
}

void spinIntakeReverse() {
  Conveyer.setVelocity(100, percent);
  Conveyer.spin(reverse);
  Intake.setVelocity(100, percent);
  Intake.spin(reverse);
}

void stopIntake() {
  Conveyer.stop();
  Intake.stop();
}

void toggleDoinkerPneuPos() {
  if (DoinkerPneu) {
    DoinkerPneu.set(false);
    DoinkerPneu = false;
  }
  else {
    DoinkerPneu.set(true);
    DoinkerPneu = true;
  }  
}

void triggerMogoMech() {
  if (mobilePneu) {
    MogoPneu.set(false);
    mobilePneu = false;
  }
  else {
    MogoPneu.set(true);
    mobilePneu = true;
  }
}

bool hangPneuPos = false;

void triggerHangMech() {
  hangPneuPos = !hangPneuPos;
  HangPneu.set(hangPneuPos);
}

bool DoinkerPneuPos = false;

void triggerDoinkerMech() {
  DoinkerPneuPos = !DoinkerPneuPos;
  DoinkerPneu.set(DoinkerPneuPos);
}

void moveArmUp() {
  Arm.setVelocity(100, percent);
  Arm.setMaxTorque(100, percent);
  Arm.spin(reverse);
}

void moveArmDown() {
  Arm.setVelocity(100, percent);
  Arm.setMaxTorque(100, percent);
  Arm.spin(forward);
}

void stopArm() {
  Arm.stop();
}

int DisplayToController() {

  while (true) {
    //controller(primary).Screen.print(Intake.velocity(rpm));
    //controller(primary).Screen.print(chassis.get_absolute_heading());
    controller(primary).Screen.print(ArmRotation.angle(degrees));
    vex::this_thread::sleep_for(1000);
  }

}

void usercontrol(void) {

    MogoPneu.set(true);

    Arm.setStopping(hold);
    Drivetrain.setStopping(coast);

    controller(primary).ButtonL2.pressed(spinIntakeReverse); 
    controller(primary).ButtonL2.released(stopIntake); 

    controller(primary).ButtonL1.pressed(spinIntakeForward);
    controller(primary).ButtonL1.released(stopIntake); 

    controller(primary).ButtonR1.pressed(triggerMogoMech);
    controller(primary).ButtonR2.pressed(loadArm);

    controller(primary).ButtonY.pressed(moveArmUp);
    controller(primary).ButtonY.released(stopArm);
    controller(primary).ButtonRight.pressed(moveArmDown);
    controller(primary).ButtonRight.released(stopArm);

    controller(primary).ButtonDown.pressed(triggerDoinkerMech);    

  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_tank();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

  vex::task t(DisplayToController);

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}