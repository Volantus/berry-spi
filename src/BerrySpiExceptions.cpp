#include <stdexcept>
#include <phpcpp.h>
#include "BerrySpiExceptions.hpp"

zend_class_entry* BerrySpiExceptions::_gioInitFailureException;
zend_class_entry* BerrySpiExceptions::_invalidArgumentException;
zend_class_entry* BerrySpiExceptions::_logicException;
zend_class_entry* BerrySpiExceptions::_gpioFailureException;

void BerrySpiExceptions::prepare()
{
    registerException("Volantus\\BerrySPI\\InvalidArgumentException", &_invalidArgumentException);
    registerException("Volantus\\BerrySPI\\GpioInitFailureException", &_gioInitFailureException);
    registerException("Volantus\\BerrySPI\\LogicException", &_logicException);
    registerException("Volantus\\BerrySPI\\GpioFailureException", &_gpioFailureException);
}

void BerrySpiExceptions::registerException(const char* name, zend_class_entry **memberClassEntry)
{
    zend_class_entry classEntry;
    INIT_CLASS_ENTRY(classEntry, name, NULL);
    *memberClassEntry = zend_register_internal_class_ex(&classEntry, zend_exception_get_default());
}

void BerrySpiExceptions::InvalidArgumentException(const char* message)
{
    zend_throw_exception_ex(_invalidArgumentException, 0, message, __FILE__, __LINE__);
}

void BerrySpiExceptions::GpioInitFailureException(const char* message)
{
    zend_throw_exception_ex(_gioInitFailureException, 0, message, __FILE__, __LINE__);
}

void BerrySpiExceptions::LogicException(const char *message)
{
    zend_throw_exception_ex(_logicException, 0, message, __FILE__, __LINE__);
}

void BerrySpiExceptions::GpioFailureException(const char *message)
{
    zend_throw_exception_ex(_gpioFailureException, 0, message, __FILE__, __LINE__);
}