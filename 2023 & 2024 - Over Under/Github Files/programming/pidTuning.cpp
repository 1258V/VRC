// User defined function
void myblockfunction_PStraight_dist_head_velo_kp(double myblockfunction_PStraight_dist_head_velo_kp__dist, double myblockfunction_PStraight_dist_head_velo_kp__head, double myblockfunction_PStraight_dist_head_velo_kp__velo, double myblockfunction_PStraight_dist_head_velo_kp__kp);
// User defined function
void myblockfunction_PTurn_head(double myblockfunction_PTurn_head__head);

float targetangle, proportional, angle, xpos, zpos;

// User defined function
void myblockfunction_PStraight_dist_head_velo_kp(double myblockfunction_PStraight_dist_head_velo_kp__dist, double myblockfunction_PStraight_dist_head_velo_kp__head, double myblockfunction_PStraight_dist_head_velo_kp__velo, double myblockfunction_PStraight_dist_head_velo_kp__kp) {
  LeftDrive.setPosition(0.0, degrees);
  RightDrive.setPosition(0.0, degrees);
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  if (myblockfunction_PStraight_dist_head_velo_kp__velo > 0.0) {
    while ((30.0 * myblockfunction_PStraight_dist_head_velo_kp__dist > LeftDrive.position(degrees))) {
      angle = myblockfunction_PStraight_dist_head_velo_kp__head - BrainInertial.rotation();
      proportional = angle * myblockfunction_PStraight_dist_head_velo_kp__kp;
      LeftDrive.setVelocity((myblockfunction_PStraight_dist_head_velo_kp__velo + proportional), percent);
      RightDrive.setVelocity((myblockfunction_PStraight_dist_head_velo_kp__velo - proportional), percent);
    wait(20, msec);
    }
  }
  else {
    while ((LeftDrive.position(degrees) > 30.0 * myblockfunction_PStraight_dist_head_velo_kp__dist)) {
      angle = myblockfunction_PStraight_dist_head_velo_kp__head - BrainInertial.rotation();
      proportional = angle * myblockfunction_PStraight_dist_head_velo_kp__kp;
      LeftDrive.setVelocity((myblockfunction_PStraight_dist_head_velo_kp__velo + proportional), percent);
      RightDrive.setVelocity((myblockfunction_PStraight_dist_head_velo_kp__velo - proportional), percent);
    wait(20, msec);
    }
  }
  LeftDrive.stop();
  RightDrive.stop();
}

// User defined function
void myblockfunction_PTurn_head(double myblockfunction_PTurn_head__head) {
  targetangle = 90.0;
  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  while ((targetangle > 2.0)) {
    if (myblockfunction_PTurn_head__head < BrainInertial.rotation()) {
      targetangle = 1.2 * (BrainInertial.rotation() - myblockfunction_PTurn_head__head);
      LeftDrive.setVelocity((0.0 - targetangle), percent);
      RightDrive.setVelocity((0.0 + targetangle), percent);
    }
    else {
      targetangle = 1.2 * (BrainInertial.rotation() - myblockfunction_PTurn_head__head);
      LeftDrive.setVelocity((0.0 - targetangle), percent);
      RightDrive.setVelocity((0.0 + targetangle), percent);
    }
  wait(20, msec);
  }
  LeftDrive.stop();
  RightDrive.stop();
}

// "when started" hat block
int init() {
  LeftDrive.setStopping(hold);
  RightDrive.setStopping(hold);
  BrainInertial.setRotation(0.0, degrees);
  BrainInertial.calibrate();
  while (BrainInertial.isCalibrating()) { task::sleep(50); }
  wait(1.0, seconds);
  myblockfunction_PStraight_dist_head_velo_kp(10.0, 0.0, 100.0, 2.0);
  myblockfunction_PTurn_head(-90.0);
  return 0;
}


int main() {
  init();
}
