<?php
use Volantus\BerrySpi\RegularInterface;

$interface = new RegularInterface(1, 32000, 0);
$interface->open();

var_dump($interface->getSpeed());
