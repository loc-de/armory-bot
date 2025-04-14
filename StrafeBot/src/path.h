#pragma once
#include <vector>
#include <iostream>
using namespace std;

struct Path {
	double dis;
	vector<int> path;

	Path(const double dis = 0, const vector<int>& path = vector<int>{});
};

ostream& operator<<(ostream&, const Path&);
