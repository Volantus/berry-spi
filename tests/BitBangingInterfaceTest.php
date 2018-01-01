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