class SpiRegularInterface : public Php::Base
{
private:
    /**
     *  Handle for the device at the address on the SPI bus.
     *  @var    unsigned
     */
    int handle = -1;

    /**
     *  A SPI channel, 0-2.
     *  @var    unsigned
     */
    unsigned channel;

    /**
     *  The speed of serial communication in bits per second.
     *  @var    unsigned
     */
    unsigned speed;

    /**
     *  Consists of the least significant 22 bits.
     *  @var    unsigned
     */
    unsigned flags;

public:
    SpiRegularInterface() = default;
    virtual ~SpiRegularInterface() = default;

    void __construct(Php::Parameters &params);
    void open();
    void close();

    Php::Value getChannel() const;
    Php::Value getSpeed() const;
    Php::Value getFlags() const;
    Php::Value isOpen() const;
};