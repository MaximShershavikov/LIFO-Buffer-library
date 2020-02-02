/**************************************************************************************

    LIFO-Buffer-library version 1.0. LIFO Buffer library
    Copyright (C) 2020  Maxim Shershavikov

    This file is part of LIFO-Buffer-library v1.0.

    LIFO-Buffer-library v1.0 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LIFO-Buffer-library v1.0 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Email m.shershavikov@yandex.ru
    To read a copy of the GNU General Public License in a file COPYING.txt,
    to do this, click the AbautProgram button.

***************************************************************************************/

#pragma once

#include <Windows.h>
#include <stdio.h>

template <class T> class LifoBuf
{
private:

    const unsigned int BuffSize;
    unsigned int       count;
    char               Text[50];
    MEMORYSTATUSEX     *Memory;
    unsigned char      *Buffer;

    struct Steck
    {
        unsigned int   size     = NULL;
        unsigned int   sizedata = NULL;
        unsigned char  *ptrlifo = nullptr;
        struct   Steck *next    = nullptr;
        struct   Steck *prev    = nullptr;
    } *SteckAll, *SteckBlock, *ptr;

    void __push();
    void __pop();

public:

    LifoBuf(const unsigned int byte);
    LifoBuf(const unsigned int byte, const unsigned int mem);
    ~LifoBuf();

    void push(T *value);
    void push(T value);
    void push(T *value, unsigned int size);
    void pop(T &value);
    void pop(T *&value);

    unsigned int QuantityBlockData();
    unsigned int MaxSizeData();
    char *AddrOfBlockData(unsigned int value);
    char *ErrorText();

    void operator > (T *value);
    void operator > (T value);
    void operator < (T &value);
    void operator < (T *&value);
};

template <class T> LifoBuf<T>::LifoBuf(const unsigned int byte) : BuffSize(byte), count(NULL), Text{ NULL }, Memory(new MEMORYSTATUSEX)
{
    Memory->dwLength = sizeof(*Memory);
    GlobalMemoryStatusEx(Memory);
    if ((Memory->ullAvailPhys / 3) < byte)
    {
        strcpy_s(Text, "Error - Maximum memory size reached");
        return;
    }
    Buffer = new unsigned char[byte];
    memset(Buffer, NULL, byte);
    SteckAll = new Steck;
    SteckBlock = SteckAll;
    SteckBlock->ptrlifo = Buffer;
    ptr = nullptr;
    count++;
}

template <class T> LifoBuf<T>::LifoBuf(const unsigned int byte, const unsigned int mem) : BuffSize(byte), count(NULL), Text{ NULL }, Memory(new MEMORYSTATUSEX)
{
    Memory->dwLength = sizeof(*Memory);
    GlobalMemoryStatusEx(Memory);
    if ((Memory->ullAvailPhys / mem) < byte)
    {
        strcpy_s(Text, "Error - Maximum memory size reached");
        return;
    }
    Buffer = new unsigned char[byte];
    memset(Buffer, NULL, byte);
    SteckAll = new Steck;
    SteckBlock = SteckAll;
    SteckBlock->ptrlifo = Buffer;
    ptr = nullptr;
    count++;
}

template <class T> LifoBuf<T>::~LifoBuf()
{
    delete[] Buffer;
    Buffer = nullptr;
    memset(Text, NULL, sizeof(Text));
    delete Memory;
    Memory = nullptr;
    while (count != NULL)
    {
        SteckBlock = SteckBlock->prev;
        ptr = SteckBlock;
        delete ptr;
        count--;
    }
}

template <class T> void LifoBuf<T>::__push()
{
    SteckBlock->next = new Steck;
    SteckBlock->next->ptrlifo = SteckBlock->ptrlifo + SteckBlock->size;
    SteckBlock->next->prev = SteckBlock;
    SteckBlock = SteckBlock->next;
    SteckBlock->sizedata = SteckBlock->prev->sizedata;
    count++;
}

template <class T> void LifoBuf<T>::__pop()
{
    if (SteckBlock->prev->prev != nullptr)
    {
        SteckBlock = SteckBlock->prev;
        delete SteckBlock->next;
        SteckBlock->next = nullptr;
        SteckBlock->sizedata = SteckBlock->prev->sizedata;
        SteckBlock->size = NULL;
    }
    else
    {
        SteckBlock = SteckBlock->prev;
        delete SteckBlock->next;
        SteckBlock->next = nullptr;
        SteckBlock->size = NULL;
        SteckBlock->sizedata = NULL;
    }
    count--;
}

