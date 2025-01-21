using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;
extern motor Left6th;
extern motor Right6th;
extern inertial Inertial13;
extern digital_out DoinkerPneu;
extern digital_out MogoPneu;
extern digital_out HangPneu;
extern motor Arm;
extern motor Conveyer;
extern motor Intake;
extern limit LimitSwitchC;
extern distance DistSensor;
extern rotation ArmRotation;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );