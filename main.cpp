/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
#include "vex.h"
#include "Vis.h"
using namespace vex;
competition Competition;
// variable declerations
int lift = 0;
// gps variable declearation
// sets distance to point
// boolean that says whether fast speed is on
bool Fwrd = true;
bool climb = false;
// tracks whether manual is on
bool sped = false;
bool manual = false;
// claw boolean
bool clawy = true;
bool PistonyGrab = false;
int PistonyLift = 0;
bool PistonyTilt = false;
bool Pushy = false;
// start of function declerations
// use rotation sensors to set movement to exact positions
// Grab function

void go (double y, double x){
  
  // sets heading of drivetrain
  Drivetrain.setHeading(GSP.heading(), degrees);
  Drivetrain.setTurnVelocity(40, percent);
  Drivetrain.setDriveVelocity(100, pct);
    // Print the starting position of the robot


  // Store the current position of the robot
  float startingX = GSP.xPosition(mm);
  float startingY = GSP.yPosition(mm);

  // Store the target ending position of the robot
  float endingX = 0;
  float endingY = 0;
  // Implement atan2 to calculate the heading that the robot needs to
  // turn to in order to drive towards the ending position
  float turnAngle = atan((endingX - startingX) / (endingY - startingY)) * 180 / M_PI;
  if (endingY - startingY < 0) {
    turnAngle = turnAngle + 180;
  }
    // Turn the robot to face the ending position
  Drivetrain.turnToHeading(turnAngle, degrees, true);

  // Calculate the drive distance needed, then drive towards the target position
  float driveDistance = sqrt(((endingX - startingX) * (endingX - startingX)) + ((endingY - startingY) * (endingY - startingY)));

  Drivetrain.driveFor(forward, driveDistance, mm, true);
  // Print the ending position of the robot
}
void goREVERSE (double y, double x){
  
  // sets heading of drivetrain
  Drivetrain.setHeading(GSP.heading(), degrees);
  Drivetrain.setTurnVelocity(40, percent);
  Drivetrain.setDriveVelocity(100, pct);
    // Print the starting position of the robot


  // Store the current position of the robot
  float startingX = GSP.xPosition(mm);
  float startingY = GSP.yPosition(mm);

  // Store the target ending position of the robot
  float endingX = 0;
  float endingY = 0;
  // Implement atan2 to calculate the heading that the robot needs to
  // turn to in order to drive towards the ending position
  float turnAngle = atan((endingX - startingX) / (endingY - startingY)) * 180 / M_PI;
  if (endingY - startingY < 0) {
    turnAngle = turnAngle + 180;
  }
    // Turn the robot to face the ending position
  Drivetrain.turnToHeading(turnAngle + 180, degrees, true);

  // Calculate the drive distance needed, then drive towards the target position
  float driveDistance = sqrt(((endingX - startingX) * (endingX - startingX)) + ((endingY - startingY) * (endingY - startingY)));

  Drivetrain.driveFor(forward, driveDistance, mm, true);
  // Print the ending position of the robot
}
    // Turn the robot to face the ending position

