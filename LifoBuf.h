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

template <class T> class LifoBuf
{
private:

	unsigned char* Buffer;
	const unsigned int BuffSize;
	MEMORYSTATUSEX* Memory;
	unsigned int count;
	bool err;

	struct Steck
	{
		unsigned int size;
		unsigned int sizedata = NULL;
		unsigned char* ptrlifo = nullptr;
		struct Steck* next = nullptr;
		struct Steck* prev = nullptr;
	} *SteckAll, * SteckBlock, * ptr;

	void __push();

public:

	LifoBuf(const unsigned int byte);
	LifoBuf(const unsigned int byte, const unsigned int mem);
	~LifoBuf();

	void push(T* value);
	void push(T value);
	void push(T* value, unsigned int size);
	void pop(T& value);
	void pop(T*& value);

	void operator > (T* value);
	void operator > (T value);
	void operator < (T& value);
	void operator < (T*& value);
};

