using namespace vex;

extern brain Brain;
extern competition Competition;
extern controller user;

/* DRIVE MOTORS */
extern motor FL, FR;
extern motor BL, BR;

/* 4-BAR */
extern motor barA, barB;

/* MOGO CLAMP */
extern motor grip;

/* MOGO CLAW */
extern motor claw;

/* MOTOR GROUPS */
extern motor_group driveBase;
extern motor_group mogoGroup;
extern motor_group liftGroup;

void vexcodeInit(void);
