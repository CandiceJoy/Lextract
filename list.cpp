//
// Created by Candice Neill on 2/7/23.
//

#include "list.h"
#include <regex>

template<typename T>
void List<T>::extend ()
{
	T *old = data;
	data = new T[_size + growBy];

	for (int x = 0; x < _size; x++)
	{
		data[x] = old[x];
	}

	maxSize += growBy;

	if (old != nullptr)
	{
		delete[] old;
	}
}

template<typename T>
List<T>::List (int sizeIn)
{
	if (sizeIn < 0)
	{
		throw std::runtime_error("Attempted to initialise List with negative size: " + std::to_string(sizeIn));
	}

	maxSize = sizeIn + (growBy - sizeIn % growBy);
	_size   = sizeIn;
	data    = new T[maxSize];
}

template<typename T>
inline unsigned int List<T>::size () const
{
	return _size;
}

template<typename T>
void List<T>::operator+= (T t)
{
	if (_size + 1 > maxSize)
	{
		extend();
	}

	data[_size++] = t;
}

template<typename T>
T &List<T>::operator[] (long loc)
{
	if (loc >= _size)
	{
		throw std::runtime_error("Array index out of bounds: " + std::to_string(loc) + " (size " + std::to_string(_size) + ")\n");
	}

	return data[loc];
}

template<typename T>
const T &List<T>::operator[] (long loc) const
{
	if (loc >= _size)
	{
		throw std::runtime_error("Array index out of bounds: " + std::to_string(loc) + " (size " + std::to_string(_size) + ")\n");
	}

	return *data[loc];
}

template<typename T>
T &List<T>::operator* () const
{ return *data; }
template<typename T>
T *List<T>::operator-> ()
{ return data; }

template<typename T>
void List<T>::insert (int pos,T value)
{
	int oldSize = _size;
	extend();

	for (int x = oldSize - 1; x >= pos; x--)
	{
		data[x + 1] = data[x];
	}

	_size++;
	data[pos] = value;
}

template<typename T>
T List<T>::remove (int pos)
{
	T removed = data[pos];

	for (int x = pos; x < _size - 1; x++)
	{
		data[x] = data[x + 1];
	}

	_size--;
	return removed;
}

template<typename T>
bool List<T>::exists (int pos)
{
	return pos < _size;
}