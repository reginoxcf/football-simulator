#include <bits/stdc++.h>
using namespace std;
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
long long getRandomInteger(long long lowerBound, long long upperBound){
	//Returns a random integer between lowerBound and upperBound
	return rng() % (upperBound - lowerBound + 1) + lowerBound;
}

int main(){
	int n;
	cin >> n;
	freopen("teams.txt","w",stdout);
	cout << n << "\n";
	while(n--){
		for(int i =0; i< 3; i++) cout << char(getRandomInteger(0, 25)+'A');
		cout << " ";
		cout << getRandomInteger(1, 10000) << " " << getRandomInteger(1, 10000) << "\n";
	}
}
