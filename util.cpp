//
// Created by Candice Neill on 2/7/23.
//
#include <regex>
#include "util.h"

using namespace std;

string util::asString (byte *list,int start,int amt)
{
	string str;

	for (int x = 0; x < amt; x++)
	{
		char c = (char) list[start + x];

		if( c != '\0' )
		{
			str += c;
		}
	}

	return str;
}

string util::asUppercaseString (byte *list,int start,int amt)
{
	return util::toUppercase(util::asString(list,start,amt));
}

string util::asLowercaseString (byte *list,int start,int amt)
{
	return util::toLowercase(util::asString(list,start,amt));
}

int util::asInt (byte *list,int start,int amt)
{
	int ret = 0;

	for (int x = start; x < start + amt; x++)
	{
		ret += (int)list[x] << 8 * x;
	}

	return ret;
}

byte util::asBytes (byte *list,long start,long amt)
{
	byte *bytes = new byte[amt];

	for (int x = 0; x < amt; x++)
	{
		bytes[x] = list[start + x];
	}

	return *bytes;
}

string util::toUppercase(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

string util::toLowercase(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}