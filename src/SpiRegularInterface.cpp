#include <phpcpp.h>
#include <stdint.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "TransmitBuffer.hpp"
#include "AbstractSpiInterface.hpp"
#include "SpiRegularInterface.hpp"

void SpiRegularInterface::__construct(Php::Parameters &params)
{
    if (!constructBaseParameters(params[1], params[2])) {return;};

    int _channel = params[0];
    if (_channel < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <channel> parameter"); return;}
    channel = _channel;
}

int SpiRegularInterface::openDevice()
{
    return spiOpen(channel, speed, flags);
}

int SpiRegularInterface::closeDevice()
{
    return spiClose(handle);
}

int SpiRegularInterface::crossTransfer(char* inBuffer, char* outBuffer, unsigned byteCount)
{
    return spiXfer(handle, outBuffer, inBuffer, byteCount);
}

Php::Value SpiRegularInterface::read(Php::Parameters &params)
{
    CHECK_IF_OPEN(-1);

    int _count = params[0];
    if (_count < 0) {
        BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <count> parameter"); return -1;
    }

    unsigned count = _count;
    char inBuffer[_count];

    int rc = spiRead(handle, (char *)inBuffer, count);
    return handleTransferResult(rc, count + 1, count, inBuffer);
}

void SpiRegularInterface::write(Php::Parameters &params)
{
    CHECK_IF_OPEN()

    TransmitBuffer* txBuffer = new TransmitBuffer(params[0]);
    if (!txBuffer->isValid()) {
        delete txBuffer;
        return;
    }
    char rxBuffer[0];

    int rc = spiWrite(handle, txBuffer->getData(), txBuffer->getWordCount());
    handleTransferResult(rc, txBuffer->getLength(), txBuffer->getWordCount(), rxBuffer);
    delete txBuffer;
}

bool SpiRegularInterface::validateOpen(int returnCode)
{
    if (returnCode >= 0) {
        return true;
    }

    switch (returnCode) {
        case PI_BAD_SPI_CHANNEL:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid channel given (PI_BAD_SPI_CHANNEL)");
            return false;
        case PI_NO_AUX_SPI:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => no aux (PI_NO_AUX_SPI)");
            return false;
    }

    return AbstractSpiInterface::validateOpen(returnCode);
}

bool SpiRegularInterface::validateClose(int returnCode)
{
    if (returnCode == 0) {
        return true;
    }

    if (returnCode == PI_BAD_HANDLE) {
        BerrySpiExceptions::RuntimeException("Closing SPI device failed => bad handle (PI_BAD_HANDLE)");
        return false;
    }

    return AbstractSpiInterface::validateClose(returnCode);
}


bool SpiRegularInterface::validateTransfer(int returnCode, int transferCount)
{
    if (returnCode >= 0) {
        return true;
    }

    if (returnCode == PI_BAD_SPI_CHANNEL) {
        BerrySpiExceptions::RuntimeException("Transferring data failed  => bad handle (PI_BAD_HANDLE)");
        return false;
    }

    return AbstractSpiInterface::validateTransfer(returnCode, transferCount);
}


Php::Value SpiRegularInterface::getChannel() const { return (int16_t) channel; }