void PistonGrab(){
  if(PistonyGrab == false){
    PGrab.open();  
    PistonyGrab = true;  
  }
  else{
    PGrab.close();
    PistonyGrab = false;
  }
}
void PistonTilt(){
  if(PistonyTilt == false){
    PTilt.open();  
    PistonyTilt = true;  
  }
  else{
    PTilt.close();
    PistonyTilt = false;
  }
}
void printPosition() {
  // Print GPS position values to the V5 Brain
  Brain.Screen.print("X: %.2f", GSP.xPosition(mm));
  Brain.Screen.print("  Y: %.2f", GSP.yPosition(mm));
  Brain.Screen.newLine();
  wait(20,msec);
}
void grabby1(){
  // claw opens
  // possible soft lock
  if(clawy==true){
    claw.spin(reverse,100,pct);
    waitUntil(Rotation2.position(turns)>1.04);
    claw.stop(hold);
    Brain.Screen.print("claw is up");
    Pushy = true;
    clawy = false;
    Brain.Screen.print("claw is up");
    wait(20,msec);
  }
  else{
  // set claw to closed
  // possible softlock
    claw.spin(forward,100,pct);
    waitUntil(Rotation2.position(turns)<0.44);
    claw.stop(hold);
    
    repeat(2){
      Brain.Screen.print("Claw position: ",Rotation2.position(turns));
    }
    Brain.Screen.print("claw is down");
    clawy = true;
    Brain.Screen.print("claw is down");
    wait(20,msec);
  }
}
// lift up functions 1-2
void lifty(){
  if(lift==0){
    // sets velocity and spins
    Lift.setVelocity(60,percent);
    Lift.spin(reverse);
    // waits until sensor reads less than value and stops
    waitUntil(Rotation1.position(turns)<0.24);
    Lift.stop(hold);
    Lift.setVelocity(0,percent);
    // sets lift to 1 so lift goes up
    lift = 1;
  }
  else {
    // sets velocity and spins
    Lift.setVelocity(60,percent);
    Lift.spin(reverse);
    // waits until sensor reads less than value and stops
    waitUntil(Rotation1.position(turns)<0.06);
    Lift.stop(hold);
    Lift.setVelocity(0,percent);
    lift = 2;
  }
}
// lift down function
void lifty2(){
  // sets velocity and spins
  Lift.setVelocity(60,percent);
  Lift.spin(forward);
  // waits until sensor is less than 1
  waitUntil(Rotation1.position(turns)>0.33);
  Lift.stop(hold);
  Lift.setVelocity(0,percent);
  lift = 0;
}
// lifts goal lift up with goal
// activate pistons?
void Pistonliftup(){
  // sets velocity and spins
  PLift.setVelocity(75,percent);
  PLift.spinFor(forward,550,degrees);
  PLift.stop(hold);
  // stops at desire rotation value
  PistonyLift = 1;
  }
