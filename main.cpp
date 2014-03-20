#include <Joystick.h>

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
    std::printf("TEST CODE 1.0");
    robot = this;
    driverJoy = new SmoothJoystick(DRIVER_JOY_PORT);
    
    sense = new Sensors();
    motors = new Motors();
    pneumatics = new Pneumatics();
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
}

void robot_class::TestInit()
{
    button = MOTORS;
    selection = 0;
}

void robot_class::TestPeriodic()
{
    static int lastSelection = 0;
    updateRegistry.update();
    if (selection < 0)
        selection = 0;
    /*
    if (selection < lastSelection)
        std::printf("DECREMENT\n");
    else if (selection > lastSelection)
        std::printf("INCREMENT\n");
    */
    getButtons();
    if (button == SENSORS)
        sense -> runSensors(selection/10);
    else if (button == PNEUMATICS)
        pneumatics -> runPneumatics(selection/10);
    else if (button == MOTORS)
        motors -> runMotor(selection/10);
    lastSelection = selection;
}
void robot_class::printStuff()
{
    std::printf("R1: Increment selection\nL1: Decrement selection\nLeft Analog stick for control\n\n");
    std::printf("TRIANGLE(Y): Print instructions\n");
    std::printf("CIRCLE(B): Pneumatics\n\t0:Shifters\n\t1:Clamp\n\t2:Digital Input\n");
    std::printf("SQUARE(X): Sensors\n\t0: Digital Switch\n\t1: Left Encoder\n\t2:Right Encoder\n\t3:Analog Ultrasonic\n\t4:Digital Ultrasonic\n\t5:Infared\n");
    std::printf("X(A): MOTORS\n\t0: Drivetrain\n\t1: Talon 1\n\t2: Talon 2\n\t3: Talon 3\n\t4: Talon 4\n\n\t5: Grabber\n\t6: Compressor (Start to override safety)\n");
}
void robot_class::getButtons()
{
    if (driverJoy->GetRawButton(BUTTON_X))
    {
        button = SENSORS;
        std::printf("SENSORS\n");
        selection = sense->previousSense*10;
        motors->compressor->Set(Relay::kOff);
    }
    if (driverJoy->GetRawButton(BUTTON_A))
    {
        button = MOTORS;
        std::printf("MOTORS\n");
        selection = motors->previousMotor*10;
        motors->compressor->Set(Relay::kOff);
    }
    else if (driverJoy->GetRawButton(BUTTON_B))
    {
        button = PNEUMATICS;
        std::printf("PNEUMATICS\n");
        selection = pneumatics->prevPnum*10;
    }
    else if (driverJoy->GetRawButton(BUTTON_Y))
    {
        printStuff();
    }
    if (driverJoy->GetRawButton(BUTTON_R1))
    {
        selection++;
        //std::printf("INCREMENT\n");
        if (button == MOTORS)
        {
            motors->disable();
        }
    }
    else if (driverJoy->GetRawButton(BUTTON_L1))
    {
        selection--;
        //std::printf("DECREMENT\n");
        if (button == MOTORS)
        {
            motors->disable();
        }
    }
    /*
    else if (driverJoy->GetRawButton(BUTTON_L2))
    {
        speed = speed + 0.02;
        std::printf("Jag Speed: %f \n", speed);
    }
    else if (driverJoy->GetRawButton(BUTTON_R2))
    {
        speed = speed - 0.02;
        std::printf("Jag Speed: %f \n", speed);
    }
    */
}

START_ROBOT_CLASS(robot_class)
