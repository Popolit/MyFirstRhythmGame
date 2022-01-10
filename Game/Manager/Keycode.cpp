#include "stdafx.h"
#include "Keycode.h"

namespace Keycode
{
	std::string toString(size_t const& code)
	{
		std::map<size_t, std::string>::const_iterator it = KeyMap.find(code);
		if (it == KeyMap.end()) return "unknown";
		return it->second;
	}
}