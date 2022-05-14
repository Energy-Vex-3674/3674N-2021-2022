// includes Vex.h file
#ifndef VEX_H
#define VEX_H
#include "vex.h"
#endif

// Includes and makes variables external
// Better way would be to use get functions and scope
#ifndef STUFF_H_INCLUDED
#define STUFF_H_INCLUDED
//lift variable
extern int lift;
// direction bool
extern bool Fwrd;
// tracks whether speed is on
extern bool sped;
// maual bool
extern bool manual;
// claw booleans
extern bool Law1;
extern bool Law2;
// tilt boolean
extern bool Tilt;
// function declerations
void Grab1();
void Grab2();
void PistonTilt();
void lifty();
void lifty2();
void Stack();
void spedy();
void manualdo();
void ChangeDR();
void Greab();
#endif