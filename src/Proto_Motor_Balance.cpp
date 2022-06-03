// includes everything needed
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

using namespace vex;
// a count for every motor individually
int Lefy1 = 0;
int Lefy2 = 0;
int Lefy3 = 0;
int Righy1 = 0;
int Righy2 = 0;
int Righy3 = 0;

// the sytem here checks for motor failures and balances motors out to maintain forward momentum, without drift
// checks the voltage of motors and counts up if voltage is 0
void MotorCheck(){
  if(Left1.voltage() == 0){
    Lefy1 = Lefy1 + 1;
  }
  if(Left2.voltage() == 0){
    Lefy2 = Lefy2 + 1;
  }
  if(Left3.voltage() == 0){
    Lefy3 = Lefy3 + 1;
  }
  if(Right1.voltage() == 0){
    Righy1 = Righy1 + 1;
  }
  if(Right2.voltage() == 0){
    Righy2 = Righy2 + 1;
  }
  if(Right3.voltage() == 0){
    Righy3 = Righy3 + 1;
  }
}
// Kills motors if count reaches 25
// 5 seconds of failure
void MotorKiller(){
  if(Lefy1 == 25 || Righy1 == 25){
    Left1.stop(coast);
    Right1.stop(coast);
  }
  if(Lefy2 == 25 || Righy2 == 25){
    Left2.stop(coast);
    Right2.stop(coast);
  }
  if(Lefy3 == 25 || Righy3 == 25){
    Left3.stop(coast);
    Right3.stop(coast);
  }
}