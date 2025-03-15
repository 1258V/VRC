#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor LeftFront = motor(PORT11, ratio6_1, true);
motor LeftBack = motor(PORT12, ratio6_1, true);
motor RightFront = motor(PORT16, ratio6_1, false);
motor RightBack = motor(PORT17, ratio6_1, false);
motor StackedLeft = motor(PORT13, ratio6_1, false);
motor StackedRight = motor(PORT19, ratio6_1, true);
inertial Inertial13 = inertial(PORT2);
digital_out RightDoinker = digital_out(Brain.ThreeWirePort.D);
digital_out LeftDoinker = digital_out(Brain.ThreeWirePort.B);
digital_out MogoPneu = digital_out(Brain.ThreeWirePort.A);
digital_out HangPneu = digital_out(Brain.ThreeWirePort.H);
motor Arm = motor(PORT20, ratio18_1, true);
motor Conveyer = motor(PORT18, ratio6_1, true);
motor Intake = motor(PORT1, ratio6_1, true);
limit LimitSwitchC = limit(Brain.ThreeWirePort.G);
distance DistSensor = distance(PORT8);
rotation ArmRotation = rotation(PORT10, true);
optical Opt = optical(PORT15);

void vexcodeInit( void ) {
  
}