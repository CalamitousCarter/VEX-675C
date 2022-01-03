#include "vex.h"

using namespace vex;

int n = 2;
int mogoVel = 100;

float turnConst = 0.5f;

bool driveLock = false;
bool mogoFloor = false;
bool autoLift = false;


void pre_auton(void) {
  vexcodeInit();
  driveBase.setStopping(coast);
  mogoGroup.setStopping(hold);
  mogoGroup.setVelocity(mogoVel, percent);
}

void autonomous(void) {

}

void drivePow(motor driveM, int axisVal){
  int driveVelocity = (int) round(((pow(axisVal, n)) / (pow(100, n-1))));
  driveVelocity *= ((axisVal >= 0) ? 1 : -1);

  driveM.spin(fwd, driveVelocity, vex::velocityUnits::pct);
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
  if(user.ButtonR1.pressing()){
    barA.spin(forward, 90, percent);
    barB.spin(reverse, 90, percent);
  }
  else if(user.ButtonR2.pressing()){
    barA.spin(forward, -90, percent);
    barB.spin(reverse, -90, percent);
  }
  else{
    barA.stop(hold);
    barB.stop(hold);
  }
}

void mogoCarry(){
  if(user.ButtonX.pressing())
    carry.spin(forward, 100, percent);
  else if(user.ButtonA.pressing())
    carry.spin(reverse, -100, percent);
  else
    carry.stop(hold);
}

void usercontrol(void) {
  while (1) {

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