template <class T> void LifoBuf<T>::push(T *value)
{
    SteckBlock->size = strlen(reinterpret_cast<const char*>(value)) + 1;
    SteckBlock->sizedata += SteckBlock->size;
    SteckBlock->ptrlifo[SteckBlock->size - 1] = NULL;
    memset(Text, NULL, sizeof(Text));
    if (SteckBlock->sizedata >= BuffSize)
    {
        if (SteckBlock->prev != nullptr)
                SteckBlock->sizedata = SteckBlock->prev->sizedata;
        strcpy_s(Text, "Error - Maximum buffer size reached");
        return;
    }
    memcpy(SteckBlock->ptrlifo, value, SteckBlock->size);

    __push();
}

template <class T> void LifoBuf<T>::push(T value)
{
    SteckBlock->size = sizeof(&value);
    SteckBlock->sizedata += SteckBlock->size;
    memset(Text, NULL, sizeof(Text));
    if (SteckBlock->sizedata >= BuffSize)
    {
        if (SteckBlock->prev != nullptr)
                SteckBlock->sizedata = SteckBlock->prev->sizedata;
        strcpy_s(Text, "Error - Maximum buffer size reached");
        return;
    }
    memcpy(SteckBlock->ptrlifo, &value, SteckBlock->size);

    __push();
}

template <class T> void LifoBuf<T>::push(T *value, unsigned int size)
{
    SteckBlock->size = size;
    SteckBlock->sizedata += SteckBlock->size;
    memset(Text, NULL, sizeof(Text));
    if (SteckBlock->sizedata >= BuffSize)
    {
        if (SteckBlock->prev != nullptr)
                SteckBlock->sizedata = SteckBlock->prev->sizedata;
        strcpy_s(Text, "Error - Maximum buffer size reached");
        return;
    }
    memcpy(SteckBlock->ptrlifo, value, SteckBlock->size);

    __push();
}

template <class T> void LifoBuf<T>::pop(T &value)
{
    memset(Text, NULL, sizeof(Text));
    if (SteckBlock->prev == nullptr)
    {
        strcpy_s(Text, "Error - There no data in buffer");
        value = NULL;
        return;
    }
    memcpy(&value, &*SteckBlock->prev->ptrlifo, SteckBlock->prev->size);
    memset(SteckBlock->prev->ptrlifo, NULL, SteckBlock->prev->size);

    __pop();
}

template <class T> void LifoBuf<T>::pop(T *&value)
{
    memset(Text, NULL, sizeof(Text));
    if (SteckBlock->prev == nullptr)
    {
        strcpy_s(Text, "Error - There no data in buffer");
        value = NULL;
        return;
    }
    value = new T[SteckBlock->prev->size / sizeof(T)];
    memcpy(value, &*SteckBlock->prev->ptrlifo, SteckBlock->prev->size);
    memset(SteckBlock->prev->ptrlifo, NULL, SteckBlock->prev->size);

    __pop();
}

template <class T> char *LifoBuf<T>::AddrOfBlockData(unsigned int value)
{
    int num = 9;

    ptr = SteckAll;
    memset(Text, NULL, sizeof(Text));
    if (value > count || value < 1)
    {
        strcpy_s(Text, "Error - There no block of data");
        return Text;
    }
    if (SteckAll->next == nullptr)
    {
        strcpy_s(Text, "Error - There no data in buffer");
        return Text;
    }
    for (unsigned int i = 1; i <= value; i++) ptr = ptr->next;
    sprintf_s(Text, "%X", reinterpret_cast<unsigned int>(ptr->prev->ptrlifo));
    for (int i = 10; i >= 0; i--)
    {
        if (Text[10] == '\0') { Text[num] = Text[i]; num--; }
        if (Text[i] == '\0') Text[10] = Text[i];
        Text[i] = '0';
    }
    Text[0] = '0'; Text[1] = 'x';

    return Text;
}

template <class T> char* LifoBuf<T>::ErrorText()
{
    if (Text[0] == 'E') return Text;
    else {
        memset(Text, NULL, sizeof(Text));
        strcpy_s(Text, "There no text of error in ErrorText()");
        return Text;
    }
}

template <class T> unsigned int LifoBuf<T>::QuantityBlockData() 
{
    return count;
}

template <class T> unsigned int LifoBuf<T>::MaxSizeData() 
{
    return SteckBlock->prev->sizedata;
}

template <class T> void LifoBuf<T>::operator > (T *value) { push(value); }
template <class T> void LifoBuf<T>::operator > (T value) { push(value); }
template <class T> void LifoBuf<T>::operator < (T &value) { pop(value); }
template <class T> void LifoBuf<T>::operator < (T *&value) { pop(value); }
