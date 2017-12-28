# Berry SPI PHP extension
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
wget https://github.com/Volantus/berry-spi/releases/download/0.0.1/berry-spi.so
sudo echo "extension=berry-spi.so" >> /etc/php/7.0/cli/php.ini
```
## Compile on your own
Please make sure you installed the PHP-CPP library ([guide](http://www.php-cpp.com/documentation/install)) + pigpio ([Guide](http://abyz.me.uk/rpi/pigpio/download.html)) .
Then simply clone and compile the source code:
```bash
git clone https://github.com/Volantus/berry-spi
cd berry-spi
make
sudo make install
```


# Usage
Communication is handled by the RegularInterface class. (Implementation of BitBanging is planned for the near future)

```PHP
    use Volantus\BerrySpi\RegularInterface;
    
    $interface = new RegularInterface(1, 32768, 0);
    
    // Opening the connection
    $interface->open();
    
    // Sending + retrieving data simustanisly
    $receivedData = $interface->transfer(0x1269493);
    
    // Just reading data
    $receivedData = $interface->read(8);
        
    // Just sending data
    $interface->write('abc');
    
    // Don't forget to close the connection
    $interface->close();
```

## Parameters
The constructor accept three types parameters

| Parameter     | Description                                                                             |
| ------------- |-----------------------------------------------------------------------------------------|
| channel       | SPI channel (1 or 2)                                                                    |
| speed         | Baud speed in bits per second                                                           |
|               | 32K-125M (values above 30M are unlikely to work)                                        |
| flags         | Additional configuration, see [details](http://abyz.me.uk/rpi/pigpio/cif.html#spiOpen)  |

## Error handling
All errors are wrapped in exceptions within the namespace Volantus\BerrySpi
### RegularInterface::__construct
* Volantus\BerrySpi\InvalidArgumentException
  * Negative value for channel, speed or flag given
* Volantus\BerrySpi\GpioInitFailureException
  * Pigpio library initialization failed (e.g. insufficient permissions)
  
### RegularInterface::open
* Volantus\BerrySpi\InvalidArgumentException
  * Invalid channel, speed or flag parameter (reported by pigpio library) or no aux available
* Volantus\BerrySpi\LogicException
  * Device already opened
* Volantus\BerrySpi\RuntimeException
  * In case of deeper unknown errors
  
### RegularInterface::close
* Volantus\BerrySpi\LogicException
  * Device not open
* Volantus\BerrySpi\RuntimeException
  * In case of deeper unknown errors
  
### RegularInterface::transfer
* Volantus\BerrySpi\LogicException
  * Device not open
* Volantus\BerrySpi\RuntimeException
  * In case of deeper unknown errors (e.g. PI_BAD_SPI_COUNT)
  
### RegularInterface::read
* Volantus\BerrySpi\LogicException
  * Device not open
* Volantus\BerrySpi\RuntimeException
  * In case of deeper unknown errors (e.g. PI_BAD_SPI_COUNT)
  
### RegularInterface::write
* Volantus\BerrySpi\LogicException
  * Device not open
* Volantus\BerrySpi\RuntimeException
  * In case of deeper unknown errors (e.g. PI_BAD_SPI_COUNT)
  
# Contribution
Contribution in form of bug reports, suggestions or pull requests are highly welcome :).




