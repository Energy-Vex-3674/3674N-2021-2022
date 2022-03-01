#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
// change the pistons to a motor
// change lift to single motor
controller Controller1;
motor Lift = motor(PORT18, ratio36_1, true);
motor LeftA = motor(PORT2, ratio18_1, true);
motor LeftB = motor(PORT1, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(LeftA, LeftB);
motor RightA = motor(PORT12, ratio18_1, false);
motor RightB = motor(PORT11, ratio18_1,false);
motor_group RightDriveSmart = motor_group(RightA, RightB);
// can change inertial to gps if needed
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart,GSP,319.19, 295, 40, mm, 1);
motor PLift = motor(PORT7,ratio36_1,false);
motor conveyor = motor(PORT17,ratio18_1,true);
gps GSP = gps (PORT8,-180,50,mm, 270);
inertial nertial = inertial(PORT5);
motor claw = motor(PORT5,ratio18_1,false);
rotation Rotation1 = rotation(PORT19,false);
rotation Rotation2 = rotation(PORT20,false);
pot PotA = pot(Brain.ThreeWirePort.C);
pneumatics PGrab = pneumatics(Brain.ThreeWirePort.G);
pneumatics PTilt = pneumatics(Brain.ThreeWirePort.B);
pot PotB = pot(Brain.ThreeWirePort.D);
// decomment later motor Claw = motor(PORT16,ratio18_1, true);
// VEXcode generated functions
/*
Ports:
Lift:1
LEftA:19
LeftB:20
RightA:9
RightB:10
Glift:18
Conveyor:11
GPS:13
Inertial:12
Claw:16
Vision:
rotation1: 2
potientemometer: A
*/
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}