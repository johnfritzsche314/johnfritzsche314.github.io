/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\john                                             */
/*    Created:      Tue May 21 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
using namespace std;
int idle = 0;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;                                     //defining the brain
vex::controller Controller(vex::controllerType::primary);   //defining the primary controller
vex::controller Controller2(vex::controllerType::partner);  //defining the partner controller

// A global instance of vex::competition
vex::competition Competition;                               //setting the code to be in competition format

// define your global instances of motors and other devices here

vex::motor leftMotor (vex::PORT1, vex::gearSetting::ratio18_1, false);    //defining the left front chassis motor
vex::motor leftMotor2 (vex::PORT2, vex::gearSetting::ratio18_1, false);   //defining the left back chassis motor
vex::motor rightMotor (vex::PORT3, vex::gearSetting::ratio18_1, true);    //defining the right front chassis motor
vex::motor rightMotor2 (vex::PORT4, vex::gearSetting::ratio18_1, true);   //defining the right back chassis motor
vex::motor armMotorR (vex::PORT5, vex::gearSetting::ratio6_1, true);      //defining the right arm motor
vex::motor armMotorL (vex::PORT6, vex::gearSetting::ratio6_1, false);      //defining the left arm motor
vex::motor claw (vex::PORT7, vex::gearSetting::ratio6_1, false);          //defining the claw motor
/* vex::motor strafe (vex::PORT8, vex::gearSetting::ratio18_1, false); */


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void stopReset()                            //Function that stops all motors and resets all sensors
{
  leftMotor.stop(brakeType::brake);
  rightMotor.stop(brakeType::brake);
  leftMotor2.stop(brakeType::brake);
  rightMotor2.stop(brakeType::brake);
  armMotorR.stop(brakeType::brake);
  armMotorL.stop(brakeType::brake);
  claw.stop(brakeType::brake);
  /*strafe.stop(brakeType::brake); */
  task::sleep(1);
}

void forward(int pwr)                       //Function that sets to chassis motors to forward
{
  leftMotor.spin(directionType::fwd,pwr,velocityUnits::pct);
  rightMotor.spin(directionType::fwd,pwr,velocityUnits::pct);
  leftMotor2.spin(directionType::fwd,pwr,velocityUnits::pct);
  rightMotor2.spin(directionType::fwd,pwr,velocityUnits::pct);
}

void backward(int pwr)                      //Function that sets to chassis motors to reverse
{
  leftMotor.spin(directionType::rev,pwr,velocityUnits::pct);
  rightMotor.spin(directionType::rev,pwr,velocityUnits::pct);
  leftMotor2.spin(directionType::rev,pwr,velocityUnits::pct);
  rightMotor2.spin(directionType::rev,pwr,velocityUnits::pct);
}

/*
void strafeRight(int pwr)
{
  strafe.spin(directionType::fwd,pwr,velocityUnits::pct);
}

void strafeLeft(int pwr)
{
  strafe.spin(directionType::rev,pwr,velocityUnits::pct);
} */

void armUp(int pwr)                         //Function that sets the arm motors to forward (up)
{
  armMotorR.spin(directionType::fwd,pwr,velocityUnits::pct);
  armMotorL.spin(directionType::fwd,pwr,velocityUnits::pct);
}

void armDown(int pwr)                       //Function that sets the arm motors to reverse (down)
{
  armMotorR.spin(directionType::rev,pwr,velocityUnits::pct);
  armMotorL.spin(directionType::rev,pwr,velocityUnits::pct);
}

void openClaw(int pwr)                      //Function that sets the claw motor to forward
{
  claw.spin(directionType::fwd,pwr,velocityUnits::pct);
}

void closeClaw(int pwr)                     //Function that sets the claw motor to reverse
{
  claw.spin(directionType::rev,pwr,velocityUnits::pct);
}

void holdChassis()                          //Function that sets the chassis motors to the hold type of braking
{
  leftMotor.stop(brakeType::hold);
  rightMotor.stop(brakeType::hold);
  rightMotor2.stop(brakeType::hold);
  leftMotor2.stop(brakeType::hold);
}

