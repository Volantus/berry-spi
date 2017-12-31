<?php
namespace Volantus\BerrySpi;

/**
 * Class SPIInterface
 *
 * @package Volantus\BerrySpi
 */
class RegularInterface
{
    /**
     * SPIInterface constructor.
     *
     * @param int $channel Regular SPI channel (0 or 1)
     * @param int $speed   Baud speed in bits per second
     *                     32K-125M (values above 30M are unlikely to work)
     * @param int $flags   Additional flags
     */
    public function __construct(int $channel, int $speed, int $flags)
    {
    }

    /**
     * @return void
     */
    public function open()
    {
    }

    /**
     * @return void
     */
    public function close()
    {
    }

    /**
     * @return int
     */
    public function getChannel(): int
    {
    }

    /**
     * @return int
     */
    public function getSpeed(): int
    {
    }

    /**
     * @return int
     */
    public function getFlags(): int
    {
    }

    /**
     * @return bool True if SPI device connection is open
     */
    public function isOpen(): bool
    {
    }

    /**
     * Transfers data to SPI device.
     * Simultaneously same byte count of data is read from the device and returned.
     *
     * @param string $data Data to send to device
     *
     * @return string data received by the SPI device
     */
    public function transfer(string $data): string
    {
    }

    /**
     * Reads count bytes of data from the SPI device
     *
     * @param int $count Count of bytes to read
     *
     * @return string data read by the SPI device
     */
    public function read(int $count): string
    {
    }

    /**
     * Sends data to the SPI device
     *
     * @param string $data
     */
    public function write(string $data)
    {
    }
}

/**
 * Class BitBangingInterface
 *
 * @package Volantus\BerrySpi
 */
class BitBangingInterface
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
     */
    public function __construct(int $csPin, int $misoPin, int $mosiPin, int $sclkPin, int $speed, int $flags)
    {
        $this->csPin = $csPin;
        $this->misoPin = $misoPin;
        $this->mosiPin = $mosiPin;
        $this->sclkPin = $sclkPin;
    }

    /**
     * @return void
     */
    public function open()
    {
    }

    /**
     * @return void
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
     * @return int
     */
    public function getSpeed(): int
    {
    }

    /**
     * @return int
     */
    public function getFlags(): int
    {
    }

    /**
     * @return bool True if SPI device connection is open
     */
    public function isOpen(): bool
    {
    }

    /**
     * Transfers data to SPI device.
     * Simultaneously same byte count of data is read from the device and returned.
     *
     * @param string $data Data to send to device
     *
     * @return string data received by the SPI device
     */
    public function transfer(string $data): string
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
class GpioFailureException extends \Exception
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