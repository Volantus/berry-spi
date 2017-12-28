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
     * @param string $data  Data to send to device
     *
     * @return string
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