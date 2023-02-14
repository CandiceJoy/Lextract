#include <regex>
#include "wad.h"
#include "util.h"
#include "map.h"

using namespace std;

int main (int argc,char **argv)
{
	// Map Test
	/*Map<string,string> test;
	test.put("key","value");
	test.put("key2","value2");
	test.put("a","banana");
	test.put("key","altkey");
	test.remove("key");

	List<MapPair<string,string>> pairs3 = test.getPairs();

	for (int x = 0; x < pairs3.size(); x++)
	{
		MapPair<string,string> pair = pairs3[x];
		printf("%spairs[%s] = %s\n",(x > 0 ? (pair.key < pairs3[x - 1].key ? "<" : ">") : ""),pair.key.c_str(),pair.value.c_str());
	}

	return 0;*/

	string baseWadPath;
	string wadPath;
	bool   expecting     = false;
	string expectingWhat = "";

	for (int x = 1; x < argc; x++)
	{
		bool   longFlag  = false;
		bool   shortFlag = false;
		bool   flag      = false;
		string arg       = string(argv[x]);

		regex  longFlagRegex(R"(--([^\s-]+))",std::regex_constants::icase | std::regex_constants::ECMAScript);
		regex  shortFlagRegex(R"(-([^\s-]+))",std::regex_constants::icase | std::regex_constants::ECMAScript);
		smatch longMatches;
		smatch shortMatches;

		longFlag = regex_search(arg,longMatches,longFlagRegex);
		if (longFlag) arg        = longMatches[1];
		if (!longFlag) shortFlag = regex_search(arg,shortMatches,shortFlagRegex);
		if (shortFlag) arg       = shortMatches[1];
		flag = longFlag || shortFlag;

		if (expecting)
		{
			if (flag)
			{
				printf("Error: Invalid parameter for %s\n",expectingWhat.c_str());
				return 1;
			}

			printf("Variable %s = %s\n",expectingWhat.c_str(),arg.c_str());
			expecting     = false;
			expectingWhat = "";
			continue;
		}

		if (flag)
		{
			expecting = true;
			expectingWhat = arg;
			continue;
		}


	}

	return 0;

	string filepath = "/Users/candice/Dropbox/SaveGames/doom/IWads/strife1.wad";
	Wad    wad      = *new Wad(filepath);
	wad.load();

	return 0;
}