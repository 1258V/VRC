#pragma once
#include "client/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void DriveStraight();
void Auton43Points();
void Auton38Points();
void Auton26Points();
void mirrored();
void macro();
void subMacro();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void holonomic_odom_test();
int moveArmFullyDown();
int pickUpMogo();
int lowerArm();
void spinIntake();
void stopIntake();
void loadArm();
void auton();
int loadForWallStake();
void allowDisksThrough(); 