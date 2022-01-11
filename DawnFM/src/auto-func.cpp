#include "vex.h"
using namespace vex;


void startDriveFwd(double distance, double velocity)
{
  FL.startRotateFor(reverse, distance, rotationUnits::deg, velocity, velocityUnits::pct);
  FR.startRotateFor(forward, distance, rotationUnits::deg, velocity, velocityUnits::pct);
  BL.startRotateFor(reverse, distance, rotationUnits::deg, velocity, velocityUnits::pct);
  BR.rotateFor(forward, distance, rotationUnits::deg, velocity, velocityUnits::pct);
}

void startDriveTurn(double distance, double velocity)
{
  FL.startRotateFor(directionType::rev, distance, rotationUnits::deg, velocity, velocityUnits::pct);
  FR.startRotateFor(directionType::rev, distance, rotationUnits::deg, velocity, velocityUnits::pct);
  BL.startRotateFor(directionType::rev, distance, rotationUnits::deg, velocity, velocityUnits::pct);
  BR.rotateFor(directionType::rev, distance, rotationUnits::deg, velocity, velocityUnits::pct);
}

void gripRotate(int direction, int distance, int velocity)
{
  grip.rotateFor(directionType::fwd, direction*distance, rotationUnits::deg, velocity, velocityUnits::pct);
}

void gripStartRotate(int direction, int distance, int velocity)
{
  grip.startRotateFor(directionType::fwd, direction*distance, rotationUnits::deg, velocity, velocityUnits::pct);
}

void clawStartRotate(int direction, int distance, int velocity)
{
  claw.startRotateFor(directionType::fwd, direction*distance, rotationUnits::deg, velocity, velocityUnits::pct);
}