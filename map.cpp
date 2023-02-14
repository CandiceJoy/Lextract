//
// Created by Candice Neill on 2/13/23.
//

#include "map.h"

template<typename T,typename V>
Map<T,V>::Map ()
{

}

template<typename T,typename V>
List<MapPair<T,V>> Map<T,V>::getPairs ()
{
	return pairs;
}

template<typename T,typename V>
int Map<T,V>::getIndex (T key,bool insertionPoint)
{
	printf("getIndex(%s)\n",key.c_str());

	int start  = 0;
	int end    = pairs.size();
	int index  = (start + end) / 2;

	if(end-start==0)
	{
		printf("\tReturn 0\n");
		return 0;
	}

	printf("\tSTART - start:%d, end:%d, index:%d\n", start,end,index);

	do
	{
		T currKey = pairs[index].key;
		printf("\tpairs[%d]: %s\n",index,currKey.c_str());

		if (currKey == key)
		{ return index; }
		else if (key < currKey)
		{ end = index; }
		else if (key > currKey) start = index;
		index = (start + end) / 2;
	}while (end-start > 1);

	printf("\tLOOPEND - start:%d, end:%d, index:%d\n", start,end,index);

	if (insertionPoint)
	{
		if(!pairs.exists(index)||pairs[index].key==key)
		{
			printf("\tReturn index (found)\n");
			return index;
		}
		if(pairs[index].key>key)
		{
			printf("\tReturn index (>)\n");
			return index-1;
		}
		if(pairs[index].key<key)
		{
			printf("\tReturn index + 1 (<)\n");
			return index + 1;
		}
	}
	else if(pairs[index].key==key)
	{
		return index;
	}
	else
	{ return NOT_FOUND; }
}

template<typename T,typename V>
[[nodiscard]] inline unsigned int Map<T,V>::size () const
{
	return pairs.size();
}

template<typename T,typename V>
V Map<T,V>::get (T key)
{
	int index = getIndex(key);
	if (index == NOT_FOUND)
	{ return NULL; }
	else
	{ return pairs[index].value; }
}

template<typename T,typename V>
void Map<T,V>::put (T key,V value)
{
	MapPair<T,V> pair;
	pair.key   = key;
	pair.value = value;

	if(pairs.size()==0)
	{
		pairs += pair;
		return;
	}

	int insertIndex = getIndex(key,true);
	if(insertIndex == NOT_FOUND) insertIndex=0;

	printf("\tInserting [%s] into [%d]\n",key.c_str(),insertIndex);

	if (!pairs.exists(insertIndex))
	{
		pairs += pair;
	}
		//if(insertIndex==NOT_FOUND) pairs += pair;
	else if (pairs[insertIndex].key == key)
	{ pairs[insertIndex].value = value; }
	else
	{ pairs.insert(insertIndex,pair); }
}

template<typename T,typename V>
V Map<T,V>::remove (T key)
{
	int deleteIndex = getIndex(key);

	if (deleteIndex == NOT_FOUND)
	{ return NULL; }
	else
	{ return pairs.remove(deleteIndex).value; }
}