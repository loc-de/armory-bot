#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "point.h"
#include "mapPoint.h"
#include "path.h"
using namespace std;

class Graph {
private:
	unsigned int _vertex_c = 0;
	unsigned int _edge_c = 0;
	map<int, vector<pair<int, double>>> _adj = {};
	set<pair<int, int>> _edges;

public:
	const map<int, vector<pair<int, double>>>& adj() const;
	const set<pair<int, int>>& edges() const;

	void addVertex(int);
	void addEdge(int, int, double);
	Path pathTo(const int, const int) const;
	void print() const;
};
