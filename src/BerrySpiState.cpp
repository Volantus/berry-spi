#include <pigpio.h>
#include <stdint.h>
#include <stdio.h>
#include "BerrySpiState.hpp"

int BerrySpiState::pigpioInitRc;
bool BerrySpiState::initialized;

void BerrySpiState::startup()
{
    initialized = false;
}

void BerrySpiState::initDependencies()
{
    pigpioInitRc = gpioInitialise();
    initialized = true;
}

void BerrySpiState::cleanDependencies()
{
    gpioTerminate();
    initialized = false;
}

int BerrySpiState::getPigpioInitRc()
{
    return pigpioInitRc;
}

bool BerrySpiState::isInitialized()
{
    return initialized;
}