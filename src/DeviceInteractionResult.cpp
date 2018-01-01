#include "DeviceInteractionResult.hpp"

DeviceInteractionResult::DeviceInteractionResult(int _returnCode, bool _phpExceptionThrown)
{
    returnCode = _returnCode;
    phpExceptionThrown = _phpExceptionThrown;
}

int DeviceInteractionResult::getReturnCode() const
{
    return returnCode;
}

bool DeviceInteractionResult::isPhpExceptionThrown() const
{
    return phpExceptionThrown;
}

