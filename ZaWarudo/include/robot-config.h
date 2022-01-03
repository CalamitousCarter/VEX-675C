using namespace vex;

extern brain Brain;

extern competition Competition;

extern controller user;

/* DRIVE MOTORS */
extern motor FL;
extern motor FR;
extern motor BL;
extern motor BR;

/* 4-BAR */
extern motor barA;
extern motor barB;

/* MOGO CLAMP*/
extern motor grip;

/* MOGO HOLDER */
extern motor carry;

/* MOTOR GROUPS */
extern motor_group driveBase;
extern motor_group mogoGroup;
extern motor_group liftGroup;

void vexcodeInit(void);
