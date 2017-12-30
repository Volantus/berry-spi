#ifndef BERRY_SPI_STAGE_H
#define BERRY_SPI_STAGE_H

class BerrySpiState
{
private:
    static int pigpioInitRc;

public:
    static void initDependencies();
    static void cleanDependencies();
    static int getPigpioInitRc();
};

#endif