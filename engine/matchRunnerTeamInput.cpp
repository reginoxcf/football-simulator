#include <bits/stdc++.h>
#include "engine.h"
using namespace std;
map<int, int> mp;

int main(){
	team h, a;
	cin >> h.att >> h.def >> a.att >> a.def;
	int w, d, l;
	w = d = l = 0;
	for(int i = 100; i; i--){
		pair<int, int> p = simulate(h, a);
		mp[p.first - p.second]++;
	}
	for(auto x:mp) cout << x.first << " " << x.second << "\n";
}
