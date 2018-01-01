#include <phpcpp.h>
#include <stdint.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "DeviceInteractionResult.hpp"
#include "AbstractSpiInterface.hpp"

bool AbstractSpiInterface::constructBaseParameters(int _speed, int _flags)
{
    if (_speed < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <speed> parameter"); return false;}
    if (_flags < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <flags> parameter"); return false;}

    speed = _speed;
    flags = _flags;
    handle = -1;

    if (BerrySpiState::getPigpioInitRc() < 0) {
        std::string message = "Pigpio initialization failed with RC=";
        message = message + std::to_string(BerrySpiState::getPigpioInitRc());
        BerrySpiExceptions::GpioInitFailureException(message.c_str());
        return false;
    }

    return true;
}

void AbstractSpiInterface::open()
{
    if (handle != -1) {
        BerrySpiExceptions::LogicException("SPI device is already opened"); return;
    }

    DeviceInteractionResult* result = openDevice();
    int rc = result->getReturnCode();

    if (result->isPhpExceptionThrown()) {return;}

    if (rc >= 0) {
        handle = rc; return;
    }

    switch (rc) {
        case PI_BAD_SPI_CHANNEL:
                BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid channel given (PI_BAD_SPI_CHANNEL)"); return;
        case PI_BAD_SPI_SPEED:
                BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid speed given (PI_BAD_SPI_SPEED)"); return;
        case PI_BAD_FLAGS:
                BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid flags given (PI_BAD_FLAGS)"); return;
        case PI_NO_AUX_SPI:
                BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => no aux (PI_NO_AUX_SPI)"); return;
        case PI_SPI_OPEN_FAILED:
                BerrySpiExceptions::RuntimeException("Opening SPI device failed => unknown error while opening device (PI_SPI_OPEN_FAILED)"); return;
        default:
            std::string message = "Opening SPI device failed => unknown RC " + std::to_string(rc) + " returned by spiOpen";
            BerrySpiExceptions::RuntimeException(message.c_str()); return;
    }
}

void AbstractSpiInterface::close()
{
    if (handle == -1) {
        BerrySpiExceptions::LogicException("Unable to close an unestablished device connection");
        return;
    }

    DeviceInteractionResult* result = closeDevice();
    int rc = result->getReturnCode();

    if (result->isPhpExceptionThrown()) {return;}

    if (rc == 0) {
        handle = -1;
    } else if (rc == PI_BAD_HANDLE) {
        BerrySpiExceptions::RuntimeException("Closing SPI device failed => bad handle (PI_BAD_HANDLE)"); return;
    } else if (rc != 0) {
        std::string message = "Closing SPI device failed => unknown RC " + std::to_string(rc) + " returned by spiClose";
        BerrySpiExceptions::RuntimeException(message.c_str()); return;
    }
}

Php::Value AbstractSpiInterface::transfer(Php::Parameters &params)
{
    CHECK_IF_OPEN

    std::string data = params[0];
    char * outBuffer = new char[data.size() + 1];
    std::copy(data.begin(), data.end(), outBuffer);
    outBuffer[data.size()] = '\0';

    unsigned count = data.length();
    char inBuffer[data.length()];

    DeviceInteractionResult* result = crossTransfer(inBuffer, outBuffer, count);
    if (result->isPhpExceptionThrown()) {return -1;}

    return handleTransferResult(result->getReturnCode(), (int) data.size(), count, inBuffer);
}

Php::Value AbstractSpiInterface::isOpen() const
{
    return handle != -1;
}

Php::Value AbstractSpiInterface::getSpeed() const { return (int16_t) speed; }
Php::Value AbstractSpiInterface::getFlags() const { return (int16_t) flags; }

Php::Value AbstractSpiInterface::handleTransferResult(int rc, int dataSize, unsigned transferCount, char inBuffer[])
{
    if (rc >= 0) {
        inBuffer[dataSize] = '\0';
        return (char *) inBuffer;
    }

    switch (rc) {
        case PI_BAD_SPI_CHANNEL:
            BerrySpiExceptions::RuntimeException("Transferring data failed  => bad handle (PI_BAD_HANDLE)"); return -1;
        case PI_BAD_SPI_COUNT:
             BerrySpiExceptions::RuntimeException("Transferring data failed  => bad spi count (PI_BAD_SPI_COUNT)"); return -1;
        case PI_SPI_XFER_FAILED:
            BerrySpiExceptions::RuntimeException("Transferring data failed  => unknown error (PI_SPI_XFER_FAILED)"); return -1;
        default:
            std::string message = "Transferring data failed => invalid RC " + std::to_string(rc) + " returned by SPI driver, expected" + std::to_string((int16_t) transferCount);
            BerrySpiExceptions::RuntimeException(message.c_str()); return -1;
    }
}
