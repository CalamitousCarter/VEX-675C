#include "vex.h"
using namespace vex;

/* ***************************************************************** 
  SKILLS AUTON () - Collect left blue, grab left yellow, plat yellow, plat blue, grab left red, 
  drag middle yellow, drag left yellow, grab right red, plat robot

  RIGHT AUTON (40) - Grab right neutral mogo, grab center neutral mogo, collect alliance mogo
  LEFT AUTON (40) - Grab left neutral mogo, grab center neutral mogo, collect alliance mogo

  235 - 90 deg turn, 120 - 45 deg turn
***************************************************************** */

void rightAuton(void) {
  task StartDrivePID(drivePID);
  enableDrivePID = true;
  liftGroup.rotateFor(forward, -15, degrees, false);

  // Right Neutral
  driveFwd(860, 1100);
  motorStartRotate(grip, 400, 100, 600);
  liftGroup.rotateFor(forward, 30, degrees, false);
  constUpdate(0.93, 0.97);
  driveFwd(-525, 1500);
  motorStartRotate(grip, -325, 100, 600);
  driveFwd(-200, 750);
  liftGroup.rotateFor(forward, -45, degrees, false);

  // Middle Neutral
  driveTurn(120, 600);
  driveFwd(1050,1000);
  motorStartRotate(grip, 400, 100, 600);
  liftGroup.rotateFor(forward, 30, degrees, false);
  driveFwd(-600, 1000);

  /*

  driveFwd(-600, 12, 1000);
  motorStartRotate(grip, -400, 100, 750);

  driveFwd(-200, 12, 1000);
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

  resetDriveSensors = true;
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

void skillsAuton(void){
  task StartDrivePID(drivePID);
  enableDrivePID = true;

  // Tilt Left Blue
  constUpdate(0.73, 0.78);
  driveFwd(0, 100);
  motorRotate(claw, -1000, 100, 100);
  driveFwd(-500, 1000);
  motorRotate(claw, 1000, 100, 100);

  // Reposition 
  driveFwd(600, 1000);
  driveFwd(-300, 1000);
  driveTurn(-235, 1000);

  // Grab Left Yellow
  liftGroup.rotateFor(forward, -15, degrees, false);
  driveFwd(860, 1100);
  motorStartRotate(grip, 400, 100, 600);
  liftGroup.rotateFor(forward, 30, degrees, false);
  constUpdate(0.73, 0.77);
  driveFwd(-800, 1500);

}