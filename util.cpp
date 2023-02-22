//
// Created by Candice Neill on 2/7/23.
//
#include <regex>
#include "util.h"

using namespace std;

string util::asString (byte* list,ulong start,ulong amt)
{
	string str = "";

	for (ulong x = 0; x < amt; x++)
	{
		char c = (char) list[start + x];

		if( c != '\0' )
		{
			str += c;
		}
	}

	return str;
}

string util::asUppercaseString (byte* list,ulong start,ulong amt)
{
	return util::toUppercase(util::asString(list,start,amt));
}

string util::asLowercaseString (byte* list,ulong start,ulong amt)
{
	return util::toLowercase(util::asString(list,start,amt));
}

long util::asInt(byte* list, ulong start, ulong amt)
{
	int ret = 0;

	for (ulong x = start; x < start + amt; x++)
	{
		ret += (int)list[x] << 8 * x;
	}

	return ret;
}

ulong util::asUInt(byte* list, ulong start, ulong amt)
{
	ulong ret = 0;

	for (ulong x = start; x < start + amt; x++)
	{
		ret += (ulong)list[x] << 8 * (x-start);
	}

	return ret;
}

byte* util::asBytes (byte* list,ulong start,ulong amt)
{
	byte* bytes = new byte[amt];

	for (ulong x = 0; x < amt; x++)
	{
		bytes[x] = list[start + x];
	}

	return bytes;
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

string util::asHexString(byte* list, ulong start, ulong amt)
{
	string ret = "";

	for (ulong x = 0; x < amt; x++)
	{
		int b = (int)list[start + x];
		int b1 = b & 0b00001111;
		int b2 = (b & 0b11110000) >> 4;

		if(b1>16||b2>16) throw std::runtime_error("Nibble > 16");

		if(b1<10) ret += std::to_string(b1);
		else ret += (char)(b1-10+'a');

		if(b2<10) ret += std::to_string(b2);
		else ret += (char)(b2-10+'a');

		if(x<amt-1&&x%2==1) ret += " ";
	}

	return ret;
}