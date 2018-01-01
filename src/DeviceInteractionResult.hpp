#ifndef DEVICE_INTERACTION_RESULT_H
#define DEVICE_INTERACTION_RESULT_H

class DeviceInteractionResult
{
private:
    int returnCode;
    bool phpExceptionThrown;

public:
    DeviceInteractionResult(int _returnCode, bool _phpExceptionThrown);

    bool isPhpExceptionThrown() const;
    int getReturnCode() const;
};
#endif