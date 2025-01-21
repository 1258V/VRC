#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
digital_out DigitalOutF = digital_out(Brain.ThreeWirePort.F);
motor LeftFront = motor(PORT1, ratio6_1, true);
motor LeftBack = motor(PORT12, ratio6_1, true);
motor RightFront = motor(PORT8, ratio18_1, false);
motor RightBack = motor(PORT20, ratio6_1, false);
motor Left6th = motor(PORT14, ratio6_1, false);
motor Right6th = motor(PORT18, ratio6_1, true);
inertial Inertial13 = inertial(PORT13);
digital_out WingPneu = digital_out(Brain.ThreeWirePort.D);
digital_out IntakePneu = digital_out(Brain.ThreeWirePort.E);
limit LimitSwitchC = limit(Brain.ThreeWirePort.C);
motor Catapult = motor(PORT9, ratio36_1, false);
motor Intake = motor(PORT11, ratio6_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
