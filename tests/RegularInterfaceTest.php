<?php
namespace Volantus\BerrySpi\Tests;

use PHPUnit\Framework\TestCase;
use Volantus\BerrySpi\RegularInterface;

/**
 * Class RegularInterfaceTest
 *
 * @package Volantus\BerrySpi\Tests
 */
class RegularInterfaceTest extends TestCase
{
    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <channel> parameter
     */
    public function test_construct_negativeChannel()
    {
        new RegularInterface(-1, 32000, 0);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <speed> parameter
     */
    public function test_construct_negativeSpeed()
    {
        new RegularInterface(1, -1, 0);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <flags> parameter
     */
    public function test_construct_negativeFlags()
    {
        new RegularInterface(1, 32000, -1);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage Opening SPI device failed => invalid channel given (PI_BAD_SPI_CHANNEL)
     */
    public function test_open_invalidChannel()
    {
        $interface = new RegularInterface(3, 32000, 0);
        $interface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage Opening SPI device failed => invalid speed given (PI_BAD_SPI_SPEED)
     */
    public function test_open_invalidSpeed()
    {
        $interface = new RegularInterface(1, 1, 0);
        $interface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage Opening SPI device failed => invalid flags given (PI_BAD_FLAGS)
     */
    public function test_open_invalidFlags()
    {
        $interface = new RegularInterface(1, 32000, 9999999);
        $interface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\LogicException
     * @expectedExceptionMessage SPI device is already open
     */
    public function test_open_alreadyOpen()
    {
        $interface = new RegularInterface(1, 32000, 0);
        $interface->open();
        $interface->open();
    }

    public function test_getChannel_correct()
    {
        $interface = new RegularInterface(2, 32000, 0);
        self::assertEquals(2, $interface->getChannel());
    }

    public function test_getSpeed_correct()
    {
        $interface = new RegularInterface(2, 32000, 0);
        self::assertEquals(32000, $interface->getSpeed());
    }

    public function test_getFlags_correct()
    {
        $interface = new RegularInterface(2, 32000, 16);
        self::assertEquals(16, $interface->getFlags());
    }
}