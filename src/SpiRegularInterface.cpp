#include <phpcpp.h>
#include <stdint.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "SpiRegularInterface.hpp"

void SpiRegularInterface::__construct(Php::Parameters &params)
{
    int _channel = params[0];
    int _speed = params[1];
    int _flags = 0;
    if (params.size() > 2) {
        _flags = params[2];
    }

    if (_channel < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <channel> parameter"); return;}
    if (_speed < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <speed> parameter"); return;}
    if (_flags < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <flags> parameter"); return;}

    channel = _channel;
    speed = _speed;
    flags = _flags;

    if (BerrySpiState::getPigpioInitRc() < 0) {
        std::string message = "Pigpio initialization failed with RC=";
        message = message + std::to_string(BerrySpiState::getPigpioInitRc());
        BerrySpiExceptions::GpioInitFailureException(message.c_str());
        return;
    }
}

void SpiRegularInterface::open()
{
}

void SpiRegularInterface::close()
{
    if (handle == -1) {
        BerrySpiExceptions::LogicException("Unable to close an unestablished device connection");
        return;
    }
}

Php::Value SpiRegularInterface::getChannel() const { return (int16_t) channel; }
Php::Value SpiRegularInterface::getSpeed() const { return (int16_t) speed; }
Php::Value SpiRegularInterface::getFlags() const { return (int16_t) flags; }
