#include <Joystick.h>
#include <Relay.h>
#include <DigitalInput.h>
#include <Ultrasonic.h>

#include "main.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "ports.h"
#include "Controls.h"


robot_class* robot=NULL;

robot_class::robot_class()
{
}

void robot_class::RobotInit()
{
    robot = this;
    driverJoy = new SmoothJoystick(DRIVER_JOY_PORT);
    gunnerJoy = new SmoothJoystick(GUNNER_JOY_PORT);
    
    drivetrain = new DerekDrive(TALON_FL_MODULE, TALON_FL_CHANNEL,
                                TALON_RL_MODULE, TALON_RL_CHANNEL,
                                TALON_FR_MODULE, TALON_FR_CHANNEL,
                                TALON_RR_MODULE, TALON_RR_CHANNEL);
    ultrasonic = new AnalogChannel(4,4); //fake
}

void robot_class::DisabledInit()
{
}

void robot_class::DisabledPeriodic()
{
}

void robot_class::AutonomousInit()
{

}

void robot_class::AutonomousPeriodic()
{

}

void robot_class::TeleopInit()
{

}

void robot_class::TeleopPeriodic()
{
    updateRegistry.update();
    drivetrain -> doTeleOp();
    //commented out to avoid compiler warning barf
    
}

void robot_class::TestInit()
{
    
}

void robot_class::TestPeriodic()
{
    updateRegistry.update();
    printf("ultrasonic voltage: %f, ultrasonic value: %f\n", (float)ultrasonic->GetVoltage(), (float)ultrasonic->GetValue());;
}

START_ROBOT_CLASS(robot_class)
