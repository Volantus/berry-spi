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
}