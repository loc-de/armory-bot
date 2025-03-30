#pragma once
#include "graph.h"
#include <string>
//#include <vector>
#include <map>
using namespace std;

class Data {
private:
	map<int, Point> _points;
	//vector<Point> _points;
	Graph _graph;

public:
	static const string graph_path;

	Data() = default;
	~Data() = default;

	const Graph& graph() const;
	//const map<int, Point>& points() const;
	
	const map<int, Point>& points() const;
	void load();
	
};