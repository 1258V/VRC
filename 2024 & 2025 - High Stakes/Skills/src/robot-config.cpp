#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor LeftFront = motor(PORT11, ratio6_1, true);
motor LeftBack = motor(PORT15, ratio6_1, true);
motor RightFront = motor(PORT13, ratio6_1, false);
motor RightBack = motor(PORT19, ratio6_1, false);
motor Left6th = motor(PORT12, ratio6_1, false);
motor Right6th = motor(PORT20, ratio6_1, true);
inertial Inertial13 = inertial(PORT14);
digital_out DoinkerPneu = digital_out(Brain.ThreeWirePort.B);
digital_out MogoPneu = digital_out(Brain.ThreeWirePort.H);
digital_out HangPneu = digital_out(Brain.ThreeWirePort.D);
motor Arm = motor(PORT18, ratio18_1, true);
motor Conveyer = motor(PORT10, ratio6_1, true);
motor Intake = motor(PORT9, ratio6_1, true);
distance DistSensor = distance(PORT8);
rotation ArmRotation = rotation(PORT16, false);
optical Opt = optical(PORT1);

void vexcodeInit( void ) {
  
}