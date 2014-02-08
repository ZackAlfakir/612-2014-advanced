#include <DoubleSolenoid.h>
#include "main.h"
#include "612.h"
#include "Shift.h"
#include "SmoothJoystick.h"
#include "Controls.h"

Shift::Shift(uint8_t shiftMod, uint32_t forwardChan,uint32_t reverseChan):timer()
{
    SmoothJoystick* joy = robot->driverJoy;
    joy -> pushBtn(SHIFT_LOW, (void*)this, &eventHandler);
    joy -> pushBtn(SHIFT_HIGH, (void*)this, &eventHandler);
    
    
    shift = new DoubleSolenoid(shiftMod,forwardChan, reverseChan);
    //make it default high gear to avoid it being bumped in between gears
    //shift -> Set(DoubleSolenoid::kForward);
    timer.Start();
    gear = HIGH;
    
}

Shift::~Shift()
{
}

void Shift::eventHandler(void* o,unsigned int btn) {
    Shift* sh = (Shift*)o;
    if(btn==SHIFT_LOW) {
        sh->shiftLow();
    } else {
        sh->shiftHigh();
    }
}

void Shift::shiftGear()
{
    printf("-=SHIFTING=-\n");
    if (gear==HIGH)
    {
        shiftLow();
    }
    else
    {
        shiftHigh();
    }
    timer.Reset();
}
void Shift::shiftLow()
{
    //shift -> Set(DoubleSolenoid::kReverse);
    robot->pnum->addSolenoid(0.15, shift, DoubleSolenoid::kReverse);
    gear = LOW;
}
void Shift::shiftHigh()
{
    //shift -> Set(DoubleSolenoid::kForward);
    robot->pnum->addSolenoid(0.15, shift, DoubleSolenoid::kForward);
    gear = HIGH;
}