// puts goal lift down
// relese pistons?
void Pistonliftdown(){
  // sets velocity and spins
  PLift.setVelocity(75,percent);
  PLift.spinFor(reverse,550,degrees);
  // waits until sensor is a desire place and stops
  PLift.stop(hold);
  PLift.setVelocity(0,percent);
  PistonyLift = 0;
}
// gps function decleration
void Stack(){
  // stacks goals on ramp
  // sets velocity and spins
  Lift.spin(forward,80,pct);
  // waits until sensor is less than value
  waitUntil(Rotation1.position(turns)>0.14);
  Lift.stop(hold);
  grabby1();
  wait(50, msec);
  // drives back and lift down
  LeftA.setVelocity(40,pct);
  LeftA.startSpinFor(forward, 100, degrees);
  LeftB.setVelocity(40,pct);
  LeftB.startSpinFor(forward, 100, degrees);
  RightA.setVelocity(40,pct);
  RightA.startSpinFor(forward, 100, degrees);
  RightB.setVelocity(40,pct);
  RightB.startSpinFor(forward, 100, degrees);
  lifty();
}
void PistonStack(){
  // stacks goals on ramp
  // sets velocity and spins
  PLift.setVelocity(75, pct);
  PLift.spinFor(reverse,150,degrees);
  // waits until sensor is less than value
  PLift.stop(hold);
  PistonGrab();
  wait(50, msec);
  // drives back and lift down
  PLift.spinFor(forward,150,degrees);
}
// changes speed for fast acceleration
void spedy(){
 if(sped==false){
   sped = true;
   Brain.Screen.print("sped is on");
   Controller1.Screen.print("slow ");
   wait(20,msec);
 } 
 else{
   sped = false;
   Brain.Screen.print("sped is off");
   Controller1.Screen.print("fast ");
   wait(20,msec);
 }
}
// turns on manual
void manualdo(){
  if(manual == true){
    manual = false;
    Brain.Screen.print("manual off");
    Controller1.Screen.print("non-manual ");
    wait(20,msec);
  }
  else{
    manual = true;
    Brain.Screen.print("manual on");
    Controller1.Screen.print("manual ");
    wait(20,msec);
  }
}
void ChangeDR(){
  if(Fwrd == true){
    Fwrd = false;
    Brain.Screen.print("direction changed");
    Controller1.Screen.print("Reversed ");
    wait(20,msec);
  }
  else{
    Fwrd = true;
    Brain.Screen.print("direction changed back");
    Controller1.Screen.print("forward ");
    wait(20,msec);
  }
}
void Grabbyiest(){
  if(Fwrd == false){
    PistonGrab();
  }
  else{
    grabby1();
  }
}
void Liftiest(){
  if(Fwrd == true){
    lifty();
  }
  else{
    Pistonliftup();
  }
}
void Liftiest2(){
  if(Fwrd == true){
    lifty2();
  }
  else{
    Pistonliftdown();
  }
}
void LiftiestRV(){
  if(Fwrd == true){
    Pistonliftup();
  }
  else{
    lifty();
  }
}
void Liftiest2RV(){
  if(Fwrd == true){
    Pistonliftdown();
  }
  else{
    lifty2();
  }
}
void Stackiest(){
  if(Fwrd == true){
    Stack();
  }
  else{
    PistonStack();
  }
}
// turns manual off
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
void usercontrol(void) {
  Brain.Screen.print("hi hi hi hi hi HOOO");
  claw.stop(hold);
  Controller1.ButtonLeft.pressed(manualdo);
  Controller1.ButtonL1.pressed(spedy);
  Controller1.ButtonR1.pressed(ChangeDR);
  // User control code here, inside the loop
  while (true) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
      
    // normal everything
    if(sped==false && manual == false && Fwrd == true){
      // R1 grabs goal with claw
      Controller1.ButtonR2.pressed(Grabbyiest);
      Controller1.ButtonUp.pressed(PistonTilt);
       //X lets go of goal with claw
      // stacks goal on platform with Y
      Controller1.ButtonL2.pressed(Stackiest);
      // A raises goal
      Controller1.ButtonY.pressed(Liftiest);
      // lift down
      Controller1.ButtonRight.pressed(Liftiest2);
      // spins goal lift up
      Controller1.ButtonB.pressed(LiftiestRV);
      Controller1.ButtonDown.pressed(Liftiest2RV);
      while(sped==false && manual == false && Fwrd == true){
        Vis.takeSnapshot(RING);
        // speed is set to joystick values
        LeftA.spin(forward,Controller1.Axis3.value()/2,percent);
        LeftB.spin(forward,Controller1.Axis3.value()/2,percent);
        RightA.spin(forward,Controller1.Axis2.value()/2,percent);
        RightB.spin(forward,Controller1.Axis2.value()/2,percent);
        if(Vis.largestObject.exists && PistonyGrab == true && lift > 0 && PistonyLift == 0){
          PLift.spin(reverse,75,pct);
          // waits until sensor is a desire place and stops
          PLift.stop(hold);
          PLift.setVelocity(0,percent);
          // tilt goal
          PistonTilt();
          conveyor.spin(reverse,100,pct);
          Brain.Screen.print("sees ring");
        }
        // try while statement
        else if ( PistonyGrab == false || lift <1 || PistonyLift >0){
        // stops the conveyor from spinning
          
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }

        wait(20,msec);
      }
    }
    //speed change, no manual and drive is fwrd
    if(sped==true && manual == false && Fwrd == true){
      // R2 is used for speed change use up
      // right can be manual
      Controller1.ButtonR2.pressed(Grabbyiest);
      Controller1.ButtonL2.pressed(Stackiest);
      Controller1.ButtonUp.pressed(PistonTilt);
      // lift up 
      Controller1.ButtonY.pressed(Liftiest);
      // lift down
      Controller1.ButtonRight.pressed(Liftiest2);
      // spins goal lift up
      Controller1.ButtonB.pressed(LiftiestRV);
      Controller1.ButtonDown.pressed(Liftiest2RV);
      while(sped==true && manual == false && Fwrd == true){
        Vis.takeSnapshot(RING);
        LeftA.spin(forward,Controller1.Axis3.value()*2,percent);
        LeftB.spin(forward,Controller1.Axis3.value()*2,percent);
        RightA.spin(forward,Controller1.Axis2.value()*2,percent);
        RightB.spin(forward,Controller1.Axis2.value()*2,percent);
        if(Vis.largestObject.exists && PistonyGrab == true && lift > 0 && PistonyLift == 0){
          PLift.spin(reverse,75,pct);
          // waits until sensor is a desire place and stops
          // tilt goal
          PistonTilt();
          conveyor.spin(reverse,100,pct);
          Brain.Screen.print("sees ring");
        }
        // try while statement
        else if ( PistonyGrab == false || lift <1 || PistonyLift != 0 ){
          // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        if(Controller1.ButtonB.pressing()){
          PLift.spin(forward,80,pct);
        }
        else if(Controller1.ButtonDown.pressing()){
          PLift.spin(reverse,80,pct);
        }
        else {
          PLift.stop(hold);
        }
        wait(20,msec);
        
      }
    }
    // speed is normal with Manual and drive is Fwrd
    if(sped== false && manual == true && Fwrd == true){
      Controller1.ButtonLeft.pressed(PistonTilt);
      Controller1.ButtonUp.pressed(PistonGrab);
      while(sped==false && manual == true && Fwrd == true){
        LeftA.spin(forward,Controller1.Axis3.value()/2,percent);
        LeftB.spin(forward,Controller1.Axis3.value()/2,percent);
        RightA.spin(forward,Controller1.Axis2.value()/2,percent);
        RightB.spin(forward,Controller1.Axis2.value()/2,percent);
        // setting controls for lift
      
        if(Controller1.ButtonY.pressing()){
          // lift goes up
          Lift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonRight.pressing()){
          //lift goes down
          Lift.spin(forward,80,pct);
        }
        else{
          // lift is still.
          Lift.setVelocity(0, percent);
          Lift.stop(hold);
        }
        if(Controller1.ButtonB.pressing()){
          // lift goes up
          PLift.spin(forward,80,pct);
        }
        else if(Controller1.ButtonDown.pressing()){
          //lift goes down
          PLift.spin(reverse,80,pct);
        }
        else{
          // lift is still.
          PLift.setVelocity(0, percent);
          PLift.stop(hold);
        }
        if(Controller1.ButtonA.pressing()){
        //spins other direction
        // find out what problem with reverse is
          conveyor.spin(reverse,80,pct);
        } 
        else if(Controller1.ButtonX.pressing()){
        // strts coveyor spinning
          conveyor.spin(forward,80,pct);
        }
        else{
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        if(Controller1.ButtonR2.pressing()){
          claw.spin(forward,80,pct);
        }
        else if(Controller1.ButtonL2.pressing()){
          claw.spin(reverse,80,pct);
          if(Rotation2.position(turns)>1.04){
            claw.stop(hold);
          }
        }
        else{
          claw.stop(hold);
          claw.setVelocity(0, percent);
        }
        if (Controller1.ButtonUp.pressing()){
          PTilt.open();
        }
        else{
          PTilt.close();
        }
        //speed change
      } 
    }
    // speed is fast with manual
    if(sped == true && manual == true && Fwrd == true){
      Controller1.ButtonLeft.pressed(PistonTilt);
      Controller1.ButtonUp.pressed(PistonGrab);
      while(sped==true && manual == true && Fwrd == true){
        LeftA.spin(forward,Controller1.Axis3.value()*2,percent);
        LeftB.spin(forward,Controller1.Axis3.value()*2,percent);
        RightA.spin(forward,Controller1.Axis2.value()*2,percent);
        RightB.spin(forward,Controller1.Axis2.value()*2,percent);
        // setting controls for lift
      
        if(Controller1.ButtonY.pressing()){
          // lift goes up
          Lift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonRight.pressing()){
          //lift goes down
          Lift.spin(forward,80,pct);
        }
        else{
          // lift is still.
          Lift.setVelocity(0, percent);
          Lift.stop(hold);
        }
        if(Controller1.ButtonB.pressing()){
          // lift goes up
          PLift.spin(forward,80,pct);
        }
        else if(Controller1.ButtonDown.pressing()){
          //lift goes down
          PLift.spin(reverse,80,pct);
        }
        else{
          // lift is still.
          PLift.setVelocity(0, percent);
          PLift.stop(hold);
        }
        if(Controller1.ButtonA.pressing()){
        //spins other direction
        // find out what problem with reverse is
          conveyor.spin(reverse,80,pct);
        } 
        else if(Controller1.ButtonX.pressing()){
        // strts coveyor spinning
          conveyor.spin(forward,80,pct);
        }
        else{
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        if(Controller1.ButtonR2.pressing()){
          claw.spin(forward,80,pct);
        }
        else if(Controller1.ButtonL2.pressing()){
          claw.spin(reverse,80,pct);
          if(Rotation2.position(turns)>1.04){
            claw.stop(hold);
          }
        }
        else{
          claw.stop(hold);
          claw.setVelocity(0, percent);
        }
        if (Controller1.ButtonUp.pressing()){
          PTilt.open();
        }
        else{
          PTilt.close();
        }
        wait(20,msec);
        //speed change

      }
    } 
    // Just reversed Drivetrain
    if(sped==false && manual == false && Fwrd == false){
      // R1 grabs goal with claw
      Controller1.ButtonR2.pressed(Grabbyiest);
       //X lets go of goal with claw
      // stacks goal on platform with Y
      Controller1.ButtonL2.pressed(Stackiest);
      Controller1.ButtonUp.pressed(PistonTilt);
      // A raises goal
      // spins goal lift down with Down
      Controller1.ButtonY.pressed(Liftiest);
      // lift down
      Controller1.ButtonRight.pressed(Liftiest2);
      // spins goal lift up
      Controller1.ButtonB.pressed(LiftiestRV);
      Controller1.ButtonDown.pressed(Liftiest2RV);
      while(sped==false && manual == false && Fwrd == false){
        Vis.takeSnapshot(RING);
      // speed is set to joystick values
        LeftA.spin(reverse,Controller1.Axis2.value()/2,percent);
        LeftB.spin(reverse,Controller1.Axis2.value()/2,percent);
        RightA.spin(reverse,Controller1.Axis3.value()/2,percent);
        RightB.spin(reverse,Controller1.Axis3.value()/2,percent);
        if(Vis.largestObject.exists && PistonyGrab == true && lift > 0 && PistonyLift == 0){
          PLift.spin(reverse,75,pct);
          // waits until sensor is a desire place and stops
          // tilt goal
          PistonTilt();
          conveyor.spin(reverse,100,pct);
          Brain.Screen.print("sees ring");
        }
        // try while statement
        else if ( PistonyGrab == false || lift <1 ){
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        if(Controller1.ButtonY.pressing()){
          PLift.spin(forward,80,pct);
        }
        else if(Controller1.ButtonRight.pressing()){
          PLift.spin(reverse,80,pct);
        }
        else {
          PLift.stop(hold);
        }
        wait(20,msec);
      }
    }
    //speed change and no manual reversed Drive
    if(sped==true && manual == false && Fwrd == false){
      // R2 is used for speed change use up
      // right can be manual
      Controller1.ButtonR2.pressed(Grabbyiest);
      Controller1.ButtonL2.pressed(Stackiest);
      // lift up 
      Controller1.ButtonY.pressed(Liftiest);
      // lift down
      Controller1.ButtonRight.pressed(Liftiest2);
      // spins goal lift up
      Controller1.ButtonUp.pressed(PistonTilt);
      Controller1.ButtonB.pressed(LiftiestRV);
      Controller1.ButtonDown.pressed(Liftiest2RV);
      while(sped==true && manual == false && Fwrd == false){
        Vis.takeSnapshot(RING);
        LeftA.spin(reverse,Controller1.Axis2.value()*2,percent);
        LeftB.spin(reverse,Controller1.Axis2.value()*2,percent);
        RightA.spin(reverse,Controller1.Axis3.value()*2,percent);
        RightB.spin(reverse,Controller1.Axis3.value()*2,percent);
        if(Vis.largestObject.exists && PistonyGrab == true && lift > 0 && PistonyLift == 0){
          PLift.spin(reverse,75,pct);
          // waits until sensor is a desire place and stops
          // tilt goal
          PistonTilt();
          conveyor.spin(reverse,100,pct);
          Brain.Screen.print("sees ring");
        }
        // try while statement
        else if ( PistonyGrab == false || lift <1 ){
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        if(Controller1.ButtonY.pressing()){
          PLift.spin(forward,80,pct);
        }
        else if(Controller1.ButtonRight.pressing()){
          PLift.spin(reverse,80,pct);
        }
        else {
          PLift.stop(hold);
        }
        wait(20,msec);
      }
    }
    // speed is normal with Manual Reversed Drive
    if(sped== false && manual == true && Fwrd == false){
      Controller1.ButtonLeft.pressed(PistonTilt);
      Controller1.ButtonUp.pressed(PistonGrab);
      while(sped==false && manual == true && Fwrd == false){
        LeftA.spin(reverse,Controller1.Axis2.value()/2,percent);
        LeftB.spin(reverse,Controller1.Axis2.value()/2,percent);
        RightA.spin(reverse,Controller1.Axis3.value()/2,percent);
        RightB.spin(reverse,Controller1.Axis3.value()/2,percent);
        if(Controller1.ButtonDown.pressing()){
          PLift.spin(forward,80,pct);
        }
        // setting controls for lift
        if(Controller1.ButtonY.pressing()){
          // lift goes up
          PLift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonRight.pressing()){
          //lift goes down
          PLift.spin(reverse,80,pct);
        }
        else{
          // lift is still.
          PLift.setVelocity(0, percent);
          PLift.stop(hold);
        }
        if(Controller1.ButtonB.pressing()){
          // lift goes up
          Lift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonDown.pressing()){
          //lift goes down
          Lift.spin(forward,80,pct);
        }
        else{
          // lift is still.
          Lift.setVelocity(0, percent);
          Lift.stop(hold);
        }
        if(Controller1.ButtonA.pressing()){
        //spins other direction
        // find out what problem with reverse is
          conveyor.spin(reverse,80,pct);
        } 
        else if(Controller1.ButtonX.pressing()){
        // strts coveyor spinning
          conveyor.spin(forward,80,pct);
        }
        else{
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        if(Controller1.ButtonR2.pressing()){
          claw.spin(forward,80,pct);
        }
        else if(Controller1.ButtonL2.pressing()){
          claw.spin(reverse,80,pct);
          if(Rotation2.position(turns)>1.04){
            claw.stop(hold);
          }
        }
        else{
          claw.stop(hold);
          claw.setVelocity(0, percent);
        }
        if (Controller1.ButtonUp.pressing()){
          PTilt.open();
        }
        else{
          PTilt.close();
        }
        //speed change
        wait(20,msec);
      } 
    }
    // speed is fast with manual Reversed Drive
    if(sped == true && manual == true && Fwrd == false){
      Controller1.ButtonLeft.pressed(PistonTilt);
      Controller1.ButtonUp.pressed(PistonGrab);
      while(sped==true && manual == true && Fwrd == false){
        LeftA.spin(reverse,Controller1.Axis2.value()*2,percent);
        LeftB.spin(reverse,Controller1.Axis2.value()*2,percent);
        RightA.spin(reverse,Controller1.Axis3.value()*2,percent);
        RightB.spin(reverse,Controller1.Axis3.value()*2,percent);
        // setting controls for lift
      
        if(Controller1.ButtonY.pressing()){
          // lift goes up
          PLift.spin(forward,80,pct);
        }
        else if(Controller1.ButtonRight.pressing()){
          //lift goes down
          PLift.spin(reverse,80,pct);
        }
        else{
          // lift is still.
          PLift.setVelocity(0, percent);
          PLift.stop(hold);
        }
        if(Controller1.ButtonB.pressing()){
          // lift goes up
          Lift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonDown.pressing()){
          //lift goes down
          Lift.spin(forward,80,pct);
        }
        else{
          // lift is still.
          Lift.setVelocity(0, percent);
          Lift.stop(hold);
        }
        if(Controller1.ButtonA.pressing()){
        //spins other direction
        // find out what problem with reverse is
          conveyor.spin(reverse,80,pct);
        } 
        else if(Controller1.ButtonX.pressing()){
        // strts coveyor spinning
          conveyor.spin(forward,80,pct);
        }
        else{
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        if(Controller1.ButtonR2.pressing()){
          claw.spin(forward,80,pct);
        }
        else if(Controller1.ButtonL2.pressing()){
          claw.spin(reverse,80,pct);
          if(Rotation2.position(turns)>1.04){
            claw.stop(hold);
          }
        }
        else{
          claw.stop(hold);
          claw.setVelocity(0, percent);
        }
        if (Controller1.ButtonUp.pressing()){
          PTilt.open();
        }
        else{
          PTilt.close();
        }
        wait(20,msec);
        //speed change

      }
    } 
    // end of while function
    // ........................................................................
   // Sleep the task for a short amount of time to
    // prevent wasted resources.
    task::sleep(20);
  }
}
// end of function declerations
// A global instance of competition


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void){
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  lift = 0;
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  GSP.calibrate();
  // Run the pre-autonomous function.
  // Prevent main from exiting with an infinite loop.
  // put driver control in driver control
  // add go function here instead of autonomous.
  while (true) {
    wait(100,msec);
    // normal drive
    // use cubic function
  }
  // end of int main()
}
