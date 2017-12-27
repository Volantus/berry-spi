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