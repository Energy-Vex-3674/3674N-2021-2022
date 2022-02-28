#include "vex.h"
#include "Vis.h"
using namespace vex;
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
int Pistonhigh = 215;
int PistonLow = 2320;
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
  PLift.spin(forward);
  // stops at desire rotation value
  waitUntil(PotA.value(range12bit)<Pistonhigh);
  PLift.stop(hold);
  PLift.setVelocity(0,percent);
  PistonyLift = 1;
  }
// puts goal lift down
// relese pistons?
void Pistonliftdown(){
  // sets velocity and spins
  PLift.setVelocity(75,percent);
  PLift.spin(reverse);
  // waits until sensor is a desire place and stops
  waitUntil(PotA.value(range12bit)>PistonLow);
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
  PLift.spin(forward,80,pct);
  // waits until sensor is less than value
  waitUntil(PotA.value(range12bit)>650);
  PLift.stop(hold);
  PistonGrab();
  wait(50, msec);
  // drives back and lift down
  LeftA.setVelocity(40,pct);
  LeftA.spinFor(forward, 100, degrees,false);
  LeftB.setVelocity(40,pct);
  LeftB.spinFor(forward, 100, degrees,false);
  RightA.setVelocity(40,pct);
  RightA.spinFor(forward, 100, degrees,false);
  RightB.setVelocity(40,pct);
  RightB.spinFor(forward, 100, degrees,false);
  Pistonliftup();
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
