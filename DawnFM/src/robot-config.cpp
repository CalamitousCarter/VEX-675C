#include "vex.h"

using namespace vex;

brain Brain;
competition Competition;
controller user;

/* DRIVE MOTORS */
motor FL = vex::motor(PORT9, false);
motor FR = vex::motor(PORT20, false);
motor BL = vex::motor(PORT2, true);
motor BR = vex::motor(PORT12, true);

/* 4-BAR */
motor barA = vex::motor(PORT13, false);
motor barB = vex::motor(PORT5, true);

/* MOGO CLAMP */
motor grip = vex::motor(PORT4, false);

/* MOGO HOLDER */
motor claw = vex::motor(PORT10, false);

/* MOTOR GROUPS */
motor_group driveBase(FL,FR,BR,BL);
motor_group mogoGroup(barA,barB, grip, claw);
motor_group liftGroup(barA,barB);

void vexcodeInit(void) {
}