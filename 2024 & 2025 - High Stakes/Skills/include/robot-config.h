using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;
extern motor StackedLeft;
extern motor StackedRight;
extern inertial Inertial13;
extern digital_out RightDoinker;
extern digital_out LeftDoinker;
extern digital_out MogoPneu;
extern digital_out HangPneu;
extern motor Arm;
extern motor Conveyer;
extern motor Intake;
extern limit LimitSwitchC;
extern distance DistSensor;
extern rotation ArmRotation;
extern optical Opt;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );