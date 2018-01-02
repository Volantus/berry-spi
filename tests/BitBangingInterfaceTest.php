<?php
namespace Volantus\BerrySpi\Tests;

use Volantus\BerrySpi\BitBangingInterface;

/**
 * Class BitBangingInterfaceTest
 *
 * @package Volantus\BerrySpi\Tests
 */
class BitBangingInterfaceTest extends SpiInterfaceTestCase
{
    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <csPin> parameter
     */
    public function test_construct_negativeCsPin()
    {
        new BitBangingInterface(-1, 16, 20, 21, 512, 0);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <misoPin> parameter
     */
    public function test_construct_negativeMisoPin()
    {
        new BitBangingInterface(12, -1, 20, 21, 512, 0);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <mosiPin> parameter
     */
    public function test_construct_negativeMosiPin()
    {
        new BitBangingInterface(12, 16, -1, 21, 512, 0);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <sclkPin> parameter
     */
    public function test_construct_negativeSclkPin()
    {
        new BitBangingInterface(12, 16, 20, -1, 512, 0);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <speed> parameter
     */
    public function test_construct_negativeSpeed()
    {
        new BitBangingInterface(12, 16, 20, 21, -1, 0);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage No negative values allowed for <flags> parameter
     */
    public function test_construct_negativeFlags()
    {
        new BitBangingInterface(12, 16, 20, 21, 512, -1);
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage Opening SPI device failed => bad SPI baud rate (speed), probably not 50-500k (PI_BAD_SPI_BAUD)
     */
    public function test_open_invalidSpeed()
    {
        $this->interface = new BitBangingInterface(12, 16, 20, 21, 9999999, 0);
        $this->interface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage Opening SPI device failed => on of the given pins is invalid (PI_BAD_USER_GPIO)
     */
    public function test_open_badGpio()
    {
        $this->interface = new BitBangingInterface(32, 16, 20, 21, 512, 0);
        $this->interface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\InvalidArgumentException
     * @expectedExceptionMessage Opening SPI device failed => GPIO is already in use (PI_GPIO_IN_USE)
     */
    public function test_open_gpioAlreadyInUse()
    {
        $this->interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        $this->interface->open();
        $doubleInterface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        $doubleInterface->open();
    }

    /**
     * @expectedException \Volantus\BerrySpi\LogicException
     * @expectedExceptionMessage SPI device is already open
     */
    public function test_open_alreadyOpen()
    {
        $this->interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        $this->interface->open();
        $this->interface->open();
    }

    public function test_open_deviceOpened()
    {
        $this->interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        $this->interface->open();

        self::assertTrue($this->interface->isOpen());
    }

    /**
     * @expectedException \Volantus\BerrySpi\LogicException
     * @expectedExceptionMessage Unable to close an unestablished device connection
     */
    public function test_close_notOpen()
    {
        $this->interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        $this->interface->close();
    }

    public function test_close_deviceClosed()
    {
        $interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
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
        $interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        $interface->transfer('abc');
    }

    /**
     * For this test SPI_MISO (GPIO09) and SPI_MOSI (GPIO10) pins needs to be connected (e.g. jumper cable)
     */
    public function test_transfer_dataSendIsRead()
    {
        $this->interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        $this->interface->open();
        $readData = $this->interface->transfer('abc');

        self::assertEquals('abc', $readData, 'Check if GPIO16 (MISO) and GPIO20 (MOSI) are connected properly');
    }

    public function test_getCsPin_correct()
    {
        $interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        self::assertEquals(12, $interface->getCsPin());
    }

    public function test_getMisoPin_correct()
    {
        $interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        self::assertEquals(16, $interface->getMisoPin());
    }


    public function test_getMosiPin_correct()
    {
        $interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        self::assertEquals(20, $interface->getMosiPin());
    }

    public function test_getSclkPin_correct()
    {
        $interface = new BitBangingInterface(12, 16, 20, 21, 512, 16);
        self::assertEquals(21, $interface->getSclkPin());
    }

    public function test_getFlags_correct()
    {
        $interface = new BitBangingInterface(12, 16, 20, 21, 512, 16);
        self::assertEquals(16, $interface->getFlags());
    }

    public function test_isOpen_closedByDefault()
    {
        $interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);
        self::assertFalse($interface->isOpen());
    }
}