#pragma once
#include <unordered_map>
#include <functional>


namespace mb 
{
	class init {
	public:
		static std::unordered_map<std::string, int> SRV_HANDLERS;
	};
}