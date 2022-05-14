#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller(primary);
motor Left1 = motor(PORT20,ratio18_1,true);
motor Left2 = motor(PORT19,ratio18_1,false);
motor Left3 = motor(PORT18,ratio18_1,true);
motor Right1 = motor(PORT13,ratio18_1,false);
motor Right2 = motor(PORT12,ratio18_1,true);
motor Right3 = motor(PORT11,ratio18_1,false);
motor Lift = motor(PORT9,ratio18_1,false);
motor conveyor = motor(PORT17,ratio18_1,false);
pneumatics Claw1  = pneumatics(Brain.ThreeWirePort.F);
pneumatics Claw2 = pneumatics(Brain.ThreeWirePort.H);
pneumatics Ptilt = pneumatics(Brain.ThreeWirePort.G);
inertial nertial = inertial(PORT16);
rotation rotor = rotation(PORT10);
gps GSP = gps (PORT1,-180,50,mm, 270);
// will not work



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}