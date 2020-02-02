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

#include <iostream>
#include <conio.h>
#include "LiFoBuf.h"

void main()
{
    unsigned int data_1[5] = { 0xffaaffaa, 0xdfaafdaa, 0x11001100, 0x88af88af, 0xccddccdd };
    unsigned int data_2[3] = { 0xffaaffaa, 0xdfaafdaa, 0x11001100 };
    unsigned int data_3[7] = { 0xffaaffaa, 0xdfaafdaa, 0x11001100, 0x88af88af, 0xccddccdd, 0x88af88af, 0xffaaffaa };
    unsigned int data_4[2] = { 0xffaaffaa, 0xdfaafdaa };
    unsigned int data_5[10] = { 0xffaaffaa, 0xdfaafdaa, 0x11001100, 0x88af88af, 0xccddccdd, 0x25612255, 0xf2ca7623, 0x01010101, 0xa1a2a3a4, 0x99435521 };

    unsigned int data_int[5][10] = { 0 };
    char data_char[10][10] = { 0 };

    LUINT LIFO_1(300);
    LCHAR LIFO_2(300);

    LIFO_1.push(data_1, sizeof(data_1));
    std::cout << LIFO_1.AddrOfBlockData(1) << std::endl;

    LIFO_1.push(data_2, sizeof(data_2));
    std::cout << LIFO_1.AddrOfBlockData(2) << std::endl;

    LIFO_1.push(data_3, sizeof(data_3));
    std::cout << LIFO_1.AddrOfBlockData(3) << std::endl;

    LIFO_1.push(data_4, sizeof(data_4));
    std::cout << LIFO_1.AddrOfBlockData(4) << std::endl;

    LIFO_1.push(data_5, sizeof(data_5));
    std::cout << LIFO_1.AddrOfBlockData(5) << std::endl << std::endl;

    for (int i = 0; i < 5; i++) LIFO_1.pop(*data_int[i]);

    LIFO_2 > "one";
    std::cout << LIFO_2.AddrOfBlockData(1) << std::endl;
    LIFO_2 > "two";
    std::cout << LIFO_2.AddrOfBlockData(2) << std::endl;
    LIFO_2 > "three";
    std::cout << LIFO_2.AddrOfBlockData(3) << std::endl;
    LIFO_2 > "four";
    std::cout << LIFO_2.AddrOfBlockData(4) << std::endl;
    LIFO_2 > "five";
    std::cout << LIFO_2.AddrOfBlockData(5) << std::endl;
    LIFO_2 > "six";
    std::cout << LIFO_2.AddrOfBlockData(6) << std::endl;
    LIFO_2 > "seven";
    std::cout << LIFO_2.AddrOfBlockData(7) << std::endl;
    LIFO_2 > "eight";
    std::cout << LIFO_2.AddrOfBlockData(8) << std::endl;
    LIFO_2 > "nine";
    std::cout << LIFO_2.AddrOfBlockData(9) << std::endl;
    LIFO_2 > "ten";
    std::cout << LIFO_2.AddrOfBlockData(10) << std::endl;

    for (int i = 0; i < 10; i++) LIFO_2 < *data_char[i];

    LIFO_1.~LifoBuf_unsigned_int();
    LIFO_2.~LifoBuf_char();

    _getch();
}
