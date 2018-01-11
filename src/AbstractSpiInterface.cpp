#include <phpcpp.h>
#include <stdint.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "AbstractSpiInterface.hpp"
#include "TransmitBuffer.hpp"

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

    int rc = openDevice();
    if (validateOpen(rc)) {
        handle = rc;
    }
}

void AbstractSpiInterface::close()
{
    if (handle == -1) {
        BerrySpiExceptions::LogicException("Unable to close an unestablished device connection");
        return;
    }

    int rc = closeDevice();
    if (validateClose(rc)) {
        handle = -1;
    }
}

Php::Value AbstractSpiInterface::transfer(Php::Parameters &params)
{
    CHECK_IF_OPEN(-1)

    TransmitBuffer* txBuffer = new TransmitBuffer(params[0]);
    if (!txBuffer->isValid()) {
        delete txBuffer;
        return false;
    }

    char rxBuffer[txBuffer->getLength() + 1];

    int rc = crossTransfer(rxBuffer, txBuffer->getData(), txBuffer->getWordCount());
    Php::Value returnData = handleTransferResult(rc, txBuffer->getLength(), txBuffer->getWordCount(), rxBuffer);
    delete txBuffer;

    return returnData;
}

Php::Value AbstractSpiInterface::isOpen() const
{
    return handle != -1;
}

Php::Value AbstractSpiInterface::handleTransferResult(int rc, int dataSize, unsigned transferCount, char inBuffer[])
{
    if (validateTransfer(rc, transferCount)) {
        inBuffer[dataSize] = '\0';
        Php::Value returnArray;

        for (int i = 0; i < dataSize; i++) {
            returnArray[i] = inBuffer[i];
        }

        return returnArray;
    }

    return false;
}

bool AbstractSpiInterface::validateOpen(int returnCode)
{
    if (returnCode >= 0) {
        return true;
    }

    switch (returnCode) {
        case PI_BAD_SPI_SPEED:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid speed given (PI_BAD_SPI_SPEED)");
            return false;
        case PI_BAD_FLAGS:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid flags given (PI_BAD_FLAGS)");
            return false;
        case PI_SPI_OPEN_FAILED:
            BerrySpiExceptions::RuntimeException("Opening SPI device failed => unknown error while opening device (PI_SPI_OPEN_FAILED)");
            return false;
        default:
            std::string message = "Opening SPI device failed => unknown RC " + std::to_string(returnCode) + " returned by spiOpen";
            BerrySpiExceptions::RuntimeException(message.c_str());
            return false;
    }
}

bool AbstractSpiInterface::validateClose(int returnCode)
{
    if (returnCode == 0) {
        return true;
    }

    std::string message = "Closing SPI device failed => unknown RC " + std::to_string(returnCode) + " returned by spiClose";
    BerrySpiExceptions::RuntimeException(message.c_str());
    return false;
}

bool AbstractSpiInterface::validateTransfer(int returnCode, int transferCount)
{
    if (returnCode >= 0) {
        return true;
    }

    switch (returnCode) {
        case PI_BAD_SPI_COUNT:
             BerrySpiExceptions::RuntimeException("Transferring data failed  => bad spi count (PI_BAD_SPI_COUNT)");
             return false;
        case PI_SPI_XFER_FAILED:
            BerrySpiExceptions::RuntimeException("Transferring data failed  => unknown error (PI_SPI_XFER_FAILED)");
            return false;
        default:
            std::string message = "Transferring data failed => invalid RC " + std::to_string(returnCode) + " returned by SPI driver, expected" + std::to_string((int16_t) transferCount);
            BerrySpiExceptions::RuntimeException(message.c_str());
            return false;
    }
}

Php::Value AbstractSpiInterface::getSpeed() const { return (int16_t) speed; }
Php::Value AbstractSpiInterface::getFlags() const { return (int16_t) flags; }