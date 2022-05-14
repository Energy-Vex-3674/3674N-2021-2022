#ifndef VEX_H
#define VEX_H
#include "vex.h"
#endif

#ifndef STUFF_H
#define STUFF_H
#include "Stuff.h"
#endif

// GPS and movement to use PID
// Figure out from fifteeninch
// add GPS and fix when ready Auton is easy.

//////////////////////////
// Lateral PID is below
/////////////////////////
// error tracking for data
double true_turn_error = 0;
double true_lat_error = 0;
////////////////////
// enabled variable
bool PidEnabled = true;
void Pidisabler(bool disabled){
  if(disabled){
    PidEnabled = true;
  }
  else{
    PidEnabled = false;
  }
}
// variables for Lat PID
double LatKp = 0;
double LatKd = 0;
double LatKi = 0;
int Lat_error = 0;
int Lat_prev_error = 0;
int Lat_total_error = 0;
int Lat_derivative = 0;
// mm/circumference * 360 
int Lat_desired = 0;
int PidLat(int Desired){
  Lat_error = 0;
  Lat_prev_error = 0;
  true_lat_error += Lat_total_error;
  Lat_total_error = 0;
  Lat_derivative = 0;
  Left1.resetPosition();
  Right1.resetPosition();
  // make if enabled and another variable for while
  while(PidEnabled){
    double circConst = 318;
    double degreesy = Desired/circConst*360;
    int LeftMotor = Left1.position(degrees);
    int RightMotor = Right1.position(degrees);
    int PidAverage = (LeftMotor + RightMotor)/2;
    int Lat_desired = degreesy;
    Lat_error = PidAverage - Lat_desired;
    Lat_derivative = Lat_error- Lat_prev_error;
    Lat_total_error += Lat_error;
    int Motor_power = (Lat_error * LatKp + Lat_derivative * LatKd + Lat_total_error * LatKi)/100;
    Lat_prev_error = Lat_error;
    Left1.spin(forward, Motor_power, pct);
    Left2.spin(forward, Motor_power, pct);
    Left3.spin(forward, Motor_power, pct);
    Right1.spin(forward, Motor_power, pct);
    Right2.spin(forward, Motor_power, pct);
    Right3.spin(forward, Motor_power, pct);
    // could add an if that stops pid if everything is stopped
  }
  task::sleep(20);
  return 1;
}

///////////////////////////////////
// variables for turning PID
bool Lat_Done = false;
double TurnKp = 0;
double TurnKd = 0;
double TurnKi = 0;
int Turn_error = 0;
int Turn_prev_error = 0;
int Turn_total_error = 0;
int Turn_derivative = 0;
int PidTurn(int turnAmount){
  Turn_error = 0;
  Turn_prev_error = 0;
  true_turn_error += Turn_total_error;
  Turn_total_error = 0;
  Turn_derivative = 0;
  Left1.resetPosition();
  Right1.resetPosition();
  if(PidEnabled){
    while(!Lat_Done){
      Turn_error = turnAmount - nertial.rotation(degrees);
      Turn_derivative = Turn_error- Lat_prev_error;
      Turn_total_error += Turn_error;
      int Motor_power = (Turn_error * TurnKp + Turn_derivative * TurnKd + Turn_total_error * TurnKi)/100;
      Turn_prev_error = Turn_error;
      Left1.spin(forward, Motor_power ,pct);
      Left2.spin(forward, Motor_power , pct);
      Left3.spin(forward, Motor_power , pct);
      Right1.spin(forward, Motor_power , pct);
      Right2.spin(forward, Motor_power , pct);
      Right3.spin(forward, Motor_power , pct);
      if(Left1.velocity(pct) == 0 && Left2.velocity(pct) == 0 && Left3.velocity(pct) == 0 && Right1.velocity(pct) == 0 && Right2.velocity(pct) == 0 && Right3.velocity(pct) == 0){
        Lat_Done = true;
      }
      task::sleep(20);
    }
  }
  return 1;
}










