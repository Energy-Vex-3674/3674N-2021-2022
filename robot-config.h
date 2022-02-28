using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern smartdrive Drivetrain;
extern motor Lift;
extern motor LeftA;
extern motor LeftB;
extern motor RightA;
extern motor RightB;
extern motor conveyor;
extern motor PLift;
extern gps GSP;
extern inertial nertial;
extern motor claw;
extern rotation Rotation1;
extern rotation Rotation2;
extern pot PotA;
extern pneumatics PGrab;
extern pneumatics PTilt;
extern bumper FrontPush;
extern bumper BackPush;
extern pot PotB;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );