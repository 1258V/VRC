#pragma once
#include "client/drive.h"

class Drive;

extern Drive chassis;

void alter();
void default_constants();

void ArmPickup();
void spinIntakeForward();
void ArmUp();
void macroArm();
void wallstake();
void auton_task();
void regular();
void mirrored();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void holonomic_odom_test();