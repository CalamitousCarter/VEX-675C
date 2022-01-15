#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

competition Competition;

controller user = vex::controller();

// MOGO LIFTS
motor clamp = vex::motor(PORT8, false);   // 100 rpm
motor liftA = vex::motor(PORT1, false);   // 100 rpm
motor liftB = vex::motor(PORT11, false);   // 100 rpm
motor tail = vex::motor(PORT2, false);    // 100 rpm

// DRIVE TRAIN
motor headL = vex::motor(PORT10, false);  // 200 rpm
motor headR = vex::motor(PORT9, false);  // 200 rpm
motor rearL = vex::motor(PORT5, true);   // 200 rpm
motor rearR = vex::motor(PORT18, true);   // 200 rpm

void vexcodeInit(void) {
  // Nothing to initialize
}