using namespace vex;

extern brain Brain;
extern controller Controller;
extern motor Left1;
extern motor Left2;
extern motor Left3;
extern motor Right1;
extern motor Right2;
extern motor Right3;
extern motor Lift;
extern motor conveyor;
extern pneumatics Claw1;
extern pneumatics Claw2;
extern inertial nertial;
extern pneumatics Ptilt;
extern rotation rotor;
extern vision Vis;
extern gps GSP;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
