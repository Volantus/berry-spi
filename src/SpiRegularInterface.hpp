#include "AbstractSpiInterface.hpp"

#ifndef SPI_REGULAR_INTERFACE_H
#define SPI_REGULAR_INTERFACE_H

class SpiRegularInterface: public AbstractSpiInterface
{
private:
    /**
     *  A SPI channel, 0-2.
     *  @var    unsigned
     */
    unsigned channel;

protected:
    virtual int openDevice();
    virtual int closeDevice();
    virtual int crossTransfer(char* inBuffer, char* outBuffer, unsigned byteCount);
    virtual bool validateOpen(int returnCode);
    virtual bool validateClose(int returnCode);
    virtual bool validateTransfer(int returnCode, int transferCount);

public:
    SpiRegularInterface() = default;
    virtual ~SpiRegularInterface() = default;

    void __construct(Php::Parameters &params);
    Php::Value read(Php::Parameters &params);
    void write(Php::Parameters &params);
    Php::Value getChannel() const;

    void open() {AbstractSpiInterface::open();};
    void close() {AbstractSpiInterface::close();};
    Php::Value transfer(Php::Parameters &params) {return AbstractSpiInterface::transfer(params);};
    Php::Value getSpeed() const {return AbstractSpiInterface::getSpeed();};
    Php::Value getFlags() const {return AbstractSpiInterface::getFlags();};
    Php::Value isOpen() const {return AbstractSpiInterface::isOpen();};
};

#endif