#include <bits/stdc++.h>
using namespace std;
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
long long getRandomInteger(long long lowerBound, long long upperBound){
	//Returns a random integer between lowerBound and upperBound
	return rng() % (upperBound - lowerBound + 1) + lowerBound;
}

int main(){
	int n;
	cout << "Enter number of teams (even):";
	cin >> n;
	ofstream file("teams.txt");
	file << n << "\n";
	while(n--){
		for(int i = 0; i < 3; i++) file << char(getRandomInteger(0, 25)+'A');
		file << " ";
		file << getRandomInteger(1, 10000) << " " << getRandomInteger(1, 10000) << "\n";
	}
	file.close();
	cout << "Generated " << n << " random teams! Please close this window and run simulator.cpp.";
}
