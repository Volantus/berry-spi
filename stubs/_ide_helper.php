<?php
namespace Volantus\BerrySpi;

/**
 * Interface SpiInterface
 *
 * @package Volantus\BerrySpi
 */
interface SpiInterface
{

    /**
     * @return void
     *
     * @throws InvalidArgumentException
     * @throws LogicException
     * @throws RuntimeException
     */
    public function open();

    /**
     * @return void
     *
     * @throws LogicException
     * @throws RuntimeException
     */
    public function close();

    /**
     * @return int
     */
    public function getSpeed(): int;
    /**
     * @return int
     */
    public function getFlags(): int;

    /**
     * @return bool True if SPI device connection is open
     */
    public function isOpen(): bool;

    /**
     * Transfers data to SPI device.
     * Simultaneously same byte count of data is read from the device and returned.
     *
     * @param array $data Data to send to device
     *                    (One word/byte per array item)
     *
     * @return array data received by the SPI device
     *               (One word/byte per array item)
     *
     * @throws LogicException
     * @throws RuntimeException
     */
    public function transfer(array $data): array;
}

/**
 * Class SPIInterface
 *
 * @package Volantus\BerrySpi
 */
class RegularInterface implements SpiInterface
{
    /**
     * SPIInterface constructor.
     *
     * @param int $channel Regular SPI channel (0 or 1)
     * @param int $speed   Baud speed in bits per second
     *                     32K-125M (values above 30M are unlikely to work)
     * @param int $flags   Additional flags
     *
     * @throws InvalidArgumentException
     * @throws GpioInitException
     */
    public function __construct(int $channel, int $speed, int $flags)
    {
    }

    /**
     * @inheritdoc
     */
    public function open()
    {
    }

    /**
     * @inheritdoc
     */
    public function close()
    {
    }

    /**
     * @inheritdoc
     */
    public function getChannel(): int
    {
    }

    /**
     * @inheritdoc
     */
    public function getSpeed(): int
    {
    }

    /**
     * @inheritdoc
     */
    public function getFlags(): int
    {
    }

    /**
     * @inheritdoc
     */
    public function isOpen(): bool
    {
    }

    /**
     * @inheritdoc
     */
    public function transfer(array $data): array
    {
    }

    /**
     * Reads count bytes of data from the SPI device
     *
     * @param int $count Count of bytes to read
     *
     * @return array data read by the SPI device
     *
     * @throws InvalidArgumentException
     * @throws LogicException
     * @throws RuntimeException
     */
    public function read(int $count): array
    {
    }

    /**
     * Sends data to the SPI device
     *
     * @param array $data
     *
     * @throws LogicException
     * @throws RuntimeException
     */
    public function write(array $data)
    {
    }
}

/**
 * Class BitBangingInterface
 *
 * @package Volantus\BerrySpi
 */
class BitBangingInterface implements SpiInterface
{
    /**
     * SPIInterface constructor.
     *
     * @param int $csPin   The GPIO (0-31) used for the slave select signal
     * @param int $misoPin The GPIO (0-31) used for the MISO signal
     * @param int $mosiPin The GPIO (0-31) used for the MOSI signal
     * @param int $sclkPin The GPIO (0-31) used for the SCLK signal
     * @param int $speed   Baud speed in bits per second (50-250000)
     * @param int $flags   Additional flags
     *
     * @internal param int $channel Regular SPI channel (0 or 1)
     *
     * @throws InvalidArgumentException
     * @throws GpioInitException
     */
    public function __construct(int $csPin, int $misoPin, int $mosiPin, int $sclkPin, int $speed, int $flags)
    {
    }

    /**
     * @inheritdoc
     */
    public function open()
    {
    }

    /**
     * @inheritdoc
     */
    public function close()
    {
    }

    /**
     * @return int
     */
    public function getCsPin(): int
    {
    }

    /**
     * @return int
     */
    public function getMosiPin(): int
    {
    }

    /**
     * @return int
     */
    public function getMisoPin(): int
    {
    }

    /**
     * @return int
     */
    public function getSclkPin(): int
    {
    }

    /**
     * @inheritdoc
     */
    public function getSpeed(): int
    {
    }

    /**
     * @inheritdoc
     */
    public function getFlags(): int
    {
    }

    /**
     * @inheritdoc
     */
    public function isOpen(): bool
    {
    }

    /**
     * @inheritdoc
     */
    public function transfer(array $data): array
    {
    }
}

/**
 * Class InvalidArgumentException
 *
 * @package Volantus\BerrySpi
 */
class InvalidArgumentException extends \Exception
{
}

/**
 * Class GpioInitException
 *
 * @package Volantus\BerrySpi
 */
class GpioInitException extends \Exception
{
}

/**
 * Class LogicException
 *
 * @package Volantus\BerrySpi
 */
class LogicException extends \Exception
{
}

/**
 * Class GpioFailureException
 *
 * @package Volantus\BerrySpi
 */
class RuntimeException extends \Exception
{
}