#include "vex.h"
#include "math.h"
using namespace vex;

// === Settings === 
double kP = 0.4;
double kI = 0.0;
double kD = 0.25;

double kPT = 0.23;
double kIT = 0.0;
double kDT = 0.025;

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

float driveSConst = 1.0;
float turnSConst = 0.8;
float maxPow = 11.05f;

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
      int avgPos = (LFPos - RFPos)/-2;
      
      user.Screen.clearScreen();
      user.Screen.setCursor(1, 1);
      user.Screen.print(avgPos);
      // Potential
      error = desiredDriveVal -  avgPos;

      // Derivarive
      derivative = error - prevError;

      // Integral
      totalError += error;

      double lateralMotorPower = 
          fmin(12, (error * kP + derivative * kD + totalError * kI)/12);

      FL.spin(reverse, fmin(maxPow,lateralMotorPower) * driveSConst, volt);
      FR.spin(forward, lateralMotorPower * driveSConst, volt);
      BL.spin(forward, fmin(maxPow,lateralMotorPower) * driveSConst, volt);
      BR.spin(reverse, lateralMotorPower * driveSConst, volt);

      prevError = error;
      task::sleep(20);
    }
    // Turn PID
    else if(desiredDriveVal == 0 && desiredTurnVal != 0){
      int turnDiff = (LFPos + RFPos)/2;

      user.Screen.clearScreen();
      user.Screen.setCursor(1, 1);
      user.Screen.print(turnDiff);
      // Potential
      errorT = turnDiff - desiredTurnVal;

      // Derivarive
      derivativeT = errorT - prevErrorT;

      // Integral
      totalErrorT += errorT;

      double turnMotorPower =
          fmin(12, (errorT * kPT) + (derivativeT * kDT) + (totalErrorT * kIT));

      FL.spin(reverse, fmin(maxPow, (turnMotorPower)) * turnSConst, percent);
      FR.spin(reverse, (turnMotorPower) * turnSConst, percent);
      BL.spin(forward, fmin(maxPow, (turnMotorPower)) * turnSConst, percent);
      BR.spin(forward, (turnMotorPower) * turnSConst, percent);

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