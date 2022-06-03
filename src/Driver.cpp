//////////////////////////////////////
// Includes Header files
#ifndef VEX_H
#define VEH_H
#include "vex.h"
#endif

#ifndef DRIVER_H_INCLUDED
#define DRIVER_H_INCLUDED
#include "Driver.h"
#endif

#ifndef VIS_H
#define VIS_H
#include "Vis.h"
#endif

#ifndef PROTO_MOTOR_BALANCE_H
#define PROTO_MOTOR_BALANCE_H
#include "Proto_Motor_Balance.h"
#endif
///////////////////////////////

// usercontrol function
void usercontrol(void) {
  ////////////
  // contains all of the event setups
  // to understand check the original functions
  Controller.ButtonLeft.pressed(manualdo);
  Controller.ButtonR1.pressed(spedy);
  Controller.ButtonL1.pressed(ChangeDR);
  Controller.ButtonR2.pressed(Greab);
  Controller.ButtonUp.pressed(PistonTilt);
   //X lets go of goal with claw
  // stacks goal on platform with Y
  Controller.ButtonL2.pressed(Stack);
  // A raises goal
  Controller.ButtonY.pressed(lifty);
  // lift down
  Controller.ButtonRight.pressed(lifty2);
  // spins goal lift up
  ////////////////

  // User control code here, inside the loop
  while (true) {
    // This is the main execution loop for the user control program.
    // normal everything
    // if statement triggers the while loop
    // if staement is probably not neccesary here
    if(sped==false && manual == false && Fwrd == true){
      while(sped==false && manual == false && Fwrd == true){
        Vis.takeSnapshot(RING);
        // speed is set to joystick values
        // arcade drive
        Left1.spin(forward,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Left2.spin(forward,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Left3.spin(forward,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Right1.spin(forward,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Right2.spin(forward,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Right3.spin(forward,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        // motor balance check only happens if joy sticks are moving
        if(Controller.Axis3.value() != 0 || Controller.Axis1.value() != 0){
          MotorCheck();
          MotorKiller();
        }
        // automated ring collection from vision sensor
        //try Vis.RING[0].exists
        if(Vis.largestObject.exists && Law2 == true && lift > 0 ){
          conveyor.spin(reverse,100,pct);
          Brain.Screen.print("sees ring");
        // 
        }
        else{
          conveyor.stop(hold);
        }
        wait(20,msec);
      }
    }
    // everything is the same as before but faster movement
    //speed change, no manual and drive is fwrd
    if(sped==true && manual == false && Fwrd == true){
      while(sped==true && manual == false && Fwrd == true){
        Vis.takeSnapshot(RING);
        // speed is set to joystick values
        Left1.spin(forward,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        Left2.spin(forward,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        Left3.spin(forward,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        Right1.spin(forward,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        Right2.spin(forward,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        Right3.spin(forward,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        if(Controller.Axis3.value() != 0 || Controller.Axis1.value() != 0){
          MotorCheck();
          MotorKiller();
        }
        //try Vis.RING[0].exists
        // so I can use multiple different items
        if(Vis.largestObject.exists && Law2 == true && lift > 0 ){
            conveyor.spin(reverse,100,pct);
            Brain.Screen.print("sees ring");
        // 
        }
        else{
          conveyor.stop(hold);
        }
        wait(20,msec);
        
      }
    }
    // speed is normal with Manual and drive is Fwrd
    // everything is the same as befor, but the events are overided by manual control
    if(sped== false && manual == true && Fwrd == true){
      while(sped== false && manual == true && Fwrd == true){
      Vis.takeSnapshot(RING);
        // speed is set to joystick values
        Left1.spin(forward,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Left2.spin(forward,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Left3.spin(forward,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Right1.spin(forward,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Right2.spin(forward,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Right3.spin(forward,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        if(Controller.Axis3.value() != 0 || Controller.Axis1.value() != 0){
          MotorCheck();
          MotorKiller();
        }
        // fix vision
        //conveyor.spin(reverse,100,pct);
        //Brain.Screen.print("sees ring");ift
      
        if(Controller.ButtonY.pressing()){
          // lift goes up
          Lift.spin(forward,80,pct);
        }
        else if(Controller.ButtonRight.pressing()){
          //lift goes down
          Lift.spin(reverse,80,pct);
        }
        else{
          // lift is still.
          Lift.setVelocity(0, percent);
          Lift.stop(hold);
        }
        
        
        if(Controller.ButtonA.pressing()){
        //spins other direction
        // find out what problem with reverse is
          conveyor.spin(reverse,80,pct);
        } 
        else if(Controller.ButtonX.pressing()){
        // strts coveyor spinning
          conveyor.spin(forward,80,pct);
        }
        else{
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        
        //speed change
      }
     } 
    
    // speed is fast with manual
    if(sped == true && manual == true && Fwrd == true){
      while(sped==true && manual == true && Fwrd == true){
        Vis.takeSnapshot(RING);
        // speed is set to joystick values
        Left1.spin(forward,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        Left2.spin(forward,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        Left3.spin(forward,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        Right1.spin(forward,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        Right2.spin(forward,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        Right3.spin(forward,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        if(Controller.Axis3.value() != 0 || Controller.Axis1.value() != 0){
          MotorCheck();
          MotorKiller();
        }
        // fix vision
        //conveyor.spin(reverse,100,pct);
        //Brain.Screen.print("sees ring");
        // setting controls for lift
      
        if(Controller.ButtonY.pressing()){
          // lift goes up
          Lift.spin(forward,80,pct);
        }
        else if(Controller.ButtonRight.pressing()){
          //lift goes down
          Lift.spin(reverse,80,pct);
        }
        else{
          // lift is still.
          Lift.setVelocity(0, percent);
          Lift.stop(hold);
        }
        
        
        if(Controller.ButtonA.pressing()){
        //spins other direction
        // find out what problem with reverse is
          conveyor.spin(reverse,80,pct);
        } 
        else if(Controller.ButtonX.pressing()){
        // strts coveyor spinning
          conveyor.spin(forward,80,pct);
        }
        else{
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        
        wait(20,msec);
        //speed change

        }
    } 
    // Just reversed Drivetrain
    if(sped==false && manual == false && Fwrd == false){
      // R1 grabs goal with claw
      while(sped==false && manual == false && Fwrd == false){
        Vis.takeSnapshot(RING);
      // speed is set to joystick values
      // the arcade is reversed because of direction
      // could be wrong
        Left1.spin(reverse,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Left2.spin(reverse,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Left3.spin(reverse,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Right1.spin(reverse,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Right2.spin(reverse,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Right3.spin(reverse,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        if(Controller.Axis3.value() != 0 || Controller.Axis1.value() != 0){
          MotorCheck();
          MotorKiller();
        }
        //try Vis.RING[0].exists
        // so I can use multiple different items
        if(Vis.largestObject.exists && Law2 == true && lift > 0 ){
          conveyor.spin(reverse,100,pct);
          Brain.Screen.print("sees ring");
        // 
        }
        else{
          conveyor.stop(hold);
        }
        wait(20,msec);
      }
    }
    //speed change and no manual reversed Drive
    if(sped==true && manual == false && Fwrd == false){
      // R2 is used for speed change use up
      // right can be manual
      while(sped==true && manual == false && Fwrd == false){
        Vis.takeSnapshot(RING);
        Left1.spin(reverse,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        Left2.spin(reverse,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        Left3.spin(reverse,Controller.Axis3.value()-Controller.Axis1.value(),pct);
        Right1.spin(reverse,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        Right2.spin(reverse,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        Right3.spin(reverse,Controller.Axis3.value()+Controller.Axis1.value(),pct);
        if(Controller.Axis3.value() != 0 || Controller.Axis1.value() != 0){
          MotorCheck();
          MotorKiller();
        }
        //try Vis.RING[0].exists
        // so I can use multiple different items
        if(Vis.largestObject.exists && Law2 == true && lift > 0 ){
          conveyor.spin(reverse,100,pct);
          Brain.Screen.print("sees ring");
        // 
        }
        else{
          conveyor.stop(hold);
        }
        wait(20,msec);
      }
    }
    // speed is normal with Manual Reversed Drive
    if(sped== false && manual == true && Fwrd == false){
      
      while(sped==false && manual == true && Fwrd == false){
        Left1.spin(reverse,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Left2.spin(reverse,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Left3.spin(reverse,Controller.Axis3.value()/2-Controller.Axis1.value()/2,pct);
        Right1.spin(reverse,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Right2.spin(reverse,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        Right3.spin(reverse,Controller.Axis3.value()/2+Controller.Axis1.value()/2,pct);
        if(Controller.Axis3.value() != 0 || Controller.Axis1.value() != 0){
          MotorCheck();
          MotorKiller();
        }
        // fix vision
        // fix vision
        //conveyor.spin(reverse,100,pct);
        //Brain.Screen.print("sees ring");
        // setting controls for lift
      
        if(Controller.ButtonY.pressing()){
          // lift goes up
          Lift.spin(forward,80,pct);
        }
        else if(Controller.ButtonRight.pressing()){
          //lift goes down
          Lift.spin(reverse,80,pct);
        }
        else{
          // lift is still.
          Lift.setVelocity(0, percent);
          Lift.stop(hold);
        }
        
        
        if(Controller.ButtonA.pressing()){
        //spins other direction
        // find out what problem with reverse is
          conveyor.spin(reverse,80,pct);
        } 
        else if(Controller.ButtonX.pressing()){
        // strts coveyor spinning
          conveyor.spin(forward,80,pct);
        }
        else{
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
        }
        
        wait(20,msec);
      } 
    }
    // speed is fast with manual Reversed Drive
    if(sped == true && manual == true && Fwrd == false){
      
      while(sped==true && manual == true && Fwrd == false){
        Left1.spin(reverse,Controller.Axis3.value()-Controller.Axis1.value()/2,pct);
        Left2.spin(reverse,Controller.Axis3.value()-Controller.Axis1.value()/2,pct);
        Left3.spin(reverse,Controller.Axis3.value()-Controller.Axis1.value()/2,pct);
        Right1.spin(reverse,Controller.Axis3.value()+Controller.Axis1.value()/2,pct);
        Right2.spin(reverse,Controller.Axis3.value()+Controller.Axis1.value()/2,pct);
        Right3.spin(reverse,Controller.Axis3.value()+Controller.Axis1.value()/2,pct);
        if(Controller.Axis3.value() != 0 || Controller.Axis1.value() != 0){
          MotorCheck();
          MotorKiller();
        }
        // fix vision
        // fix vision
        //conveyor.spin(reverse,100,pct);
        //Brain.Screen.print("sees ring");
        // setting controls for lift
      
        if(Controller.ButtonY.pressing()){
          // lift goes up
          Lift.spin(forward,80,pct);
        }
        else if(Controller.ButtonRight.pressing()){
          //lift goes down
          Lift.spin(reverse,80,pct);
        }
        else{
          // lift is still.
          Lift.setVelocity(0, percent);
          Lift.stop(hold);
        }
        
        
        if(Controller.ButtonA.pressing()){
        //spins other direction
        // find out what problem with reverse is
          conveyor.spin(reverse,80,pct);
        } 
        else if(Controller.ButtonX.pressing()){
        // strts coveyor spinning
          conveyor.spin(forward,80,pct);
        }
        else{
        // stops the conveyor from spinning
          conveyor.stop(hold);
          conveyor.setVelocity(0, percent);
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