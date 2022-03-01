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
  Drivetrain.setDriveVelocity(50, pct);
  Drivetrain.setTurnVelocity(50,pct);
  //Drivetrain.turnToHeading(90, degrees);
  go(0,0);

  wait(10,sec);
  Lift.stop(hold);
  nertial.calibrate();
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.setTurnVelocity(30, percent);
  Drivetrain.driveFor(forward, 745, mm,false);
  grabby1();
  wait(0.1,sec);
  Drivetrain.setDriveVelocity(70, percent);
  Drivetrain.driveFor(forward, 625, mm,false);
  wait(0.65,sec);
  grabby1();
  Drivetrain.driveFor(reverse, 1300, mm,false);
  lifty();
  waitUntil(Drivetrain.isDone());
  //possibly until inertail reads a certain value
  Drivetrain.turnFor(left, 96, degrees);
  Drivetrain.driveFor(forward, 100,mm);
  PistonGrab();
  Drivetrain.driveFor(reverse,500,mm);
  PistonGrab();
  conveyor.spin(forward,100,pct);
  wait(3,sec);
  conveyor.stop(hold);
  claw.stop(hold);
  // ..........................................................................
}