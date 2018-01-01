<?php
namespace Volantus\BerrySpi\Tests;

use PHPUnit\Framework\TestCase;
use Volantus\BerrySpi\BitBangingInterface;
use Volantus\BerrySpi\RegularInterface;

/**
 * Class SpiInterfaceTestCase
 *
 * @package Volantus\BerrySpi\Tests
 */
abstract class SpiInterfaceTestCase extends TestCase
{
    /**
     * @var BitBangingInterface|RegularInterface
     */
    protected $interface;

    protected function tearDown()
    {
        if ($this->interface !== null && $this->interface->isOpen()) {
            try {
                $this->interface->close();
            } catch (\Throwable $e) {}
        }

        $this->interface = null;
    }
}