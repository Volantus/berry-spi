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

public:
    SpiRegularInterface() = default;
    virtual ~SpiRegularInterface() = default;

    void __construct(Php::Parameters &params);
    void open();
    void close();
    Php::Value transfer(Php::Parameters &params);
    Php::Value read(Php::Parameters &params);
    int write(Php::Parameters &params);

    Php::Value getChannel() const;
    Php::Value getSpeed() const;
    Php::Value getFlags() const;
    Php::Value isOpen() const;
};

#endif