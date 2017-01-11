#include "QLerner.h"



QLerner::QLerner(int x, int y, double gamma):
	R(x, std::vector<std::vector<std::vector<std::vector<int>>>>(y, std::vector<std::vector<std::vector<int>>>(x, std::vector<std::vector<int>>(2, std::vector<int>(2, (0)))))),
	Q(x, std::vector<std::vector<std::vector<std::vector<int>>>>(y, std::vector<std::vector<std::vector<int>>>(x, std::vector<std::vector<int>>(2, std::vector<int>(2, (0)))))),
	gamma(gamma)
{
}

QLerner::~QLerner()
{
}


