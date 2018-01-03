<?php
namespace Volantus\BerrySpi\Tests;

use Volantus\BerrySpi\RegularInterface;
use Volantus\BerrySpi\SpiInterface;

/**
 * Class RegularInterfaceTest
 *
 * @package Volantus\BerrySpi\Tests
 */
class RegularInterfaceTest extends SpiInterfaceTestCase
{
    public function test_implements_spiInterface()
    {
        $interface = new RegularInterface(1, 32000, 0);
        self::assertInstanceOf(SpiInterface::class, $interface);
    }

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
        $this->interface = new RegularInterface(3, 32000, 0);
        $this->interface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage Opening SPI device failed => invalid speed given (PI_BAD_SPI_SPEED)
     */
    public function test_open_invalidSpeed()
    {
        $this->interface = new RegularInterface(1, 1, 0);
        $this->interface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage Opening SPI device failed => invalid flags given (PI_BAD_FLAGS)
     */
    public function test_open_invalidFlags()
    {
        $this->interface = new RegularInterface(1, 32000, 9999999);
        $this->interface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\LogicException
     * @expectedExceptionMessage SPI device is already open
     */
    public function test_open_alreadyOpen()
    {
        $this->interface = new RegularInterface(1, 32000, 0);
        $this->interface->open();
        $this->interface->open();
    }

    public function test_open_deviceOpened()
    {
        $this->interface = new RegularInterface(1, 32000, 0);
        $this->interface->open();

        self::assertTrue($this->interface->isOpen());
    }

    /**
     * @expectedException \Volantus\BerrySpi\LogicException
     * @expectedExceptionMessage Unable to close an unestablished device connection
     */
    public function test_close_notOpen()
    {
        $interface = new RegularInterface(1, 32000, 0);
        $interface->close();
    }

    public function test_close_deviceClosed()
    {
        $interface = new RegularInterface(1, 32000, 0);
        $interface->open();
        $interface->close();

        self::assertFalse($interface->isOpen());
    }

    /**
     * @expectedException \Volantus\BerrySpi\LogicException
     * @expectedExceptionMessage Unable to transfer data via an unestablished device connection
     */
    public function test_transfer_notOpened()
    {
        $interface = new RegularInterface(1, 32000, 0);
        $interface->transfer('abc');
    }

    /**
     * For this test SPI_MISO (GPIO09) and SPI_MOSI (GPIO10) pins needs to be connected (e.g. jumper cable)
     */
    public function test_transfer_dataSendIsRead()
    {
        $this->interface = new RegularInterface(1, 32000, 0);
        $this->interface->open();
        $readData = $this->interface->transfer('abc');

        self::assertEquals('abc', $readData, 'Check if SPI_MISO (GPIO09) and SPI_MOSI (GPIO10) are connected properly');
    }

    /**
     * @expectedException \Volantus\BerrySpi\LogicException
     * @expectedExceptionMessage Unable to transfer data via an unestablished device connection
     */
    public function test_read_noOpen()
    {
        $interface = new RegularInterface(1, 32000, 0);
        $interface->read(3);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <count> parameter
     */
    public function test_read_negativeCountGiven()
    {
        $this->interface = new RegularInterface(1, 32000, 0);
        $this->interface->open();
        $this->interface->read(-3);
    }

    /**
     * @expectedException \Volantus\BerrySpi\LogicException
     * @expectedExceptionMessage Unable to transfer data via an unestablished device connection
     */
    public function test_write_noOpen()
    {
        $interface = new RegularInterface(1, 32000, 0);
        $interface->write('abc');
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

    public function test_isOpen_closedByDefault()
    {
        $interface = new RegularInterface(2, 32000, 16);
        self::assertFalse($interface->isOpen());
    }
}