#include "QLerner.h"



QLerner::QLerner(int x, int y, double gamma, int tableMax) :
	R(x, std::vector<std::vector<std::vector<std::vector<int>>>>(y, std::vector<std::vector<std::vector<int>>>(x, std::vector<std::vector<int>>(2, std::vector<int>(2, (0)))))),
	Q(x, std::vector<std::vector<std::vector<std::vector<int>>>>(y, std::vector<std::vector<std::vector<int>>>(x, std::vector<std::vector<int>>(2, std::vector<int>(2, (0)))))),
	xMax(x),
	yMax(y),
	gamma(gamma),
	tableMax(tableMax)
{
}

QLerner::~QLerner()
{
}

int QLerner::getActionValue(int BallX, int BallY, int TischX, int VelocityX, int VelocityY)
{
	VelocityX = (VelocityX > 0 ? 0 : 1);
	VelocityY = (VelocityY > 0 ? 0 : 1);
	return Q[BallX / 10][BallY / 10][TischX / 10][VelocityX][VelocityY];
}



// -1 0 1
int QLerner::getBestNextAction(int BallX, int BallY, int TischX, int VelocityX, int VelocityY)
{
	BallX += VelocityX;
	BallY += VelocityY;
	int rewardl;
	int rewardr;
	int reward0 = getActionValue(BallX, BallY, TischX, VelocityX, VelocityY);
	if (TischX <= 0) {
		rewardl = -1000;
		rewardr = getActionValue(BallX, BallY, TischX + 10, VelocityX, VelocityY);
	}
	else if (TischX >= tableMax) {
		rewardl = getActionValue(BallX, BallY, TischX - 10, VelocityX, VelocityY);
		rewardr = -1000;
	}
	else {
		rewardl = getActionValue(BallX, BallY, TischX - 10, VelocityX, VelocityY);
		rewardr = getActionValue(BallX, BallY, TischX + 10, VelocityX, VelocityY);
	}
	if (rewardl == rewardr) {
		return 0;
	} 
	else if (rewardr > rewardl) {
		writeReward(BallX, BallY, TischX + 10, VelocityX, VelocityY, rewardr - 1);
		return 1;
	}
	else {
		writeReward(BallX, BallY, TischX - 10, VelocityX, VelocityY, rewardl - 1);
		return -1;
	}
}

void QLerner::writeReward(int BallX, int BallY, int TischX, int VelocityX, int VelocityY, int reward)
{
	VelocityX = (VelocityX > 0 ? 0 : 1);
	VelocityY = (VelocityY > 0 ? 0 : 1);
	Q[BallX / 10][BallY / 10][TischX / 10][VelocityX][VelocityY] = reward;
}


