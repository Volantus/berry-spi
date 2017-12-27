#include <Zend/zend.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_API.h>

class BerrySpiExceptions
{
private:
    static zend_class_entry* _invalidArgumentException;
    static zend_class_entry* _gioInitFailureException;
    static zend_class_entry* _logicException;
    static zend_class_entry* _gpioFailureException;
    static void registerException(const char* name, zend_class_entry **memberClassEntry);

public:
    static void prepare();
    static void InvalidArgumentException(const char* message);
    static void GpioInitFailureException(const char* message);
    static void LogicException(const char* message);
    static void GpioFailureException(const char* message);
};