#pragma once
#include <vector>

class QLerner
{
public:
	//Dimensionen: BallpositionX, BallpositionY, TischX, VelocityX, VelocityY
	std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> R;
	std::vector<std::vector<std::vector<std::vector<std::vector<int>>>>> Q;
	double gamma;
	int xMax, yMax, tableMax;
	QLerner(int x, int y, double gamma, int tableMax);
	~QLerner();
	int getActionValue(int BallX, int BallY, int TischX, int VelocityX, int VelocityY);
	int getBestNextAction(int BallX, int BallY, int TischX, int VelocityX, int VelocityY);
	void writeReward(int BallX, int BallY, int TischX, int VelocityX, int VelocityY, int reward);
};

