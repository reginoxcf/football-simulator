#ifndef HEADER_6FE32AAB5ECBC19E
#define HEADER_6FE32AAB5ECBC19E
#include <ctime>
#include <random>

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
//Mersenne Twister Randomizer

const int goalLimit = 100, moveDistance = 2;

struct team{
	//Football team
	int att, def;
};

long long getRandomInteger(long long lowerBound, long long upperBound){
	//Returns a random integer between lowerBound and upperBound
	return rng() % (upperBound - lowerBound + 1) + lowerBound;
}

int moveDirection(team home, team away){
	int x = home.att + away.def, y = home.def + away.att;
//	long long surprise = std::min(getRandomInteger(150ll, 250ll), (long long)x*(long long)y/(long long)1e15);
	long long valueRng = getRandomInteger(1ll, 2ll * (long long)x * (long long)y);
	if(valueRng <= (long long)y * (long long)home.att) return 2;
	valueRng -= (long long)y * (long long)home.att;
	if(valueRng <= (long long)y * (long long)away.def) return -1;
	valueRng -= (long long)y * (long long)away.def;
	if(valueRng <= (long long)x * (long long)away.att) return -2;
	return 1;
}

std::pair<int, int> simulate(team home, team away){
	int seconds = 0, ballX = 0, homeGoals = 0, awayGoals = 0; //maximum = 90 * 60 = 5400
	while(seconds <= 5400){
		seconds += getRandomInteger(7, 13);
		ballX += moveDirection(home, away) * moveDistance;
		if(ballX <= -goalLimit) ++awayGoals;
		if(ballX >= goalLimit) ++homeGoals;
		if(abs(ballX) >= goalLimit) ballX = 0;
	}
	return {homeGoals, awayGoals};
}
#endif // header guard

