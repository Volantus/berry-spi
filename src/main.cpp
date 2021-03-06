#include <phpcpp.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "AbstractSpiInterface.hpp"
#include "SpiRegularInterface.hpp"
#include "SpiBitBangingInterface.hpp"

extern "C" {
    /**
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("berry-spi", "0.4.1");

        Php::Interface spiInterfaceInterface("Volantus\\BerrySpi\\SpiInterface");

        spiInterfaceInterface.method("initialize", Php::Static);
        spiInterfaceInterface.method("open");
        spiInterfaceInterface.method("close");
        spiInterfaceInterface.method("transfer", {
            Php::ByVal("data", Php::Type::Array, true)
        });
        spiInterfaceInterface.method("isInitialized", Php::Static);
        spiInterfaceInterface.method("getSpeed");
        spiInterfaceInterface.method("getFlags");
        spiInterfaceInterface.method("isOpen");

        extension.add(spiInterfaceInterface);


        Php::Class<SpiRegularInterface> regularInterface("Volantus\\BerrySpi\\RegularInterface");
        regularInterface.implements(spiInterfaceInterface);

        regularInterface.method<&SpiRegularInterface::__construct> ("__construct", {
            Php::ByVal("channel", Php::Type::Numeric, true),
            Php::ByVal("speed", Php::Type::Numeric, true),
            Php::ByVal("flags", Php::Type::Numeric, true)
        });
        regularInterface.method<&SpiRegularInterface::getChannel> ("getChannel");
        regularInterface.method<&SpiRegularInterface::getSpeed> ("getSpeed");
        regularInterface.method<&SpiRegularInterface::getFlags> ("getFlags");
        regularInterface.method<&SpiRegularInterface::isOpen> ("isOpen");
        regularInterface.method<&SpiRegularInterface::isInitialized> ("isInitialized");
        regularInterface.method<&SpiRegularInterface::initialize> ("initialize");
        regularInterface.method<&SpiRegularInterface::open> ("open");
        regularInterface.method<&SpiRegularInterface::close> ("close");
        regularInterface.method<&SpiRegularInterface::transfer> ("transfer", {
            Php::ByVal("data", Php::Type::Array, true)
        });
        regularInterface.method<&SpiRegularInterface::read> ("read", {
            Php::ByVal("count", Php::Type::Numeric, true)
        });
        regularInterface.method<&SpiRegularInterface::write> ("write", {
            Php::ByVal("data", Php::Type::Array, true)
        });

        extension.add(std::move(regularInterface));


        Php::Class<SpiBitBangingInterface> bitBangingInterface("Volantus\\BerrySpi\\BitBangingInterface");
        bitBangingInterface.implements(spiInterfaceInterface);

        bitBangingInterface.method<&SpiBitBangingInterface::__construct> ("__construct", {
            Php::ByVal("csPin", Php::Type::Numeric, true),
            Php::ByVal("misoPin", Php::Type::Numeric, true),
            Php::ByVal("mosiPin", Php::Type::Numeric, true),
            Php::ByVal("sclkPin", Php::Type::Numeric, true),
            Php::ByVal("speed", Php::Type::Numeric, true),
            Php::ByVal("flags", Php::Type::Numeric, true),
        });
        bitBangingInterface.method<&SpiBitBangingInterface::getCsPin> ("getCsPin");
        bitBangingInterface.method<&SpiBitBangingInterface::getMisoPin> ("getMisoPin");
        bitBangingInterface.method<&SpiBitBangingInterface::getMosiPin> ("getMosiPin");
        bitBangingInterface.method<&SpiBitBangingInterface::getSclkPin> ("getSclkPin");
        bitBangingInterface.method<&SpiBitBangingInterface::getSpeed> ("getSpeed");
        bitBangingInterface.method<&SpiBitBangingInterface::getFlags> ("getFlags");
        bitBangingInterface.method<&SpiBitBangingInterface::isOpen> ("isOpen");
        bitBangingInterface.method<&SpiRegularInterface::isInitialized> ("isInitialized");
        bitBangingInterface.method<&SpiBitBangingInterface::initialize> ("initialize");
        bitBangingInterface.method<&SpiBitBangingInterface::open> ("open");
        bitBangingInterface.method<&SpiBitBangingInterface::close> ("close");
        bitBangingInterface.method<&SpiBitBangingInterface::transfer> ("transfer", {
            Php::ByVal("data", Php::Type::Array, true)
        });

        extension.add(std::move(bitBangingInterface));

        extension.onStartup([]() {
            BerrySpiState::startup();
            BerrySpiExceptions::prepare();
        });

        extension.onShutdown([]() {
            BerrySpiState::cleanDependencies();
        });

        return extension;
    }
}
