#include <phpcpp.h>
#include <pigpio.h>
#include "BerrySpiState.hpp"
#include "BerrySpiExceptions.hpp"
#include "AbstractSpiInterface.hpp"
#include "SpiRegularInterface.hpp"

extern "C" {
    /**
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("berry-spi", "0.0.2");
        Php::Class<SpiRegularInterface> regularInterface("Volantus\\BerrySpi\\RegularInterface");
        regularInterface.method<&SpiRegularInterface::__construct> ("__construct", {
            Php::ByVal("channel", Php::Type::Numeric, true),
            Php::ByVal("speed", Php::Type::Numeric, true),
            Php::ByVal("flags", Php::Type::Numeric, true)
        });
        regularInterface.method<&SpiRegularInterface::getChannel> ("getChannel");
        regularInterface.method<&SpiRegularInterface::getSpeed> ("getSpeed");
        regularInterface.method<&SpiRegularInterface::getFlags> ("getFlags");
        regularInterface.method<&SpiRegularInterface::isOpen> ("isOpen");
        regularInterface.method<&SpiRegularInterface::open> ("open");
        regularInterface.method<&SpiRegularInterface::close> ("close");
        regularInterface.method<&SpiRegularInterface::transfer> ("transfer", {
            Php::ByVal("data", Php::Type::String, true)
        });
        regularInterface.method<&SpiRegularInterface::read> ("read", {
            Php::ByVal("count", Php::Type::Numeric, true)
        });
        regularInterface.method<&SpiRegularInterface::transfer> ("write", {
            Php::ByVal("data", Php::Type::String, true)
        });

        extension.add(std::move(regularInterface));

        extension.onStartup([]() {
            BerrySpiState::initDependencies();
            BerrySpiExceptions::prepare();
        });

        extension.onShutdown([]() {
            BerrySpiState::cleanDependencies();
        });

        return extension;
    }
}
