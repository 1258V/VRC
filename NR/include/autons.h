#pragma once
#include "client/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void DriveStraight();
void NR();
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
void spinIntake();
void stopIntake();
int pickUpDisk();
void loadArm();