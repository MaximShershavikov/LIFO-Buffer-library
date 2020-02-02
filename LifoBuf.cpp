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

#include "LifoTemplate.h"
#include "LifoBuf.h"

#define DEFCLASSLIFO(type)                                                    \
LifoBuf##type::LifoBuf##type(const unsigned int byte)                         \
{                                                                             \
    LifoBuf <type> *Lifo = new LifoBuf <type>(byte);                          \
    pointer = Lifo;                                                           \
}                                                                             \
                                                                              \
LifoBuf##type::LifoBuf##type(const unsigned int byte, const unsigned int mem) \
{                                                                             \
    LifoBuf <type>* Lifo = new LifoBuf <type>(byte, mem);                     \
    pointer = Lifo;                                                           \
}                                                                             \
                                                                              \
void LifoBuf##type::push(type *value)                                         \
{                                                                             \
    static_cast<LifoBuf<type>*>(pointer)->push(value);                        \
}                                                                             \
                                                                              \
void LifoBuf##type::push(type value)                                          \
{                                                                             \
    static_cast<LifoBuf<type>*>(pointer)->push(value);                        \
}                                                                             \
                                                                              \
void LifoBuf##type::push(type *value, unsigned int size)                      \
{                                                                             \
    static_cast<LifoBuf<type>*>(pointer)->push(value, size);                  \
}                                                                             \
                                                                              \
void LifoBuf##type::pop(type &value)                                          \
{                                                                             \
    static_cast<LifoBuf<type>*>(pointer)->pop(value);                         \
}                                                                             \
                                                                              \
void LifoBuf##type::pop(type *&value)                                         \
{                                                                             \
    static_cast<LifoBuf<type>*>(pointer)->pop(value);                         \
}                                                                             \
                                                                              \
unsigned int LifoBuf##type::QuantityBlockData()                               \
{                                                                             \
    return static_cast<LifoBuf<type>*>(pointer)->QuantityBlockData();         \
}                                                                             \
                                                                              \
unsigned int LifoBuf##type::MaxSizeData()                                     \
{                                                                             \
    return static_cast<LifoBuf<type>*>(pointer)->MaxSizeData();               \
}                                                                             \
                                                                              \
char *LifoBuf##type::AddrOfBlockData(unsigned int value)                      \
{                                                                             \
    return static_cast<LifoBuf<type>*>(pointer)->AddrOfBlockData(value);      \
}                                                                             \
                                                                              \
char *LifoBuf##type::ErrorText()                                              \
{                                                                             \
    return static_cast<LifoBuf<type>*>(pointer)->ErrorText();                 \
}                                                                             \
                                                                              \
void LifoBuf##type::operator > (type *value) { push(value); }                 \
void LifoBuf##type::operator > (type value) { push(value); }                  \
void LifoBuf##type::operator < (type &value) { pop(value); }                  \
void LifoBuf##type::operator < (type *&value) { pop(value); }                 \
                                                                              \
LifoBuf##type::~LifoBuf##type()                                               \
{                                                                             \
    delete static_cast<LifoBuf<type>*>(pointer);                              \
    pointer = nullptr;                                                        \
}                                                                             \

DEFCLASSLIFO(_int)
DEFCLASSLIFO(_unsigned_int)
DEFCLASSLIFO(_char)
DEFCLASSLIFO(_unsigned_char)
DEFCLASSLIFO(_short)
DEFCLASSLIFO(_unsigned_short)
DEFCLASSLIFO(_long)
DEFCLASSLIFO(_unsigned_long)
DEFCLASSLIFO(_long_long)
DEFCLASSLIFO(_unsigned_long_long)
DEFCLASSLIFO(_double)
