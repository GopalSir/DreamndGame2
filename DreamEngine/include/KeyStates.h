#pragma once
#include <map>
#include <utility>
#include <glheaders.hpp>
namespace DREAM {
	class KeyStates
	{
	public:
		// first = pressed status, second = repeat or not
		static std::map<int, std::pair<bool,bool>> KeyState;
		static void setState(int _key, std::pair<bool,bool> _status) { KeyState[_key] = _status; };
	};

}

