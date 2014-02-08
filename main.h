#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
#include <Joystick.h>
#include <AnalogChannel.h>

#include "SmoothJoystick.h"
#include "DerekDrive.h"

#include "UpdateRegistry.h"


class robot_class : public IterativeRobot
{
public:
    robot_class();

    void RobotInit();

    void DisabledInit();
    void DisabledPeriodic();

    void AutonomousInit();
    void AutonomousPeriodic();

    void TeleopInit();
    void TeleopPeriodic();

    void TestInit();
    void TestPeriodic();
    
    //DerekDrive* test_drivetrain;
    SmoothJoystick* driverJoy;
    SmoothJoystick* gunnerJoy;
    
    DerekDrive* drivetrain;
    
    UpdateRegistry updateRegistry;
    
    AnalogChannel* ultrasonic;
    
private:
};

#endif // MAIN_H
