//
// Created by Candice Neill on 2/7/23.
//
#include <iostream>
#ifndef LUMPREADER_UTIL_H
#define LUMPREADER_UTIL_H
typedef std::byte byte;
typedef std::string string;
typedef unsigned long ulong; // Unsigned long

class util
{
public:
	static string asString (byte* list,ulong start,ulong amt = 4);
	static string asUppercaseString (byte* list,ulong start,ulong amt = 4);
	static string asLowercaseString (byte* list,ulong start,ulong amt = 4);
	static ulong asUInt(byte* list, ulong start, ulong amt = 4);
	static long asInt(byte* list, ulong start, ulong amt = 4);
	static byte* asBytes (byte* list,ulong start,ulong amt);
	static string asHexString(byte* list, ulong start, ulong amt);
	static string toUppercase(string in);
	static string toLowercase(string in);
};


#endif //LUMPREADER_UTIL_H
