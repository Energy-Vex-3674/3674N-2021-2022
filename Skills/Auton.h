#include "STUFF!.h"
using namespace vex;
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // not using Gps at all times because of moving in reverse or other
  // piston test
  PGrab.open();
  wait(1, sec);
  PGrab.close();
  wait(1, sec);
  PGrab.close();
  wait(10,sec);
  PGrab.open();
  Drivetrain.setDriveVelocity(100, pct);
  Drivetrain.setTurnVelocity(100,pct);
  wait(1,sec);
  PistonGrab();
  Lift.stop(hold);
  Drivetrain.driveFor(reverse, 100, mm);
  PistonGrab();
  PistonTilt();
  Drivetrain.drive(reverse);
  waitUntil(GSP.yPosition() == 0.9);
  Drivetrain.stop();
  go(0.875,1.475);
  grabby1();
  lifty();
  conveyor.spin(reverse,100,pct);
  go(-1.15,0);
  lifty();
  Stack();
  Drivetrain.driveFor(reverse,50,mm);
  Pistonliftup();
  Drivetrain.turnFor(180,degrees);
  Drivetrain.driveFor(reverse,50,mm);
  PistonStack();
  lifty2();
  Pistonliftdown();
  Drivetrain.turnToHeading(0,degrees);
  Drivetrain.driveFor(forward,1050,mm);
  Drivetrain.turnToHeading(90,degrees);
  Drivetrain.driveFor(reverse,150,mm);
  PistonGrab();
  PistonTilt();
  go(0.05,900);
  grabby1();
  lifty();
  conveyor.spin(reverse,100,pct);
  go(0,1.18);
  lifty();
  Stack();
  Drivetrain.driveFor(reverse, 50, mm);
  Pistonliftup();
  lifty2();
  Drivetrain.turnToHeading(270,degrees);
  Drivetrain.driveFor(reverse,50,mm);
  PistonStack();

  // ..........................................................................
}