#include "Auton.h"
using namespace vex;
void usercontrol(void) {
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
       //X lets go of goal with claw
      // stacks goal on platform with Y
      Controller1.ButtonL2.pressed(Stack);
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
          waitUntil(PotA.value(range12bit)>2600);
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
    //speed change, no manual and drive is fwrd
    if(sped==true && manual == false && Fwrd == true){
      // R2 is used for speed change use up
      // right can be manual
      Controller1.ButtonR2.pressed(Grabbyiest);
      Controller1.ButtonL2.pressed(Stack);
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
          waitUntil(PotA.value(range12bit)>2600);
          PLift.stop(hold);
          PLift.setVelocity(0,percent);
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
          PLift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonDown.pressing()){
          //lift goes down
          PLift.spin(forward,80,pct);
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
          PLift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonDown.pressing()){
          //lift goes down
          PLift.spin(forward,80,pct);
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
      Controller1.ButtonL2.pressed(PistonStack);
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
          waitUntil(PotA.value(range12bit)>2600);
          PLift.stop(hold);
          PLift.setVelocity(0,percent);
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
      Controller1.ButtonL2.pressed(PistonStack);
      // lift up 
      Controller1.ButtonY.pressed(Liftiest);
      // lift down
      Controller1.ButtonRight.pressed(Liftiest2);
      // spins goal lift up
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
          waitUntil(PotA.value(range12bit)>2600);
          PLift.stop(hold);
          PLift.setVelocity(0,percent);
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
          PLift.spin(reverse,80,pct);
        }
        // setting controls for lift
        if(Controller1.ButtonY.pressing()){
          // lift goes up
          PLift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonRight.pressing()){
          //lift goes down
          PLift.spin(forward,80,pct);
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
          PLift.spin(reverse,80,pct);
        }
        else if(Controller1.ButtonRight.pressing()){
          //lift goes down
          PLift.spin(forward,80,pct);
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