#pragma once

#include <string>

namespace gw
{
std::string generateRandomWord()
{
	std::string buffString;
	for (int i = 0, last = (rand() % 12) + 3; i < last; i++)
		buffString.push_back(97 + (rand() % 24));
	buffString[0] = toupper(buffString[0]);
	return buffString;
}
};