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
    vector<int> tmp; tmp.clear();
    for(int i = 0; i < n; i++) tmp.push_back(i);
	for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n/2; j++){
            matches.emplace_back(tmp[j], tmp[n-j-1]);
        }
        int k = tmp[1];
        tmp.erase(tmp.begin() + 1);
        tmp.push_back(k);
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

void printStandings(){
    sort(teamStats, teamStats+noOfTeams, comp);
	cout << "#   | Club | MP  | W   | D   | L   | GF   | GA   | GD   | Pts   |\n";
	int rnk = 0;
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hConsole, 31);
	for(auto x:teamStats){
		rnk++;
//		if(rnk == 5) SetConsoleTextAttribute(hConsole, 47);
//		if(rnk == 6) SetConsoleTextAttribute(hConsole, 63);
//		if(rnk == 7) SetConsoleTextAttribute(hConsole, 15);
//		if(rnk == noOfTeams-2) SetConsoleTextAttribute(hConsole, 111);
//		if(rnk == noOfTeams-1) SetConsoleTextAttribute(hConsole, 79);
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
		cout << "\n";
		if(rnk >= noOfTeams) break;
	}
//	SetConsoleTextAttribute(hConsole, 15);
//	cout << "\n#   | Club | MP  | W   | D   | L   | GF   | GA   | GD   | Pts   |\n";
}

int main(){
	freopen("teams.txt","r",stdin);
	// freopen("results.txt","w",stdout);
	cin >> noOfTeams;
	for(int i = 0; i < noOfTeams; i++){
		cin >> teamStats[i].name >> teamList[i].att >> teamList[i].def;
	}
//	for(int i = 0; i < noOfTeams; i++){
//        cout << teamStats[i].name << " " << teamList[i].att << " " << teamList[i].def << "\n";
//	}
	generateOrder(noOfTeams);
	pair<int, int> res;
	for(auto [i, j]:matches) matches.emplace_back(j, i);
	int id = -1, ho, aw;
	for(int i = 0; i < 2*noOfTeams-2; i++){
        cout << "Matchday " << i+1 << "\n";
        for(int j = 0; j < noOfTeams/2; j++){
            id++;
            ho = matches[id].first, aw = matches[id].second;
            res = simulate(teamList[ho], teamList[aw]);
            cout << teamStats[ho].name << " " << res.first << " - " << res.second << " " << teamStats[aw].name << "\n";
            updateStats(ho, res);
            updateStats(aw, {res.second, res.first});
        }
        printStandings();
	}
}
