#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor LeftFront = motor(PORT10, ratio6_1, true);
motor LeftBack = motor(PORT11, ratio6_1, true);
motor RightFront = motor(PORT9, ratio6_1, false);
motor RightBack = motor(PORT13, ratio6_1, false);
motor Left6th = motor(PORT7, ratio6_1, false);
motor Right6th = motor(PORT8, ratio6_1, true);
inertial Inertial13 = inertial(PORT5);
digital_out DoinkerPneu = digital_out(Brain.ThreeWirePort.B);
digital_out MogoPneu = digital_out(Brain.ThreeWirePort.H);
digital_out HangPneu = digital_out(Brain.ThreeWirePort.D);
motor Arm = motor(PORT1, ratio18_1, true);
motor Conveyer = motor(PORT20, ratio6_1, true);
motor Intake = motor(PORT6, ratio6_1, true);
distance DistSensor = distance(PORT8);
rotation ArmRotation = rotation(PORT2, true);
optical Opt = optical(PORT1);

void vexcodeInit( void ) {
  
}