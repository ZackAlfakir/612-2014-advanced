#include "Pneumatics.h"
#include "main.h"
//#include <Relay.h>

Pneumatics::Pneumatics()
{
    shift1 = new DoubleSolenoid(7,8);
    clamp = new DoubleSolenoid(5,6);
    piston = new DoubleSolenoid(3,4); //TODO NOT REAL PORTS
    
//     compressor = new Relay(PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
//     digiSwitch = new DigitalInput(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL);
    
    filename = "Pneumatics.txt";
    fp = new FileProcessor(filename, rw);
    curInfo = new char[256];
    prevPnum = 0;
}

void Pneumatics::runPneumatics(int pnum)
{
//     bool isNotified = false;
    pressurize();
    unsigned long int prevVal = 0;
    if (pnum == 0)
    {
        toggleSolenoid(shift1);
        if (prevPnum != pnum)
        {
            snprintf(curInfo, 100, "Shift Solenoid\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
    }
    else if (pnum == 1)
    {
        toggleSolenoid(clamp);
        if (prevPnum != pnum)
        {
            snprintf(curInfo, 100, "Clamp Solenoid\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
    }
    else if (pnum == 2)
    {
        static int count = 0;
        if (count % 50 == 0)
        {
            if (robot->sense->pnumSwitch->Get() != prevVal)
            { 
                snprintf(curInfo, 100, "DigitalInput: %ld\n", robot->sense->pnumSwitch->Get());
                std::printf("%s", curInfo);
                fp->write(curInfo);
                
            }
        }
        count++;
    }
    else if (pnum == 3)
    {
        toggleSolenoid(piston);
        if (prevPnum = pnum)
        {
            snprintf(curInfo, 100, "!!Piston!!\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
        }
    }
    else if(pnum >= 4)
    {
        snprintf(curInfo, 100, "MAX");
        std::printf("%s", curInfo);
        fp->write(curInfo);
        robot->selection = 30;
    }
    prevPnum = pnum;
}
void Pneumatics::toggleSolenoid(DoubleSolenoid* sol)
{
    axis = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    static DoubleSolenoid::Value solToggled = DoubleSolenoid::kOff;
    if (axis > JOYSTICK_ZERO_TOLERANCE)
    {
        sol->Set(DoubleSolenoid::kForward);
        if (solToggled != DoubleSolenoid::kForward)
        {
            snprintf(curInfo, 100, "Solenoid Forward\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            solToggled = DoubleSolenoid::kForward;
        }
    }
    else if (axis < JOYSTICK_ZERO_TOLERANCE*-1)
    {
        sol->Set(DoubleSolenoid::kReverse);
        if (solToggled != DoubleSolenoid::kReverse)
        {
            snprintf(curInfo, 100, "Solenoid Reverse\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            solToggled = DoubleSolenoid::kReverse;
        }
    }
    else
    {
        sol->Set(DoubleSolenoid::kOff);
        if (solToggled != DoubleSolenoid::kOff)
        {
            snprintf(curInfo, 100, "Solenoid Off\n");
            std::printf("%s", curInfo);
            fp->write(curInfo);
            solToggled = DoubleSolenoid::kOff;
        }
    }
}
void Pneumatics::pressurize()
{
    if (robot->sense->pnumSwitch->Get() == 0)
    {
        robot->motors->compressor->Set(Relay::kForward);
    }
    else
    {
        robot->motors->compressor->Set(Relay::kOff);
    }
}

