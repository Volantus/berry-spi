#include <phpcpp.h>
#include <stdint.h>
#include "BerrySpiExceptions.hpp"
#include "TransmitBuffer.hpp"

TransmitBuffer::TransmitBuffer(Php::Value phpData)
{
    this->wordCount = phpData.size();
    this->length = phpData.size();
    std::string txString;

    if (this->length == 0) {
        BerrySpiExceptions::InvalidArgumentException("Invalid Parameter <data> given => unable to send empty data");
        this->valid = false;
        return;
    }

    for (int i = 0; i < length; i++) {
        std::string arrayItem = phpData[i];
        if (arrayItem.length() > 1) {
            BerrySpiExceptions::InvalidArgumentException("Invalid data given => only one byte per array item allowed");
            this->valid = false;
            return;
        }

        txString = txString + arrayItem;
    }

    this->data = new char[length + 1];

    std::copy(txString.begin(), txString.end(), this->data);
    this->data[this->length] = '\0';
    this->valid = true;
}

unsigned TransmitBuffer::getWordCount()
{
    return wordCount;
};

int TransmitBuffer::getLength()
{
    return length;
};

char* TransmitBuffer::getData()
{
    return data;
};

bool TransmitBuffer::isValid()
{
    return valid;
}