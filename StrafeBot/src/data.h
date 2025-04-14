#pragma once
#include "graph.h"
#include "path.h"
#include <string>
#include <map>
using namespace std;

class Data {
private:
	map<int, MapPoint> _map_points;
	Graph _graph;
	map<int, Path> _paths;

public:
	const Graph& graph() const;
	const map<int, MapPoint>& mapPoints() const;
	const MapPoint& mapPoint(const int) const;
	const Path& path(const int, const int);
	void load();
};