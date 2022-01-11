#include "vex.h"
using namespace vex;

void topAuton(void) {
  task StartDrivePID(drivePID);
  enableDrivePID = true;

  resetDriveSensors = true;
  desiredDriveVal = 907;
  task::sleep(1050);

  gripStartRotate(1, 420, 100);
  task::sleep(600);

  resetDriveSensors = true;
  maxPow = 12;
  desiredDriveVal = -680;
  task::sleep(500);

  gripStartRotate(1, -380, 100);
  task::sleep(600);

  resetDriveSensors = true;
  maxPow = 11.9f;
  desiredDriveVal = -175;
  task::sleep(500); 

  resetDriveSensors = true;
  maxPow = 11.9f;
  desiredDriveVal = 0;
  desiredTurnVal = 105;
  task::sleep(600); 

  resetDriveSensors = true;
  maxPow = 11.9f;
  desiredTurnVal = 0;
  desiredDriveVal = 1050;
  task::sleep(1000); 

  gripStartRotate(1, 420, 100);
  task::sleep(600);

  resetDriveSensors = true;
  maxPow = 11.9f;
  desiredDriveVal = -600;
  task::sleep(1000);

  gripStartRotate(1, -400, 100);
  task::sleep(750);

  resetDriveSensors = true;
  maxPow = 11.9f;
  desiredDriveVal = -100;
  task::sleep(1000);

  resetDriveSensors = true;
  maxPow = 11.9f;
  desiredDriveVal = 0;
  desiredTurnVal = 160;
  task::sleep(600); 

  clawStartRotate(1, -1050, 100);
  task::sleep(1000);

  resetDriveSensors = true;
  maxPow = 11.9f;
  desiredTurnVal = 0;
  desiredDriveVal = -575;
  task::sleep(1000); 

  clawStartRotate(1, 1000, 100);
  task::sleep(1000);

  /*resetDriveSensors = true;
  maxPow = 11.9f;
  desiredDriveVal = 0;
  desiredTurnVal = -575;
  task::sleep(1000); 

  resetDriveSensors = true;
  maxPow = 11.9f;
  desiredTurnVal = 0;
  desiredDriveVal = 270;
  task::sleep(800); 

  gripStartRotate(1, 420, 100);
  task::sleep(600);*/

}