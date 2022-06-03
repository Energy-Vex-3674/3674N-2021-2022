/////////////////////////////////////////
// includes header files needed
#ifndef VEX_H
#define VEH_H
#include "vex.h"
#endif


#ifndef AUTON_H_INCLUDED
#define AUTON_H_INCLUDED
#include "Auton.h"
#endif

#ifndef PID_H
#define PID_H
#include "PID.h"
#endif

#ifndef PROTO_MOTOR_BALANCE_H
#define PROTO_MOTOR_BALANCE_H
#include "Proto_Motor_Balance.h"
#endif
/////////////////////////////////////////////

// allows for moving forward and reverse for a specific number of inches
int choice = 0;

// sets up an autonomus selection process
// Untested!!!
void autonomous(void){
  if(choice == 0){
    Lift.stop(hold);
    nertial.calibrate();
    // switch to reverse to get middle with Front.
    //29.3307 inches + 23.8189
    PidLat(1350);
    // good
    Grab1();
    // forward less
    PidLat(1230);
    //48.4252 inches
    // Piston lift instead
    lifty();
    waitUntil(Left1.isDone());
    waitUntil(Right1.isDone());
    // Turn different to go or middle 
    // USe GPS?
    PidTurn(-94);
    //94 degrees left
    // good but increase
    lifty2();
    PidLat(130);
    //5.11811 inches
    //grabby
    Grab2();
    PidLat(450);
    //17.7165
    //good
    Grab2();
    // 
    conveyor.spin(reverse,100,pct);
    wait(3,sec);
    conveyor.stop(hold);
  }
  if(choice == 1){
  //auton 2  
  }
}