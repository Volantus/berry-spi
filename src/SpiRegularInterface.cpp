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
    handle = -1;

    if (BerrySpiState::getPigpioInitRc() < 0) {
        std::string message = "Pigpio initialization failed with RC=";
        message = message + std::to_string(BerrySpiState::getPigpioInitRc());
        BerrySpiExceptions::GpioInitFailureException(message.c_str());
        return;
    }
}

void SpiRegularInterface::open()
{
    if (handle != -1) {
        BerrySpiExceptions::LogicException("SPI device is already opened"); return;
    }

    int rc = spiOpen(channel, speed, flags);

    if (rc >= 0) {
        handle = rc;
    } else if (rc == PI_BAD_SPI_CHANNEL) {
        BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid channel given (PI_BAD_SPI_CHANNEL)"); return;
    } else if (rc == PI_BAD_SPI_SPEED) {
        BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid speed given (PI_BAD_SPI_SPEED)"); return;
    } else if (rc == PI_BAD_FLAGS) {
        BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid flags given (PI_BAD_FLAGS)"); return;
    } else if (rc == PI_NO_AUX_SPI) {
        BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => no aux (PI_NO_AUX_SPI)"); return;
    } else if (rc == PI_SPI_OPEN_FAILED) {
        BerrySpiExceptions::GpioFailureException("Opening SPI device failed => unknown error while opening device (PI_SPI_OPEN_FAILED)"); return;
    } else {
        std::string message = "Opening SPI device failed => unknown RC " + std::to_string(rc) + " returned by spiOpen";
        BerrySpiExceptions::RuntimeException(message.c_str()); return;
    }
}

void SpiRegularInterface::close()
{
    if (handle == -1) {
        BerrySpiExceptions::LogicException("Unable to close an unestablished device connection");
        return;
    }

    int rc = spiClose(handle);

    if (rc == 0) {
        handle = -1;
    } else if (rc == PI_BAD_HANDLE) {
        BerrySpiExceptions::GpioFailureException("Closing SPI device failed => bad handle (PI_BAD_HANDLE)"); return;
    } else if (rc != 0) {
        std::string message = "Closing SPI device failed => unknown RC " + std::to_string(rc) + " returned by spiClose";
        BerrySpiExceptions::RuntimeException(message.c_str()); return;
    }
}

Php::Value SpiRegularInterface::isOpen() const
{
    return handle != -1;
}

Php::Value SpiRegularInterface::getChannel() const { return (int16_t) channel; }
Php::Value SpiRegularInterface::getSpeed() const { return (int16_t) speed; }
Php::Value SpiRegularInterface::getFlags() const { return (int16_t) flags; }
