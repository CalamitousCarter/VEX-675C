#include "vex.h"

using namespace vex;

bool liftManual = true;
bool mogoGround = false;
bool driveLock = true;

int clawStartRot = 0;
int clawEndRot = -1050;

int gripVel = 100;
int liftVel = 100;
int clawVel = 100;
int n = 2;

float turnPow = 0.5f;

void pre_auton(void) {
  vexcodeInit();

}

void autonomous(void) {
  topAuton();
}

int driveCurve(int inputVal){
  int driveVal = (int) round(pow(inputVal, n) / pow(100, n-1));
  driveVal *= (inputVal >= 0) ? 1 : -1;

  return driveVal;
}

int userDrive(){
  int chi = user.Axis4.value() * turnPow;
  int zed = user.Axis3.value();

  FL.spin(reverse, driveCurve(chi + zed), percent);
  BL.spin(forward, driveCurve(chi + zed), percent);
  FR.spin(reverse, driveCurve(chi - zed), percent);
  BR.spin(forward, driveCurve(chi - zed), percent);

  if(liftManual)
    (user.ButtonR1.pressing()) ? liftGroup.spin(forward, liftVel, pct) : 
    (user.ButtonR2.pressing()) ? liftGroup.spin(reverse, liftVel, pct) : liftGroup.stop(hold);

  (user.ButtonL1.pressing()) ? grip.spin(forward, gripVel, pct) : 
  (user.ButtonL2.pressing() && grip.rotation(degrees) > 5) ? grip.spin(reverse, gripVel, pct) : grip.stop(hold);

  return 1;
}

int clawMacro() {
  if(!mogoGround){
    claw.rotateTo(clawEndRot, degrees, clawVel, velocityUnits::pct);
    mogoGround = true;
  }
  else if (mogoGround){
    claw.rotateTo(clawStartRot, degrees, clawVel, velocityUnits::pct);
    mogoGround = false;
  }
  return 1;
}

int liftMacro() {
  liftManual = false;
  while (liftGroup.rotation(degrees) > 0) {
    liftGroup.spin(reverse, liftVel, percent);
    task::sleep(20);
  }
  liftManual = true;
  return 1;
}

int swicthDriveLock(){
  if(!driveLock){
    driveLock = true;
    user.rumble("- -");
    FL.setBrake(coast);
    FR.setBrake(coast);
    BL.setBrake(coast);
    BR.setBrake(coast);
  }
  else if (driveLock) {
    driveLock = false;
    user.rumble(". . .");
    driveBase.setStopping(hold);
  }
  return 1;
}

void startClawMacro(){
  task claw (clawMacro);
}

void startLiftMacro(){
  task lift (liftMacro);
  user.rumble("-");
}

void startLockMacro(){
  task lock (swicthDriveLock);
}

void usercontrol(void) {
  while (1) {
    enableDrivePID = false;
    userDrive();

    user.ButtonUp.pressed(startLockMacro);
    user.ButtonX.pressed(startClawMacro);
    user.ButtonA.pressed(startLiftMacro);

    task::sleep(20);
    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
