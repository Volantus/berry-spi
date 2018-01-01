#include <phpcpp.h>
#include <stdint.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "AbstractSpiInterface.hpp"
#include "DeviceInteractionResult.hpp"
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

DeviceInteractionResult* SpiBitBangingInterface::openDevice()
{
    return new DeviceInteractionResult(1, false);
}

DeviceInteractionResult* SpiBitBangingInterface::closeDevice()
{
    return new DeviceInteractionResult(1, false);
}

DeviceInteractionResult* SpiBitBangingInterface::crossTransfer(char* inBuffer, char* outBuffer, unsigned byteCount)
{
    return new DeviceInteractionResult(1, false);
}

Php::Value SpiBitBangingInterface::getCsPin() const { return (int16_t) csPin; }
Php::Value SpiBitBangingInterface::getMosiPin() const { return (int16_t) mosiPin; }
Php::Value SpiBitBangingInterface::getMisoPin() const { return (int16_t) misoPin; }
Php::Value SpiBitBangingInterface::getSclkPin() const { return (int16_t) sclkPin; }