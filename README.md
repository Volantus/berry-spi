# Raspberry Pi SPI PHP extension
Native PHP extension for SPI communication on RaspberryPi.

Extension is still in alpha state. Please don't hesitate to report bugs, make suggestions or ask questions.

# Credits
The extension uses the great [pigpio library](http://abyz.me.uk/rpi/pigpio/index.html) and is build on top of [PHP-CPP](http://www.php-cpp.com/).

# Installation
For the moment only PHP 7.0 is tested. As soon we reach BETA status, backports will be created.
Deployment via official DEB repository is planned.

## Precompiled release 
Download the latest shared object and include it into php.ini:
```bash
cd /usr/lib/php/$(php -v | grep -i 'PHP [57]' | cut -c1-8 | sed s/'PHP '//g | cut -c1-3)
wget https://github.com/Volantus/berry-spi/releases/download/0.2.0/berry-spi.so
sudo echo "extension=berry-spi.so" >> /etc/php/7.0/cli/php.ini
```
## Compile from source
Please make sure you installed the PHP-CPP library ([guide](http://www.php-cpp.com/documentation/install)) + pigpio ([Guide](http://abyz.me.uk/rpi/pigpio/download.html)).
Clone and compile the source code:
```bash
git clone https://github.com/Volantus/berry-spi
cd berry-spi
make
sudo make install
```


# Usage
Communication is handled by the following classes
* RegularInterface: In case of using the native SPI pins (GPIO 07 - 11)
* BitBangingInterface: In case of using any other GPIO pins

## Regular interface
Don't forget to close connection before object gets deleted.
Otherwise new connection could fail.
### Opening/Closing the connection
```PHP
use Volantus\BerrySpi\RegularInterface;

$interface = new RegularInterface(1, 32768, 0);

// Opening the connection
$interface->open();

// Don't forget to close the connection
$interface->close();
```

#### Parameters
The constructor accept three parameters

| Parameter     | Description                                                                             |
| ------------- |-----------------------------------------------------------------------------------------|
| channel       | SPI channel (1 or 2)                                                                    |
| speed         | Baud speed in bits per second                                                           |
|               | 32K-125M (values above 30M are unlikely to work)                                        |
| flags         | Additional configuration, see [details](http://abyz.me.uk/rpi/pigpio/cif.html#spiOpen)  |


### Cross transferring data
Sending + retrieving data simultaneously. Same count of byte as send is read.
Method accepts an array of words(bytes) to send.
```PHP
$retrievedData = $interface->transfer([1, 2, 3]);
echo '1. received byte: ' . $retrievedData[0];
echo '2. received byte: ' . $retrievedData[1];
echo '3. received byte: ' . $retrievedData[2];
```
### Just reading
Reads given count of bytes
```PHP
// Reading 8 bytes of data
$retrievedData = $interface->read(8);
```

### Just writing
Sends the given bytes
```PHP
// Just sending data
$interface->write([1, 2, 3]);
```

## Bit banging interface
Don't forget to close connection before object gets deleted.
Otherwise new connection could fail.
### Opening/Closing the connection
```PHP
use Volantus\BerrySpi\BitBangingInterface;

$interface = new BitBangingInterface(12, 16, 20, 21, 512, 0);

// Opening the connection
$interface->open();

// Don't forget to close the connection
$interface->close();
```

#### Parameters
The constructor accept three parameters

| Parameter     | Description                                                                              |
| ------------- |------------------------------------------------------------------------------------------|
| csPin         | The GPIO (0-31) used for the slave select signal *¹                                      |
| misoPin       | The GPIO (0-31) used for the MISO signal *²                                              |
| mosiPin       | The GPIO (0-31) used for the MOSI signal *²                                              |
| sclkPin       | The GPIO (0-31) used for the SCLK signal *²                                              |
| speed         | Baud speed in bits per second                                                            |
|               | 50-250k                                                                                  |
| flags         | Additional configuration, see [details](http://abyz.me.uk/rpi/pigpio/cif.html#bbSpiOpen) |

*¹ This pin has to be unique for each device

*² This pin can be shared with multiple slave devices, if no parallel data transfer is required


### Cross transferring data
Sending + retrieving data simultaneously. Same count of byte as send is read.
Method accepts an array of words(bytes) to send.
```PHP
$retrievedData = $interface->transfer([1, 2, 3]);
echo '1. received byte: ' . $retrievedData[0];
echo '2. received byte: ' . $retrievedData[1];
echo '3. received byte: ' . $retrievedData[2];
```

## Error handling
All errors are wrapped in exceptions within the namespace Volantus\BerrySpi.
To see which method throws which exception please consult the stubs.

### Volantus\BerrySpi\InvalidArgumentException
In case of invalid parameters (e.g. negative channel or bad speed).

### Volantus\BerrySpi\GpioInitFailureException
Pigpio library initialization failed (e.g. insufficient permissions).

### Volantus\BerrySpi\LogicException
In case of logically incorrect behaviour (e.g. trying to send data by an non-open connection).

### Volantus\BerrySpi\RuntimeException
In case of deeper problems (e.g. internal failure).

  
# Contribution
Contribution in form of bug reports, suggestions or pull requests is highly welcome!
## Executing the unit tests
For integration testing some GPIO pins need to be connected (e.g. by jumper cable) while running the test suite
 * SPI_MISO (GPIO09) and SPI_MOSI (GPIO10)
 * GPIO16 and GPIO20  

All tests are managed by PHPUnit:
```Bash
    # Install PHPUnit if not already done
    composer install
    
    # Execution of the tests (sudo is required by pigpio)
    sudo vendor/phpunit/phpunit/phpunit 
```





