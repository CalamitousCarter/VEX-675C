#include "vex.h"

using namespace vex;

competition Competition;

controller cont = vex::controller();

// --- MOGO Lift Motors ---
motor angler = vex::motor(vex::PORT1, false);
motor hook =  vex::motor(vex::PORT15, false);
motor lift1 = vex::motor(vex::PORT2, false);
motor lift2 = vex::motor(vex::PORT16, true);

motor mogoArr[] = {angler, hook, lift1, lift2};

// --- Ring Conveyor Motors ---
motor slider = vex::motor(vex::PORT4, false);

// --- Gear Drive Motors ---
motor driveL1 = vex::motor(vex::PORT11, true);
motor driveL2 = vex::motor(vex::PORT12, false);
motor driveR1 = vex::motor(vex::PORT1, true);
motor driveR2 = vex::motor(vex::PORT5, false);

motor driveArr[] = {driveL1, driveL2, driveR1, driveR2};

//Variables
bool switchDrive = true;
int liftVel = 50;
int hookVel = 50;
int anglerVel = 50;

// Functions
void singleStick(){
  driveL1.spin(vex::directionType::fwd, cont.Axis4.value() + cont.Axis3.value(), vex::velocityUnits::pct);
  driveL2.spin(vex::directionType::rev, cont.Axis4.value() + cont.Axis3.value(), vex::velocityUnits::pct);
  driveR1.spin(vex::directionType::fwd, cont.Axis4.value() - cont.Axis3.value(), vex::velocityUnits::pct);
  driveR2.spin(vex::directionType::rev, cont.Axis4.value() - cont.Axis3.value(), vex::velocityUnits::pct);
}

void mogoLift(){
        for(motor x : mogoArr)
    x.setStopping(vex::brakeType::hold);

  // --- 4-Bar Lift ---
  if(cont.ButtonR2.pressing()){
    lift1.spin(vex::directionType::fwd, liftVel, vex::velocityUnits::pct);
    lift2.spin(vex::directionType::fwd, liftVel, vex::velocityUnits::pct);
  }
  else if(cont.ButtonL2.pressing()){
    lift1.spin(vex::directionType::fwd, -liftVel, vex::velocityUnits::pct);
    lift2.spin(vex::directionType::fwd, -liftVel, vex::velocityUnits::pct);
  }
  else{
        lift1.stop();
        lift2.stop();
  }

  // --- Hook Mechanism --- 
  if(cont.ButtonR1.pressing())
    hook.spin(vex::directionType::fwd, hookVel, vex::velocityUnits::pct);
  else if(cont.ButtonL1.pressing())
    hook.spin(vex::directionType::fwd, -hookVel, vex::velocityUnits::pct);
  else
    hook.stop();
}

void moveDrive(int waitTime){
  driveL1.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  driveL2.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  driveR1.spin(vex::directionType::fwd, -50, vex::velocityUnits::pct);
  driveR2.spin(vex::directionType::rev, -50, vex::velocityUnits::pct);
  wait(waitTime, msec);
  for(motor x: driveArr)
    x.stop();
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  for(motor x : mogoArr)
    x.setStopping(vex::brakeType::hold);
  for(motor x : driveArr)
    x.setStopping(vex::brakeType::coast);
  for(motor x : driveArr){
    x.setVelocity(50,vex::velocityUnits::pct);
  }
}

void autonomous(void) {
  moveDrive(2000);
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    singleStick();
    mogoLift();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
