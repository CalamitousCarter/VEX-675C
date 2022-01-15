#include "vex.h"
#include "math.h"
using namespace vex;

// === Settings === 
double kP = 0.45;
double kI = 0.001;
double kD = 0.55;

double kPT = 0.20;
double kIT = 0.0005;
double kDT = 0.045;

// === Autonomous Settings ===
int desiredDriveVal = 0;
int desiredTurnVal = 0;

int error; // current value - desired value : Positional
int prevError = 0; // Position 20 milliseconds ago
int totalError = 0; // Summation of all error
int derivative; // error - previous error : speed

int errorT;
int prevErrorT = 0;
int totalErrorT = 0;
int derivativeT = 0;

// === Modifier Variables ===
bool enableDrivePID = false;
bool enableTurnPID = false;
bool resetDriveSensors = false;

float driveLConst = .93;
float driveRConst = .98;
float turnLConst = .975;
float turnRConst = .975;

int drivePID(){
  while(enableDrivePID ){ 
    if(resetDriveSensors){
      resetDriveSensors = false;

      FL.setPosition(0, degrees);
      FR.setPosition(0, degrees);
      BL.setPosition(0, degrees);
      BR.setPosition(0, degrees);
    }
    // Get position of motors
    int LFPos = FL.position(degrees);
    int RFPos = FR.position(degrees);

    // Lateral PID
    if(desiredDriveVal != 0 && desiredTurnVal == 0){
      // Get average of motors
      int avgPos = (int) round((LFPos - RFPos)/-2.0);
      
      user.Screen.clearScreen();
      user.Screen.setCursor(1, 1);
      user.Screen.print(avgPos);
      // Potential
      error = desiredDriveVal -  avgPos;

      // Derivarive
      derivative = error - prevError;

      // Integral
      totalError += error;

      double lateralMotorPower = (error * kP + derivative * kD + totalError * kI)/12;

      FL.spin(reverse, lateralMotorPower * driveLConst, volt);
      FR.spin(forward, lateralMotorPower * driveRConst, volt);
      BL.spin(forward, lateralMotorPower * driveLConst, volt);
      BR.spin(reverse, lateralMotorPower * driveRConst, volt);

      prevError = error;
      task::sleep(20);
    }
    // Turn PID
    else if(desiredDriveVal == 0 && desiredTurnVal != 0){
      int turnDiff = (int) round((LFPos + RFPos)/2.0);

      user.Screen.clearScreen();
      user.Screen.setCursor(1, 1);
      user.Screen.print(turnDiff);
      // Potential
      errorT = turnDiff - desiredTurnVal;

      // Derivarive
      derivativeT = errorT - prevErrorT;

      // Integral
      totalErrorT += errorT;

      double turnMotorPower = (errorT * kPT) + (derivativeT * kDT) + (totalErrorT * kIT)/12;

      FL.spin(reverse, turnMotorPower * turnLConst, percent);
      FR.spin(reverse, (turnMotorPower) * turnRConst, percent);
      BL.spin(forward, (turnMotorPower) * turnLConst, percent);
      BR.spin(forward, (turnMotorPower) * turnRConst, percent);

      prevErrorT = errorT;
      task::sleep(20);
    }

    else if(desiredDriveVal == 0 && desiredTurnVal == 0){
      FL.setBrake(hold);
      FR.setBrake(hold);
      BL.setBrake(hold);
      BR.setBrake(hold);
    }
  }
  return 1;
}