void brakeChassis()                         //Function that sets the chassis motors to the brake type of braking
{
  leftMotor.stop(brakeType::brake);
  rightMotor.stop(brakeType::brake);
  rightMotor2.stop(brakeType::brake);
  leftMotor2.stop(brakeType::brake);
}

void coastChassis()                         //Function that sets the chassis motors to the coast type of braking
{
  leftMotor.stop(brakeType::coast);
  leftMotor2.stop(brakeType::coast);
  rightMotor.stop(brakeType::coast);
  rightMotor2.stop(brakeType::coast);
}

void idleTrue()
{
  claw.stop(brakeType::brake);
  task::sleep(100);
  claw.spin(directionType::rev,5,velocityUnits::pct);
}

void idleFalse()
{
  void stopReset();
}

/*
void holdStrafe()
{
  strafe.stop(brakeType::hold);
}

void brakeStrafe()
{
  strafe.stop(brakeType::brake);
}

void coastStrafe()
{
  strafe.stop(brakeType::coast);
} */

void holdArm()                                //Function that sets the arm motors to the hold type of braking
{
  armMotorR.stop(brakeType::hold);
  armMotorL.stop(brakeType::hold);
}

void brakeArm()                               //Function that sets the arm motors to the brake type of braking
{
  armMotorR.stop(brakeType::brake);
  armMotorL.stop(brakeType::brake);
}

void coastArm()                                //Function that sets the arm motors to the coast type of braking
{
  armMotorR.stop(brakeType::coast);
  armMotorL.stop(brakeType::coast);
}

void holdClaw()                                //Function that sets the claw motor to the hold type of braking
{   
  claw.stop(brakeType::hold);
}

void brakeClaw()                               //Function that sets the claw motor to the brake type of braking
{
  claw.stop(brakeType::brake);
}

void coastClaw()                               //Function that sets the claw motor to the coast type of braking
{
  claw.stop(brakeType::coast);
}

void pre_auton( void )
{
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void )
{
  Brain.Screen.render(true, false);
   Brain.Screen.clearLine(0,color::green);
        Brain.Screen.clearLine(1,color::green);
        Brain.Screen.setCursor(1,0);
        Brain.Screen.print("Penguins have knees");
        Brain.Screen.setCursor(2,0);
        Brain.Screen.print("('>')");
        Brain.Screen.render();
  stopReset();
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

void usercontrol(void)
{
  // User control code here, inside the loop
  int idle = 0;

  while(1 == 1)
  {
    rightMotor.spin(directionType::fwd,Controller.Axis2.position(percentUnits::pct),velocityUnits::pct);                        //Setting the chassis control to "tank control,"
    rightMotor2.spin(directionType::fwd,Controller.Axis2.position(percentUnits::pct),velocityUnits::pct);                       //which means the right joystick of the controller
    leftMotor.spin(directionType::fwd,Controller.Axis3.position(percentUnits::pct),velocityUnits::pct);                         //controls the right chassis motors, and the left
    leftMotor2.spin(directionType::fwd,Controller.Axis3.position(percentUnits::pct),velocityUnits::pct);                        //joystick controls the left side of the chassis

  /*  if(Controller.ButtonA.pressing())
    {
      void strafeRight(int pwr = 100);
    }

    else if(Controller.ButtonY.pressing())
    {
      void strafeLeft(int pwr = 100);
    }

    else
    {
      void holdStrafe();
    } */

    armMotorR.spin(directionType::fwd,Controller2.Axis3.position(percentUnits::pct),velocityUnits::pct);
    armMotorL.spin(directionType::fwd,Controller2.Axis3.position(percentUnits::pct),velocityUnits::pct);
    claw.spin(directionType::fwd,Controller2.Axis2.position(percentUnits::pct),velocityUnits::pct);

    if(Controller2.ButtonX.pressing())
    {
      idle = 1;
    }

    else if(Controller.ButtonB.pressing())
    {
      idle = 0;
    }

    else
    {
      vex::task::sleep(1);
    }

    if(idle == 1)
    {
      void idleTrue();
    }

    if(idle == 0)
    {
      void idleFalse();
    }

    vex::task::sleep(100); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1 == 1)
    {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}