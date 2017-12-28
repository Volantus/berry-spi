#include <phpcpp.h>
#include <stdint.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "SpiRegularInterface.hpp"

#define CHECK_IF_OPEN     if (handle == -1) {\
                              BerrySpiExceptions::LogicException("Unable to transfer data via an unestablished device connection");\
                              return -1;\
                          }

#define HANDLE_TRANSFER_RESULT

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
        BerrySpiExceptions::RuntimeException("Closing SPI device failed => bad handle (PI_BAD_HANDLE)"); return;
    } else if (rc != 0) {
        std::string message = "Closing SPI device failed => unknown RC " + std::to_string(rc) + " returned by spiClose";
        BerrySpiExceptions::RuntimeException(message.c_str()); return;
    }
}

Php::Value SpiRegularInterface::transfer(Php::Parameters &params) const
{
    CHECK_IF_OPEN

    std::string data = params[0];
    char * outBuffer = new char[data.size() + 1];
    std::copy(data.begin(), data.end(), outBuffer);
    outBuffer[data.size()] = '\0';

    unsigned count = data.length();
    char inBuffer[data.length()];

    int rc = spiXfer(handle, outBuffer, (char *)inBuffer, count);
    return handleTransferResult(rc, (int) data.size(), count, inBuffer);
}

Php::Value SpiRegularInterface::read(Php::Parameters &params) const
{
    CHECK_IF_OPEN

    int _count = params[0];
    if (_count < 0) {
        BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <count> parameter"); return -1;
    }

    unsigned count = _count;
    char inBuffer[_count];

    int rc = spiRead(handle, (char *)inBuffer, count);
    return handleTransferResult(rc, count + 1, count, inBuffer);
}

int SpiRegularInterface::write(Php::Parameters &params) const
{
    CHECK_IF_OPEN

    std::string data = params[0];
    char * outBuffer = new char[data.size() + 1];
    std::copy(data.begin(), data.end(), outBuffer);
    outBuffer[data.size()] = '\0';

    unsigned count = data.length();
    char inBuffer[0];

    int rc = spiWrite(handle, outBuffer, count);
    handleTransferResult(rc, (int) data.size(), count, inBuffer);
    return 1;
}

Php::Value SpiRegularInterface::isOpen() const
{
    return handle != -1;
}

Php::Value SpiRegularInterface::getChannel() const { return (int16_t) channel; }
Php::Value SpiRegularInterface::getSpeed() const { return (int16_t) speed; }
Php::Value SpiRegularInterface::getFlags() const { return (int16_t) flags; }

Php::Value SpiRegularInterface::handleTransferResult(int rc, int dataSize, unsigned transferCount, char inBuffer[]) const
{
    if (rc >= 0) {
        inBuffer[dataSize] = '\0';
        return (char *) inBuffer;
    } else if (rc == PI_BAD_HANDLE) {
        BerrySpiExceptions::RuntimeException("Transferring data failed  => bad handle (PI_BAD_HANDLE)"); return -1;
    } else if (rc == PI_BAD_SPI_COUNT) {
        BerrySpiExceptions::RuntimeException("Transferring data failed  => bad spi count (PI_BAD_SPI_COUNT)"); return -1;
    } else if (rc == PI_SPI_XFER_FAILED) {
        BerrySpiExceptions::RuntimeException("Transferring data failed  => unknown error (PI_SPI_XFER_FAILED)"); return -1;
    } else {
        std::string message = "Transferring data failed => invalid RC " + std::to_string(rc) + " returned by SPI driver, expected" + std::to_string((int16_t) transferCount);
        BerrySpiExceptions::RuntimeException(message.c_str()); return -1;
    }
}
