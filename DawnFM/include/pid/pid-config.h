// === Settings === 
extern double kP;
extern double kI;
extern double kD;

extern double kPT;
extern double kIT;
extern double kDT;

// === Autonomous Settings ===
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

// === Modifier Variables ===
extern bool enableDrivePID;
extern bool resetDriveSensors;

extern float driveLConst;
extern float driveRConst;
extern float turnLConst;
extern float turnRConst;

extern int drivePID();