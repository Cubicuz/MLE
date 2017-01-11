#pragma once
#include <vector>

class QLerner
{
public:
	//Dimensionen: BallpositionX, BallpositionY, TischX, BallRichtungY, BallRichtungY
	std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> R;
	std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> Q;
	double gamma;

	QLerner(int x, int y, double gamma);
	~QLerner();
	

};

