#include "vex.h"
using namespace vex;

void driveFwd(int dist, int sleepTime){
  resetDriveSensors = true;
  desiredDriveVal = dist;
  desiredTurnVal = 0;
  task::sleep(sleepTime);
}

void driveTurn(int rot, int sleepTime){
  resetDriveSensors = true;
  desiredTurnVal = rot;
  desiredDriveVal = 0;
  task::sleep(sleepTime);
}

void constUpdate(float left, float right){
  driveLConst = left;
  driveRConst = right;
}

void motorRotate(motor mot, int dist, int vel, int timing){
  mot.rotateFor(forward, dist, rotationUnits::deg, vel, velocityUnits::pct);
  task::sleep(timing);
}

void motorStartRotate(motor mot, int dist, int vel, int timing){
  mot.startRotateFor(forward, dist, rotationUnits::deg, vel, velocityUnits::pct);
  task::sleep(timing);
}