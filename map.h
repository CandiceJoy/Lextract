//
// Created by Candice Neill on 2/13/23.
//

#include <string>
#include "list.h"

#ifndef LEXTRACT_MAP_H
#define LEXTRACT_MAP_H

template<typename T, typename V>
struct MapPair
{
	T key;
	V value;
};

template<typename T, typename V>
class Map
{
private:
	static const int   NOT_FOUND = -1;
	List<MapPair<T,V>> pairs;
	int getIndex(T key, bool insertionPoint=false);
public:
	//explicit Map(int sizeIn=0);
	//void operator+= (T t);
	explicit Map();
	[[nodiscard]] inline unsigned int size() const;
	V get(T key);
	void put(T key, V value);
	V remove(T key);
	List<MapPair<T,V>> getPairs();
};

#include "map.cpp"

#endif //LEXTRACT_MAP_H