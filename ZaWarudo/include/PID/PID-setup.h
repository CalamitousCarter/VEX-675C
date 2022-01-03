/* SETTINGS */
extern double kP, kI, kD;
extern double kPT, kIT, kDT;

/* AUTON SETTINGS */
extern int desiredDriveVal;
extern int desiredTurnVal;

extern int error;
extern int prevError;
extern int totalError;
extern int derivative;

extern int errorT;
extern int prevErrorT;
extern int totalErrorT;
extern int derivativeT;

/* MODIFIER VARIABLES */
extern bool enableDrivePID, enableTurnPID;
extern bool resetDriveSensors;

extern float driveSConst, turnSConst;

/* PID FUNCTIONS */
extern int drivePID();