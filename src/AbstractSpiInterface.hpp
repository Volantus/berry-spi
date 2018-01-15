#ifndef ABSTRACT_SPI_INTERFACE_H
#define ABSTRACT_SPI_INTERFACE_H

#define CHECK_IF_OPEN(rv)   if (handle == -1) {\
                              BerrySpiExceptions::LogicException("Unable to transfer data via an unestablished device connection");\
                              return rv;\
                            }

class AbstractSpiInterface: public Php::Base
{
protected:
    /* The speed of serial communication in bits per second. */
    unsigned speed;

    /* Consists of the least significant 22 bits. */
    unsigned flags;

    /*  Internal pigpio device handle */
    int handle;

    /* Handles return of all device I/O operations */
    Php::Value handleTransferResult(int rc, int dataSize, unsigned transferCount, char inBuffer[]);

    /* Validates the return code received while opening the device */
    virtual bool validateOpen(int returnCode);

    /* Validates the return code received while closing the device */
    virtual bool validateClose(int returnCode);

    /* Validates the return code received while transferring data */
    virtual bool validateTransfer(int returnCode, int transferCount);

    /**
    *   Executes the real commands for opening the device connection.
    *   Has to return the pigpio return code
    */
    virtual int openDevice() = 0;

    /**
    *   Executes the real commands for closing the device connection.
    *   Has to return the pigpio return code
    */
    virtual int closeDevice() = 0;

    /**
    *   Executes the real commands for device cross (read + write) transfer.
    *   Has to return the pigpio return code
    */
    virtual int crossTransfer(char* inBuffer, char* outBuffer, unsigned byteCount) = 0;

public:
    AbstractSpiInterface() = default;
    virtual ~AbstractSpiInterface() = default;

    /* Constructs and validates the base parameters */
    bool constructBaseParameters(int _speed, int _flags);

    /* Initializes the Pigpio library */
    static Php::Value initialize();

    /* Abstracted API function for opening the device, will call openDevice */
    void open();

    /* Abstracted API function for closing the device, will call closeDevice */
    void close();

    /* Abstracted API function for cross transfer, will call crossTransfer */
    Php::Value transfer(Php::Parameters &params);

    static Php::Value isInitialized();
    Php::Value getSpeed() const;
    Php::Value getFlags() const;
    Php::Value isOpen() const;
};
#endif