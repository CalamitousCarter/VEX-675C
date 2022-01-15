
#include "vex.h"
#include "math.h"

using namespace vex;

motor mogoArr[] = {tail, clamp, liftA, liftB};
motor driveArr[] = {headL, rearL, headR, rearR};

bool revDrive = false; // Drive Forward Direction
bool lockDrive = false; // Set Drive Lock Type
bool upPressed = false;
bool rightPressed = false;

int upVal = 0;
int rightVal = 0;
int n = 2; // Drive Exponent

float turnConst = 0.5f;

void autonDrive(int rotation){
  headL.rotateFor(forward,rotation, degrees, false);
  rearL.rotateFor(reverse,rotation, degrees, false);
  headR.rotateFor(reverse,rotation, degrees, false);
  rearR.rotateFor(forward,rotation, degrees);
}

void autoTurn(int rotation){
  headL.rotateFor(reverse,rotation, degrees, false);
  rearL.rotateFor(forward,rotation, degrees, false);
  headR.rotateFor(reverse,rotation, degrees, false);
  rearR.rotateFor(forward,rotation, degrees);
}

void autonTail(int deg){
  tail.rotateFor(deg, degrees, false);
}

void autonClamp(int deg){
  clamp.rotateFor(deg, degrees, false);
}

void pre_auton(void) {
  vexcodeInit();
  tail.setVelocity(100, velocityUnits::pct);
  for(motor x : driveArr)
    x.setVelocity(100, velocityUnits::pct);
}

void autonomous(void) {
  autonTail(-1200);
  autonDrive(1100);
  autonTail(800);
  wait(750, msec);
  autonDrive(-900);
  autoTurn(350);
}

void drivePow(motor driveM, int axisVal){
  int driveVelocity = (int) round(((pow(axisVal, n)) / (pow(100, n-1))));
  driveVelocity *= ((axisVal >= 0) ? 1 : -1);

  driveM.spin(fwd, driveVelocity, vex::velocityUnits::pct);
}

void reverseControl(){
  if(!upPressed){
    revDrive = !revDrive;
    user.rumble((!revDrive) ? "  . . . . " : " --     -- ");
      for(motor m : driveArr)
      m.setBrake((!revDrive) ? vex::brakeType::coast : vex::brakeType::hold);
    upPressed = true;
  }
  //Brain.Screen.clearLine(); Brain.Screen.print((!revDrive) ? "normal" : "reversed");
}

void lockMotors(){
  if(!rightPressed){
    lockDrive = !lockDrive;
    for(motor m : driveArr)
      m.setBrake((!lockDrive) ? vex::brakeType::coast : vex::brakeType::hold);
    user.rumble((!lockDrive) ? "- . -" : ". . - . .");
    rightPressed = true;
  }
}

void renewRev(){
  upPressed = false;
}

void renewLock(){
  rightPressed = false;
}

void stickDrive(){
  int chi = user.Axis3.value(); // Forward & Backward
  int zed = user.Axis4.value(); // Left & Right
  int dir = ((!revDrive) ? 1 : -1); 

  drivePow(headL, dir * (-chi - (zed * turnConst)));
  drivePow(rearL, dir * ( chi + (zed * turnConst)));
  drivePow(headR, dir * ( chi - (zed * turnConst)));
  drivePow(rearR, dir * (-chi + (zed * turnConst)));


  if(user.ButtonUp.pressing()){
    headL.setBrake(hold);
    headR.setBrake(hold);
    rearL.setBrake(hold);
    rearR.setBrake(hold);
  }
  else if(user.ButtonDown.pressing()) {
    headL.setBrake(coast);
    headR.setBrake(coast);
    rearL.setBrake(coast);
    rearR.setBrake(coast);
  }
  //user.ButtonUp.pressed(reverseControl); 
  //user.ButtonUp.released(renewRev);

  //user.ButtonRight.pressed(lockMotors);
  //user.ButtonRight.released(renewLock);

}

void mogoLift(){
  for(motor x : mogoArr)
    x.setStopping(vex::brakeType::hold);

  if(user.ButtonR1.pressing()){
    liftA.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    liftB.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  }
  else if(user.ButtonR2.pressing()){
    liftA.spin(vex::directionType::rev, -100, vex::velocityUnits::pct);
    liftB.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
  }
  else{
    liftA.stop();
    liftB.stop();
  }
}

void mogoTail(){
  tail.setStopping(vex::brakeType::hold);

  if(user.ButtonL1.pressing())
    tail.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  else if(user.ButtonL2.pressing())
    tail.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
  else
    tail.stop();
}

void clampMech(){
  clamp.setStopping(vex::brakeType::hold);
  
  if(user.ButtonA.pressing() && clamp.rotation(rotationUnits::deg) < 0 )
    clamp.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  else if(user.ButtonX.pressing() && clamp.rotation(rotationUnits::deg) > -800.0)
    clamp.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
  else
    clamp.stop();

  if(user.ButtonY.pressing()){
    double rot = clamp.rotation(rotationUnits::deg);
    Brain.Screen.clearLine();
    Brain.Screen.print(rot);
  }
}

void usercontrol(void) {
  while (1) {
    stickDrive();
    mogoLift();
    clampMech();
    mogoTail();

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