#include <phpcpp.h>
#include <stdint.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "AbstractSpiInterface.hpp"
#include "DeviceInteractionResult.hpp"
#include "SpiRegularInterface.hpp"

void SpiRegularInterface::__construct(Php::Parameters &params)
{
    if (!constructBaseParameters(params[1], params[2])) {return;};

    int _channel = params[0];
    if (_channel < 0) {BerrySpiExceptions::InvalidArgumentException("No negative values allowed for <channel> parameter"); return;}
    channel = _channel;
}

DeviceInteractionResult* SpiRegularInterface::openDevice()
{
    int returnCode = spiOpen(channel, speed, flags);

    switch (returnCode) {
        case PI_BAD_SPI_CHANNEL:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => invalid channel given (PI_BAD_SPI_CHANNEL)");
            return new DeviceInteractionResult(returnCode, true);
        case PI_NO_AUX_SPI:
            BerrySpiExceptions::InvalidArgumentException("Opening SPI device failed => no aux (PI_NO_AUX_SPI)");
            return new DeviceInteractionResult(returnCode, true);
        default:
            return new DeviceInteractionResult(returnCode, false);
    }
}

DeviceInteractionResult* SpiRegularInterface::closeDevice()
{
    int returnCode = spiClose(handle);
    return new DeviceInteractionResult(returnCode, false);
}

DeviceInteractionResult* SpiRegularInterface::crossTransfer(char* inBuffer, char* outBuffer, unsigned byteCount)
{
    int returnCode = spiXfer(handle, outBuffer, inBuffer, byteCount);
    return new DeviceInteractionResult(returnCode, false);
}


Php::Value SpiRegularInterface::handleTransferResult(int rc, int dataSize, unsigned transferCount, char inBuffer[])
{
    if (rc == PI_BAD_SPI_CHANNEL) {
        BerrySpiExceptions::RuntimeException("Transferring data failed  => bad handle (PI_BAD_HANDLE)"); return -1;
    }

    return AbstractSpiInterface::handleTransferResult(rc, dataSize, transferCount, inBuffer);
}

Php::Value SpiRegularInterface::read(Php::Parameters &params)
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

int SpiRegularInterface::write(Php::Parameters &params)
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

Php::Value SpiRegularInterface::getChannel() const { return (int16_t) channel; }