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
#include <vector>
#include "LiFoBuf.h"

void main()
{
    unsigned int data_int[5][10] = { 0 };
    char data_char[10][10] = { 0 };

    std::vector < std::vector<unsigned int> > data(5);
    data[0] = { 0xffaaffaa, 0xdfaafdaa, 0x11001100, 0x88af88af, 0xccddccdd };
    data[1] = { 0xffaaffaa, 0xdfaafdaa, 0x11001100 };
    data[2] = { 0xffaaffaa, 0xdfaafdaa, 0x11001100, 0x88af88af, 0xccddccdd, 0x88af88af, 0xffaaffaa };
    data[3] = { 0xffaaffaa, 0xdfaafdaa };
    data[4] = { 0xffaaffaa, 0xdfaafdaa, 0x11001100, 0x88af88af, 0xccddccdd, 0x25612255, 0xf2ca7623, 0x01010101, 0xa1a2a3a4, 0x99435521 };

    std::vector <char*> text = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };

    LUINT LIFO_1(300);
    LCHAR LIFO_2(300);

    for (int i = 0; i < 5; i++)
    {
        std::cout << LIFO_1.push(data[i].data(), (data[i].size() * 4)) << " ";
        std::cout << LIFO_1.AddrAndNumOfBlockData(i + 1) << std::endl;
    }
    for (int i = 0; i < 5; i++) std::cout << LIFO_1.pop(*data_int[i]) << std::endl;

    for (int i = 0; i < 10; i++)
    {
        LIFO_2 > text[i];
        std::cout << LIFO_2.AddrAndNumOfBlockData(i + 1) << std::endl;
    }
    for (int i = 0; i < 10; i++) std::cout << (LIFO_2 < *data_char[i]) << std::endl;

    LIFO_1.~LifoBuf_unsigned_int();
    LIFO_2.~LifoBuf_char();

    _getch();
}
