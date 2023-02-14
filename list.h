//
// Created by Candice Neill on 2/7/23.
//

#ifndef LUMPREADER_LIST_H
#define LUMPREADER_LIST_H

template<typename T>
class List
{
private:
	const int growBy = 10;
	int _size = 0;
	int maxSize = growBy;
	T* data;
	void extend();
public:
	explicit List(int sizeIn=0);
	[[nodiscard]] inline unsigned int size () const;
	void insert(int pos, T value);
	T remove(int pos);
	bool exists(int pos);
	void operator+= (T t);
	T& operator[] (long loc);
	const T& operator[] (long loc) const;
	T &operator* () const;
	T *operator-> ();
};

#include "list.cpp"

#endif //LUMPREADER_LIST_H
