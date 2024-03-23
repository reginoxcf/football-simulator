#include <bits/stdc++.h>
#include "engine.h"
#include <windows.h>
using namespace std;
const int maxTeams = 3000;
struct stats{
	int gf, ga, gd, pts, w, l, d, mp;
	string name;
} teamStats[maxTeams];
string command;
int teamLength = 3, teamAttLength = 5, teamDefLength = 5;

bool comp(stats &x, stats &y){
	if(x.pts != y.pts) return x.pts > y.pts;
	if(x.gd != y.gd) return x.gd > y.gd;
	if(x.gf != y.gf) return x.gf > y.gf;
	return x.w > y.w;
}

int noOfTeams;
team teamList[maxTeams+1];
vector<pair<int, int>> matches, matches2;

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
	cout << "#   | ";
	print("Club", teamLength);
	cout << "MP  | W   | D   | L   | GF   | GA   | GD   | Pts   |\n";
	int rnk = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 31);
	for(auto x:teamStats){
		rnk++;
		if(rnk == 3) SetConsoleTextAttribute(hConsole, 15);
		if(rnk == noOfTeams-1) SetConsoleTextAttribute(hConsole, 79);
		print(to_string(rnk), 4);
		print(x.name, teamLength);
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
	SetConsoleTextAttribute(hConsole, 15);
//	cout << "\n#   | Club | MP  | W   | D   | L   | GF   | GA   | GD   | Pts   |\n";
}

void simulateMatch(int id){
	ofstream file("matches.txt", ios::app);
	if(id % (noOfTeams/2) == 1) file << "\nMatchday " << (id+(noOfTeams/2)-1)/(noOfTeams/2) << ":\n";
    int ho = matches[id].first, aw = matches[id].second;
    pair<int, int> res = simulate(teamList[ho], teamList[aw]);
    cout << teamStats[ho].name << " " << res.first << " - " << res.second << " " << teamStats[aw].name << "\n";
    file << teamStats[ho].name << " " << res.first << " - " << res.second << " " << teamStats[aw].name << "\n";
    updateStats(ho, res);
    updateStats(aw, {res.second, res.first});
}

int main(){
	ofstream dele("matches.txt");
	dele.close();
	ifstream file("teams.txt");
	// freopen("results.txt","w",stdout);
	file >> noOfTeams;
	for(int i = 0; i < noOfTeams; i++){
		getline(file, teamStats[i].name);
		getline(file, teamStats[i].name);
		teamLength = max(teamLength, (int)teamStats[i].name.size()+2);
		file >> teamList[i].att >> teamList[i].def;
		teamAttLength = max(teamAttLength, (int)to_string(teamList[i].att).size()+2);
		teamDefLength = max(teamDefLength, (int)to_string(teamList[i].def).size()+2);
	}
	cout << "Teams imported from teams.txt\n";
	file.close();
	generateOrder(noOfTeams);
	for(auto [i, j]:matches) matches2.emplace_back(j, i);
	matches.insert(matches.end(), matches2.begin(), matches2.end());
    matches.insert(matches.begin(), {0, 0});
	cout << "Matches generated\nPress h for help!\n>>> ";
	int id = 0;
	while(true){
        cin >> command;
        if(command == "h"){
            cout << "h: help\n";
            cout << "st: print statistics\n";
            cout << "s: print standings\n";
            cout << "nm: simulate next match\n";
            cout << "nmd: simulate until end of matchday\n";
            cout << "tl: print team list\n";
        }
        else if(command == "s"){
            printStandings();
        }
        else if(command == "nm"){
            //next match
            id++; simulateMatch(id);
        }
        else if(command == "nmd"){
            //til we meet again
            id++; simulateMatch(id);
            while(id % (noOfTeams/2)){id++; simulateMatch(id);}
        }
        else if(command == "st"){
            cout << "Matches played: " << id << "\n";
            cout << "Current matchday: " << (id+noOfTeams/2-1)/(noOfTeams/2) << "\n";
            if(id < (noOfTeams)*(noOfTeams-1))
                cout << "Next match: " << teamStats[matches[id+1].first].name << " - " << teamStats[matches[id+1].second].name << "\n";
        }
        else if(command == "tl"){
        	print("Club", teamLength);
        	print("ATT", teamAttLength);
        	print("DEF", teamDefLength);
        	cout << "\n";
            for(int i = 0; i < noOfTeams; i++){
                print(teamStats[i].name, teamLength);
                print(to_string(teamList[i].att), teamAttLength);
                print(to_string(teamList[i].def), teamDefLength);
                cout << "\n";
            }
        }
        if(id >= (noOfTeams)*(noOfTeams-1)) break;
        cout << ">>> ";
	}
	cout << "Final Standings:\n";
	printStandings();
	freopen("results.txt","w",stdout);
	printStandings();
}
