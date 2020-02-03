#include "WIN_Utils.h"

using namespace win;
using namespace utils;

bool win::utils::filterNumerical(const char c[])
{
	if ((*c >= '0' && *c <= '9')) {
		return true;
	}
	else {
		return false;
	}
}