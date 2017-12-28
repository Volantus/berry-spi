#include <pigpio.h>
#include <stdint.h>
#include <stdio.h>
#include "BerrySpiState.hpp"

int BerrySpiState::pigpioInitRc;

void BerrySpiState::initDependencies()
{
    pigpioInitRc = gpioInitialise();
    freopen("/dev/null", "w", stderr);
}

void BerrySpiState::cleanDependencies()
{
    gpioTerminate();
}

int BerrySpiState::getPigpioInitRc()
{
    return pigpioInitRc;
}

