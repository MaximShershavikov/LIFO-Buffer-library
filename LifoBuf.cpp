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

#include "LifoBuf.h"

template <class T> LifoBuf<T>::LifoBuf(const unsigned int byte) : BuffSize(byte), Memory(new MEMORYSTATUSEX), count(NULL), err(false)
{
	Memory->dwLength = sizeof(*Memory);
	GlobalMemoryStatusEx(Memory);
	if ((Memory->ullAvailPhys / 3) < byte) err = true;
	Buffer = new unsigned char[byte];
	memset(Buffer, NULL, byte);
	SteckAll = new Steck;
	SteckBlock = SteckAll;
	SteckBlock->ptrlifo = Buffer;
	ptr = nullptr;
	count++;
}

template <class T> LifoBuf<T>::LifoBuf(const unsigned int byte, const unsigned int mem) : BuffSize(byte), Memory(new MEMORYSTATUSEX), count(NULL), err(false)
{
	Memory->dwLength = sizeof(*Memory);
	GlobalMemoryStatusEx(Memory);
	if ((Memory->ullAvailPhys / mem) < byte) err = true;
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

template <class T> void LifoBuf<T>::push(T* value)
{
	SteckBlock->size = strlen(value) + 1;
	SteckBlock->sizedata += SteckBlock->size;
	SteckBlock->ptrlifo[SteckBlock->size - 1] = NULL;
	if (SteckBlock->sizedata >= BuffSize) return;
	memcpy(SteckBlock->ptrlifo, value, SteckBlock->size);

	__push();
}

template <class T> void LifoBuf<T>::push(T value)
{
	SteckBlock->size = sizeof(&value);
	SteckBlock->sizedata += SteckBlock->size;
	if (SteckBlock->sizedata >= BuffSize) return;
	memcpy(SteckBlock->ptrlifo, &value, SteckBlock->size);

	__push();
}

template <class T> void LifoBuf<T>::push(T* value, unsigned int size)
{
	SteckBlock->size = size * sizeof(T);
	SteckBlock->sizedata += SteckBlock->size;
	if (SteckBlock->sizedata >= BuffSize) return;
	memcpy(SteckBlock->ptrlifo, value, SteckBlock->size);

	__push();
}

template <class T> void LifoBuf<T>::pop(T& value)
{
	if (SteckBlock->prev == nullptr)
	{
		value = NULL;
		return;
	}
	ptr = SteckBlock->prev;
	memcpy(&value, &*SteckBlock->prev->ptrlifo, SteckBlock->prev->size);
	memset(SteckBlock->prev->ptrlifo, NULL, SteckBlock->prev->size);
	if (SteckBlock->prev->prev != nullptr)
	{
		SteckBlock->prev->prev->next = SteckBlock;
		SteckBlock->prev = SteckBlock->prev->prev;
		delete ptr;
		ptr = nullptr;
	}
}

template <class T> void LifoBuf<T>::pop(T*& value)
{
	if (SteckBlock->prev == nullptr)
	{
		value = NULL;
		return;
	}
	ptr = SteckBlock->prev;
	value = new T[SteckBlock->prev->size / sizeof(T)];
	memcpy(value, &*SteckBlock->prev->ptrlifo, SteckBlock->prev->size);
	memset(SteckBlock->prev->ptrlifo, NULL, SteckBlock->prev->size);
	if (SteckBlock->prev->prev != nullptr)
	{
		SteckBlock->prev->prev->next = SteckBlock;
		SteckBlock->prev = SteckBlock->prev->prev;
		delete ptr;
		ptr = nullptr;
	}
}

template <class T> void LifoBuf<T>::operator > (T* value)
{
	push(value);
}
template <class T> void LifoBuf<T>::operator > (T value)
{
	push(value);
}
template <class T> void LifoBuf<T>::operator < (T& value)
{
	pop(value);
}
template <class T> void LifoBuf<T>::operator < (T*& value)
{
	pop(value);
}
