#include "AbstractSpiInterface.hpp"

#ifndef SPI_BIT_BANGING_INTERFACE_H
#define SPI_BIT_BANGING_INTERFACE_H

class SpiBitBangingInterface: public AbstractSpiInterface
{
private:
    /** The GPIO (0-31) used for the slave select signal */
    unsigned csPin;

    /** The GPIO (0-31) used for the MISO signal */
    unsigned misoPin;

    /** The GPIO (0-31) used for the MOSI signal */
    unsigned mosiPin;

    /** The GPIO (0-31) used for the SCLK signal */
    unsigned sclkPin;

protected:
    virtual int openDevice();
    virtual int closeDevice();
    virtual int crossTransfer(char* inBuffer, char* outBuffer, unsigned byteCount);

public:
    SpiBitBangingInterface() = default;
    virtual ~SpiBitBangingInterface() = default;

    void __construct(Php::Parameters &params);
    Php::Value getCsPin() const;
    Php::Value getMisoPin() const;
    Php::Value getMosiPin() const;
    Php::Value getSclkPin() const;

    void open() {AbstractSpiInterface::open();};
    void close() {AbstractSpiInterface::close();};
    Php::Value transfer(Php::Parameters &params) {return AbstractSpiInterface::transfer(params);};
    Php::Value getSpeed() const {return AbstractSpiInterface::getSpeed();};
    Php::Value getFlags() const {return AbstractSpiInterface::getFlags();};
    Php::Value isOpen() const {return AbstractSpiInterface::isOpen();};
};

#endif