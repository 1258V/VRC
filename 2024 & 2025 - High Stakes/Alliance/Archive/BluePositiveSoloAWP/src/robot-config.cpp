#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor LeftFront = motor(PORT16, ratio6_1, true);
motor LeftBack = motor(PORT17, ratio6_1, true);
motor RightFront = motor(PORT13, ratio6_1, false);
motor RightBack = motor(PORT14, ratio6_1, false);
motor Left6th = motor(PORT18, ratio6_1, true);
motor Right6th = motor(PORT15, ratio6_1, false);
inertial Inertial13 = inertial(PORT21);
digital_out DoinkerPneu = digital_out(Brain.ThreeWirePort.B);
digital_out MogoPneu = digital_out(Brain.ThreeWirePort.A);
digital_out HangPneu = digital_out(Brain.ThreeWirePort.D);
motor Arm = motor(PORT12, ratio18_1, false);
motor Intake = motor(PORT9, ratio6_1, false);
motor FrontIntake = motor(PORT11, ratio6_1, true);
limit LimitSwitchC = limit(Brain.ThreeWirePort.C);
distance DistSensor = distance(PORT11);
rotation ArmRotation = rotation(PORT10, true);
optical Optical6 = optical(PORT20);

void vexcodeInit( void ) {
  
}