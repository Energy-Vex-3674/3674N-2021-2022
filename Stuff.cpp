/////////////////////////
// includes everything
#ifndef VEX_H
#define VEH_H
#include "vex.h"
#endif

#ifndef STUFF_H
#define STUFF_H
#include "Stuff.h"
#endif

#ifndef PROTO_MOTOR_BALANCE_H
#define PROTO_MOTOR_BALANCE_H
#include "Proto_Motor_Balance.h"
#endif
////////////////////////////////////


// File includes lots of functions for actions in all parts of the code.
// there is PID in the lift


//lift variable
int lift = 0;
// direction bool
bool Fwrd = true;
// tracks whether speed is on
bool sped = false;
// maual bool
bool manual = false;
// claw booleans
bool Law1 = true;
bool Law2 = false;
// tilt booleans
bool Tilt = false;

// grab front
void Grab1(){
  if(Law1 == false){
    Claw1.open();  
    Law1 = true;  
  }
  else{
    Claw1.close();
    Law1 = false;
  }
}
// Grab back
void Grab2(){
  if(Law2 == false){
    Claw2.open();  
    Law2 = true;  
  }
  else{
    Claw2.close();
    Law2 = false;
  }
}

// single tilt
void PistonTilt(){
  if(Tilt == false){
    Ptilt.open();  
    Tilt = true;  
  }
  else{
    Ptilt.close();
    Tilt = false;
  }
}

// lift up functions 1-2
// variables for Lift PID
const double LiftKp = 0.5;
// amost pointless value
const double LiftKd = 10000000000;
const double LiftKi = 0;
int Lift_error = 0;
int Lift_prev_error = 0;
int Lift_total_error = 0;
int Lift_derivative = 0;
int Lift_desired = 0;
int LiftMotor = 0;
void lifty(){
  if(lift==0){
    // sets variables to 0
    Lift_error = 0;
    Lift_prev_error = 0;
    Lift_total_error = 0;
    Lift_derivative = 0;
    Lift_desired = 0;
    LiftMotor = 0;
    Lift.resetPosition();
    while(rotor.position(degrees)>103){
      LiftMotor = rotor.position(degrees);
      // cahnge value to subtract
      // add deepthroat pans to controller screen
      Lift_desired =( rotor.position(degrees) - 103);
      Lift_error = LiftMotor - Lift_desired;
      Lift_derivative = Lift_error- Lift_prev_error;
      Lift_total_error += Lift_error;
      int Motor_power = (Lift_error * LiftKp + Lift_derivative * LiftKd + Lift_total_error * LiftKi)/100;
      // sets velocity and spins
      if(Motor_power>80){
        Motor_power = 80;
      } 
      Lift.spin(forward,Motor_power,pct);
    }
      // waits until sensor reads less than value and stops
      Lift.stop(hold);
      Lift.setVelocity(0,percent);
      // sets lift to 1 so lift goes up
      lift = 1;
  }
  else {
    // sets velocity and spins
    while(rotor.position(degrees)>41){
      LiftMotor = rotor.position(degrees);
      // cahnge value to subtract
      // add deepthroat pans to controller screen
      Lift_desired = (rotor.position(degrees) - 41);
      Lift_error = LiftMotor - Lift_desired;
      Lift_derivative = Lift_error- Lift_prev_error;
      Lift_total_error += Lift_error;
      int Motor_power = (Lift_error * LiftKp + Lift_derivative * LiftKd)/100;
      if(Motor_power>80){
        Motor_power = 80;
      } 
      // sets velocity and spins
      Lift.spin(forward,Motor_power,pct);
    }
      // waits until sensor reads less than value and stops
      Lift.stop(hold);
      Lift.setVelocity(0,percent);
      // sets lift to 1 so lift goes up
      lift = 2;
  }
}
// lift down function
void lifty2(){
  // sets velocity and spins
  Lift.spin(reverse,70,pct);
  // waits until sensor is less than 1
  waitUntil(rotor.position(turns)>0.33);
  Lift.stop(hold);
  Lift.setVelocity(0,percent);
  lift = 0;
}
void Stack(){
  // stacks goals on ramp
  // sets velocity and spins
  Lift.spin(reverse,80,pct);
  // waits until sensor is less than value
  waitUntil(rotor.position(turns)>0.14);
  Lift.stop(hold);
  Grab1();
  wait(50, msec);
  // drives back and lift down
  Left1.setVelocity(40, pct);
  Left1.spinFor(reverse,100, degrees,false);
  Left2.setVelocity(40, pct);
  Left2.spinFor(reverse,100, degrees,false);
  Left3.setVelocity(40, pct);
  Left3.spinFor(reverse,100, degrees,false);
  Right1.setVelocity(40, pct);
  Right1.spinFor(reverse,100, degrees,false);
  Right2.setVelocity(40, pct);
  Right2.spinFor(reverse,100, degrees,false);
  Right3.setVelocity(40, pct);
  Right3.spinFor(reverse,100, degrees,false);
  lifty();
}
/////////////////////////


// functions for changing mode on the controls of the robot is the rest of the file

///////////////////////
void spedy(){
 if(sped==false){
   sped = true;
   Brain.Screen.print("sped is on");
   Controller.Screen.print("slow ");
   wait(20,msec);
 } 
 else{
   sped = false;
   Brain.Screen.print("sped is off");
   Controller.Screen.print("fast ");
   wait(20,msec);
 }
}
// turns on manual
void manualdo(){
  if(manual == true){
    manual = false;
    Brain.Screen.print("manual off");
    Controller.Screen.print("non-manual ");
    wait(20,msec);
  }
  else{
    manual = true;
    Brain.Screen.print("manual on");
    Controller.Screen.print("manual ");
    wait(20,msec);
  }
}
void ChangeDR(){
  if(Fwrd == true){
    Fwrd = false;
    Brain.Screen.print("direction changed");
    Controller.Screen.print("Reversed ");
    wait(20,msec);
  }
  else{
    Fwrd = true;
    Brain.Screen.print("direction changed back");
    Controller.Screen.print("forward ");
    wait(20,msec);
  }
}
// changes which grab triggers based on direction
void Greab(){
  if(Fwrd == false){
    Grab2();
  }
  else{
    Grab1();
  }
}