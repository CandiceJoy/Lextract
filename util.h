//
// Created by Candice Neill on 2/7/23.
//

#ifndef LUMPREADER_UTIL_H
#define LUMPREADER_UTIL_H

using namespace std;

class util
{
public:
	static string asString (byte *list,int start,int amt = 4);
	static string asUppercaseString (byte *list,int start,int amt = 4);
	static string asLowercaseString (byte *list,int start,int amt = 4);
	static int asInt (byte *list,int start,int amt = 4);
	static byte asBytes (byte *list,long start,long amt);
	static string toUppercase(string in);
	static string toLowercase(string in);
};


#endif //LUMPREADER_UTIL_H
