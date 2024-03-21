#include <bits/stdc++.h>
#include "engine.h"
#include <windows.h>
using namespace std;
const int maxTeams = 3000;
struct stats{
	int gf, ga, gd, pts, w, l, d, mp;
	string name;
} teamStats[maxTeams];

bool comp(stats &x, stats &y){
	if(x.pts != y.pts) return x.pts > y.pts;
	if(x.gd != y.gd) return x.gd > y.gd;
	if(x.gf != y.gf) return x.gf > y.gf;
	return x.w > y.w;
}

int noOfTeams;
team teamList[maxTeams+1];
vector<pair<int, int>> matches;

void generateOrder(int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i==j) continue;
			matches.emplace_back(i, j);
		}
	}
}

void updateStats(int id, pair<int, int> res){
	teamStats[id].gf += res.first;
	teamStats[id].ga += res.second;
	teamStats[id].gd += res.first - res.second;
	teamStats[id].mp++;
	if(res.first > res.second){teamStats[id].w++; teamStats[id].pts+=3;}
	else if(res.first < res.second) teamStats[id].l++;
	else{teamStats[id].d++, teamStats[id].pts++;}
}

void print(string s, int sp){
	cout << s;
	sp -= s.size();
	while(sp--) cout << " ";
	cout << "| ";
}

int main(){
	freopen("teams.txt","r",stdin);
	freopen("results.txt","w",stdout);
	cin >> noOfTeams;
	for(int i = 0; i < noOfTeams; i++){
		cin >> teamStats[i].name >> teamList[i].att >> teamList[i].def;
	}
	shuffle(teamList, teamList+noOfTeams, rng);
	generateOrder(noOfTeams);
	shuffle(matches.begin(), matches.end(), rng);
	pair<int, int> res;
	for(auto [i, j]:matches){
		res = simulate(teamList[i], teamList[j]);
		cout << teamStats[i].name << " " << res.first << " - " << res.second << " " << teamStats[j].name << "\n";
		updateStats(i, res);
		updateStats(j, {res.second, res.first});
	}
	sort(teamStats, teamStats+noOfTeams, comp);
	cout << "#   | Club | MP  | W   | D   | L   | GF   | GA   | GD   | Pts   |\n";
	int rnk = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 31);
	for(auto x:teamStats){
		rnk++;
		if(rnk == 5) SetConsoleTextAttribute(hConsole, 47);
		if(rnk == 6) SetConsoleTextAttribute(hConsole, 63);
		if(rnk == 7) SetConsoleTextAttribute(hConsole, 15);
		if(rnk == noOfTeams-2) SetConsoleTextAttribute(hConsole, 111);
		if(rnk == noOfTeams-1) SetConsoleTextAttribute(hConsole, 79);
		print(to_string(rnk), 4);
		print(x.name, 5);
		print(to_string(x.mp), 4);
		print(to_string(x.w), 4);
		print(to_string(x.d), 4);
		print(to_string(x.l), 4);
		print(to_string(x.gf), 5);
		print(to_string(x.ga), 5);
		print(to_string(x.gd), 5);
		print(to_string(x.pts), 6);
		if(rnk >= noOfTeams) break;
		cout << "\n";
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << "\n#   | Club | MP  | W   | D   | L   | GF   | GA   | GD   | Pts   |";
}
