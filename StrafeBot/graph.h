#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "point.h"
using namespace std;

class Graph {
private:
	unsigned int _vertex_c = 0;
	unsigned int _edge_c = 0;
	map<int, vector<int>> _adj = {};

public:
	Graph() = default;
	~Graph() = default;

	const map<int, vector<int>>& adj() const;

	void addVertex(int);
	void addEdge(int, int);
	vector<int> pathTo(int, int) const;
	void print() const;
	//void verify(const map<int, Point>&);
};