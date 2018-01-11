#ifndef TRANSFER_BUFFER_H
#define TRANSFER_BUFFER_H

class TransmitBuffer
{
private:
   unsigned wordCount;
   int length;
   char* data;
   bool valid;

public:
    TransmitBuffer(Php::Value phpData);

    unsigned getWordCount();
    int getLength();
    char* getData();
    bool isValid();
};
#endif