#include "vex.h" //get VEX ROBOTICS COMMANDS
#include "math.h" //get math methods

using namespace vex;

motor driveBase[] = {FL, FR, BL, BR};
motor mogoLifts[] = {barA, barB, grip, carry};

int n = 2;

float turnConst = 0.5f;

void setLockType(bool pickMotors, brakeType brake){
  if(pickMotors)
      for(motor dev : driveBase)
        dev.setStopping(brake);
  else if (!pickMotors)
      for(motor dev : mogoLifts)
        dev.setStopping(brake);
}

void setAllSpeed(bool pickMotors, int speed){
    if(pickMotors)
      for(motor dev : driveBase)
        dev.setVelocity(speed, percent);
  else if (!pickMotors)
      for(motor dev : mogoLifts)
        dev.setVelocity(speed, percent);
}

void autonAction(motor mogo, bool useDrive, bool useTurn, int rotDegrees){
  if(useDrive && !useTurn){
    for(int i = 0; i < 4; i++){
      driveBase[i].rotateFor((i % 3 == 0) ? forward : reverse, rotDegrees, degrees, (i - 3 == 0) ? true : false);
    }
  }
  else if (!useDrive && useTurn){
    for(int i = 0; i < 4; i++){
      driveBase[i].rotateFor((i > 2) ? forward : reverse, rotDegrees, degrees, (i - 3 == 0) ? true : false);
    }
  }
  else if(!useDrive && !useTurn){
    mogo.rotateFor(rotDegrees, degrees, false);
  }
}

void autonDrive(int rotation){
  FL.rotateFor(forward,rotation, degrees, false);
  BL.rotateFor(reverse,rotation, degrees, false);
  FR.rotateFor(reverse,rotation, degrees, false);
  BR.rotateFor(forward,rotation, degrees);
}

void pre_auton(void) {
  vexcodeInit();
  setLockType(true, hold);
  setLockType(false, hold);
  setAllSpeed(true, 100);
  setAllSpeed(false, 100);
  carry.setVelocity(100, percent);
  FL.setVelocity(75, percent);
  BL.setVelocity(75, percent);
  FR.setVelocity(75, percent);
  BR.setVelocity(75, percent);
}

void autonomous(void) {
  autonAction(carry, false, false, -950);
  autonDrive(1000);
  autonAction(carry, false, false, 850);
  wait(1000, msec);
  autonDrive(-1000);
}

int drivePow(motor driveM, int axisVal){
  int driveVelocity = (int) round(((pow(axisVal, n)) / (pow(100, n-1))));
  driveVelocity *= ((axisVal >= 0) ? 1 : -1);

  driveM.spin(fwd, driveVelocity, vex::velocityUnits::pct);
  return 1;
}

void stickDrive(){
  int chi = user.Axis3.value();
  int zed = user.Axis4.value();

  drivePow(FL, (-chi - (zed * turnConst)));
  drivePow(BL, ( chi + (zed * turnConst)));
  drivePow(FR, ( chi - (zed * turnConst)));
  drivePow(BR, (-chi + (zed * turnConst)));
}

void mogoLift(){
  setLockType(false, hold);

  if(user.ButtonR1.pressing()){
    barA.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    barB.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  }
  else if(user.ButtonR2.pressing()){
    barA.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    barB.spin(vex::directionType::rev, -100, vex::velocityUnits::pct);
  }
  else{
    barA.stop(hold);
    barB.stop(hold);
  }
}

void mogoCarry(){
  setLockType(false, hold);

  if(user.ButtonL1.pressing())
    carry.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  else if(user.ButtonL2.pressing())
    carry.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
  else
    carry.stop(hold);
}

void gripMech(){
  setLockType(false, hold);
  
  if(user.ButtonX.pressing())
    grip.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
  else if(user.ButtonA.pressing())
    grip.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  else{
    grip.stop(hold);
  }
}

void usercontrol(void) {
  setLockType(true, coast);
  while (1) {
    stickDrive();
    mogoLift();
    gripMech();
    mogoCarry();
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
