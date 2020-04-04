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

#define LINT       LifoBuf_int
#define LUINT      LifoBuf_unsigned_int
#define LCHAR      LifoBuf_char
#define LUCHAR     LifoBuf_unsigned_char
#define LSHORT     LifoBuf_short	
#define LUSHORT    LifoBuf_unsigned_short
#define LLONG      LifoBuf_long
#define LULONG     LifoBuf_unsigned_long
#define LLONGLONG  LifoBuf_long_long
#define LULONGLONG LifoBuf_unsigned_long_long
#define LDOUBLE    LifoBuf_double

typedef int                _int;
typedef unsigned int       _unsigned_int;
typedef char               _char;
typedef unsigned char      _unsigned_char;
typedef short              _short;
typedef unsigned short     _unsigned_short;
typedef long               _long;
typedef unsigned long      _unsigned_long;
typedef long long          _long_long;
typedef unsigned long long _unsigned_long_long;
typedef double             _double;

#define DEF_CLASS_BUF_LIFO(type)                                    \
{                                                                   \
private:                                                            \
    void* pointer;                                                  \
public:                                                             \
    LifoBuf##type(const unsigned int byte);                         \
    LifoBuf##type(const unsigned int byte, const unsigned int mem); \
    ~LifoBuf##type();                                               \
                                                                    \
    char *push(type* value);                                        \
    char *push(type value);                                         \
    char *push(type* value, unsigned int size);                     \
    char *pop(type& value);                                         \
    char *pop(type*& value);                                        \
                                                                    \
    unsigned int QuantityBlockData();                               \
    unsigned int MaxSizeData();                                     \
    char *AddrOfBlockData(unsigned int value);                      \
    char *AddrAndNumOfBlockData(unsigned int value);                \
    char *ErrorText();                                              \
                                                                    \
    char *operator > (type* value);                                 \
    char *operator > (type value);                                  \
    char *operator < (type& value);                                 \
    char *operator < (type*& value);                                \
}                                                                   \

class LifoBuf_int                DEF_CLASS_BUF_LIFO(_int);
class LifoBuf_unsigned_int       DEF_CLASS_BUF_LIFO(_unsigned_int);
class LifoBuf_char               DEF_CLASS_BUF_LIFO(_char);
class LifoBuf_unsigned_char      DEF_CLASS_BUF_LIFO(_unsigned_char);
class LifoBuf_short              DEF_CLASS_BUF_LIFO(_short);
class LifoBuf_unsigned_short	 DEF_CLASS_BUF_LIFO(_unsigned_short);
class LifoBuf_long               DEF_CLASS_BUF_LIFO(_long);
class LifoBuf_unsigned_long      DEF_CLASS_BUF_LIFO(_unsigned_long);
class LifoBuf_long_long          DEF_CLASS_BUF_LIFO(_long_long);
class LifoBuf_unsigned_long_long DEF_CLASS_BUF_LIFO(_unsigned_long_long);
class LifoBuf_double             DEF_CLASS_BUF_LIFO(_double);
