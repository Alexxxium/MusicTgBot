#pragma once
#include "Command.h"
#include <exception>
#include <vector>

extern const std::string TOKEN;

namespace cmd::type
{
	extern const std::string MACRO, INLINE, ANY;
}

namespace err
{
	extern std::exception EMBARGO;
}

namespace init
{
	extern const std::vector<cmd::Command*> CMD_BASE;
}
