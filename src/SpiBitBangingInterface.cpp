#include <phpcpp.h>
#include <stdint.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "AbstractSpiInterface.hpp"
#include "SpiBitBangingInterface.hpp"

void SpiBitBangingInterface::__construct(Php::Parameters &params)
{
    if (!constructBaseParameters(params[4], params[5])) {return;};

    int _csPin = params[0];
    int _misoPin = params[1];
    int _mosiPin = params[2];
    int _sclkPin = params[3];

    if (_csPin < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <csPin> parameter"); return;}
    if (_misoPin < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <misoPin> parameter"); return;}
    if (_mosiPin < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <mosiPin> parameter"); return;}
    if (_sclkPin < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <sclkPin> parameter"); return;}

    csPin = _csPin;
    misoPin = _misoPin;
    mosiPin = _mosiPin;
    sclkPin = _sclkPin;
}

int SpiBitBangingInterface::openDevice()
{
    return bbSPIOpen(csPin, misoPin, mosiPin, sclkPin, speed, flags);
}

int SpiBitBangingInterface::closeDevice()
{
    return bbSPIClose(csPin);
}

int SpiBitBangingInterface::crossTransfer(char* inBuffer, char* outBuffer, unsigned byteCount)
{
    return bbSPIXfer(csPin, outBuffer, inBuffer, byteCount);
}

bool SpiBitBangingInterface::validateOpen(int returnCode)
{
    if (returnCode >= 0) {
        return true;
    }

    switch (returnCode) {
        case PI_BAD_USER_GPIO:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => on of the given pins is invalid (PI_BAD_USER_GPIO)");
            return false;
        case PI_BAD_SPI_BAUD:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => bad SPI baud rate (speed), probably not 50-500k (PI_BAD_SPI_BAUD)");
            return false;
        case PI_GPIO_IN_USE:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => GPIO is already in use (PI_GPIO_IN_USE)");
            return false;
    }

    return AbstractSpiInterface::validateOpen(returnCode);
}

bool SpiBitBangingInterface::validateClose(int returnCode)
{
    if (returnCode >= 0) {
        return true;
    }

    switch (returnCode) {
        case PI_BAD_USER_GPIO:
            BerrySpiExceptions::RuntimeException("Closing SPI device failed => internal extension failure (PI_BAD_USER_GPIO)");
            return false;
        case PI_NOT_SPI_GPIO:
            BerrySpiExceptions::RuntimeException("Closing SPI device failed => internal extension failure (PI_NOT_SPI_GPIO)");
            return false;
    }

    return AbstractSpiInterface::validateClose(returnCode);
}

bool SpiBitBangingInterface::validateTransfer(int returnCode, int transferCount)
{
    if (returnCode >= 0) {
        return true;
    }

    switch (returnCode) {
        case PI_BAD_USER_GPIO:
            BerrySpiExceptions::RuntimeException("Closing SPI device failed => internal extension failure (PI_BAD_USER_GPIO)");
            return false;
        case PI_NOT_SPI_GPIO:
            BerrySpiExceptions::RuntimeException("Closing SPI device failed => internal extension failure (PI_NOT_SPI_GPIO)");
            return false;
        case PI_BAD_POINTER:
            BerrySpiExceptions::RuntimeException("Closing SPI device failed => internal extension failure (PI_BAD_POINTER)");
            return false;
    }

    return AbstractSpiInterface::validateTransfer(returnCode, transferCount);
}

Php::Value SpiBitBangingInterface::getCsPin() const { return (int16_t) csPin; }
Php::Value SpiBitBangingInterface::getMosiPin() const { return (int16_t) mosiPin; }
Php::Value SpiBitBangingInterface::getMisoPin() const { return (int16_t) misoPin; }
Php::Value SpiBitBangingInterface::getSclkPin() const { return (int16_t) sclkPin; }