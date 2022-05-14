/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\17138                                            */
/*    Created:      Wed Apr 13 2022                                           */
/*    Description:  V5 project, by: Kyle Spiller
*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
// These are all of the header inclusions in the main file
// Each one is a protected inclusion
#ifndef VEX_H
#define VEX_H
#include "vex.h"
#endif

#ifndef DRIVER_H
#define DRIVER_H
#include "Driver.h"
#endif

#ifndef AUTON_H
#define AUTON_H
#include "Auton.h"
#endif

#ifndef PROTO_MOTOR_BALANCE_H
#define PROTO_MOTOR_BALANCE_H
#include "Proto_Motor_Balance.h"
#endif
////////////////////////////////////////////////////////
// pre autonomous function is triggered at the beggining of main before autonomous activates.
void pre_auton(){
}
// starts using the namespace
using namespace vex;
// creates the competion class Competition
competition Competition; 
// sets bool up for Autonomous choosing
bool chosen = false;
// main function
int main() {
  // Initializing Robot Configuration.
  vexcodeInit();
  pre_auton();
  // Autonomous choosing process
  // Untested!
  // while loop keeps it going until one is chosen
  while(chosen == false){
    if(Controller.ButtonA.pressing()) {
      choice = 0;
      chosen = true;
    }
    if(Controller.ButtonB.pressing()) {
      choice = 1;
      chosen = true;
    }
    if(Controller.ButtonX.pressing()) {
      choice = 2;
      chosen = true;
    }
    if(Controller.ButtonY.pressing()) {
      choice = 3;
      chosen = true;
    }
    else {
      choice = 0;
      chosen = true;
    }
    // sleeps task 
    task::sleep(20);
  }
  // triggers driveControl period
  Competition.drivercontrol(usercontrol);
  // triggers auton period
  Competition.autonomous(autonomous);
}
