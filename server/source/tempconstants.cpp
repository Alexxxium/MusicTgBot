#include "tempconstants.h"
#include <iostream>



namespace mb
{
	std::unordered_map<std::string, int> init::SRV_HANDLERS
	{
		{ "download",     3 },
		{ "upload",       2 },
		{ "upload_group", 2 }
	};
}