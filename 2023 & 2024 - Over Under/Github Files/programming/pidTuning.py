proportional = 0
derivative = 0
integral = 0
ki = 1.2
kd = 1

def PStraight_dist_head_velo_kp(PStraight_dist_head_velo_kp__dist, PStraight_dist_head_velo_kp__head, PStraight_dist_head_velo_kp__velo, PStraight_dist_head_velo_kp__kp):
    global proportional, derivative, kd, integral, ki
    LeftDrive.set_position(0, DEGREES)
    RightDrive.set_position(0, DEGREES)
    LeftDrive.spin(FORWARD)
    RightDrive.spin(FORWARD)
    if PStraight_dist_head_velo_kp__velo > 0:
        while 30 * PStraight_dist_head_velo_kp__dist > LeftDrive.position(DEGREES):
            derivative = PStraight_dist_head_velo_kp__head - inertial_7.rotation(DEGREES)
            proportional = PStraight_dist_head_velo_kp__kp * (kd * derivative)
            LeftDrive.set_velocity((PStraight_dist_head_velo_kp__velo + proportional), PERCENT)
            RightDrive.set_velocity((PStraight_dist_head_velo_kp__velo - proportional), PERCENT)
            wait(5, MSEC)
    else:
        while LeftDrive.position(DEGREES) > 30 * PStraight_dist_head_velo_kp__dist:
            derivative = PStraight_dist_head_velo_kp__head - inertial_7.rotation(DEGREES)
            proportional = PStraight_dist_head_velo_kp__kp * (kd * derivative)
            LeftDrive.set_velocity((PStraight_dist_head_velo_kp__velo + proportional), PERCENT)
            RightDrive.set_velocity((PStraight_dist_head_velo_kp__velo - proportional), PERCENT)
            wait(5, MSEC)
    LeftDrive.stop()
    RightDrive.stop()

def PTurn_head(PTurn_head__head):
    global proportional, derivative, kd, integral, ki
    integral = 90
    LeftDrive.set_position(0, DEGREES)
    RightDrive.set_position(0, DEGREES)
    LeftDrive.spin(FORWARD)
    RightDrive.spin(FORWARD)
    if inertial_7.rotation(DEGREES) > PTurn_head__head:
        while integral > 2:
            integral = ki * (PStraight_dist_head_velo_kp__head - inertial_7.rotation(DEGREES))
            LeftDrive.set_velocity((0 + integral), PERCENT)
            RightDrive.set_velocity((0 - integral), PERCENT)
            wait(5, MSEC)
    else:
        while integral > 2:
            integral = ki * (PStraight_dist_head_velo_kp__head - inertial_7.rotation(DEGREES))
            LeftDrive.set_velocity((0 + integral), PERCENT)
            RightDrive.set_velocity((0 - integral), PERCENT)
            wait(5, MSEC)
    LeftDrive.stop()
    RightDrive.stop()

def init():
    global proportional, derivative, kd, integral, ki
    kd = 1
    ki = 1.2
    PStraight_dist_head_velo_kp(1, 1, 1, 1)

init()

