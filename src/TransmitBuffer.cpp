#include <phpcpp.h>
#include <stdint.h>
#include "BerrySpiExceptions.hpp"
#include "TransmitBuffer.hpp"

TransmitBuffer::TransmitBuffer(Php::Value phpData)
{
    this->wordCount = phpData.size();
    this->length = phpData.size();

    if (this->length == 0) {
        BerrySpiExceptions::InvalidArgumentException("Invalid Parameter <data> given => unable to send empty data");
        this->valid = false;
        return;
    }

    this->data = new char[length + 1];

    for (int i = 0; i < length; i++) {
        int signedItem = phpData[i];

        if (signedItem < 0) {
            BerrySpiExceptions::InvalidArgumentException("Invalid data given => no negative values allowed");
            this->valid = false;
            return;
        }

        if (signedItem > 255) {
            BerrySpiExceptions::InvalidArgumentException("Invalid data given => only one byte per array item allowed");
            this->valid = false;
            return;
        }

        unsigned unsignedItem = signedItem;
        this->data[i] = unsignedItem;
    }


    this->data[this->length] = '\0';
    this->valid = true;
}

TransmitBuffer::~TransmitBuffer()
{
    if (this->length > 0) {
        delete[] this->data;
    }
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