#include "data.h"
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

void Data::load() {
	fstream file;
	file.open(graph_path, fstream::in);
	
	string line;
	map<int, vector<int>> p_ns;
	while (getline(file, line)) {
		if (line[0] == '#')
			continue;

		stringstream l_ss(line);
		Point p;
		string ns_str;
		l_ss >> p.id() >> p.x() >> p.y() >> p.z() >> ns_str;
		_points[p.id()] = p;
		p_ns[p.id()] = {};

		stringstream ns_ss(ns_str);
		string neighbor_id;

		while (getline(ns_ss, neighbor_id, ','))
			p_ns[p.id()].push_back(stoi(neighbor_id));
	}

	for (auto ns : p_ns) {
		for (int id : ns.second) {
			if (p_ns.find(id) != p_ns.end())
				_graph.addEdge(ns.first, id);
		}
	}
		
}

const Graph& Data::graph() const {
	return _graph;
}

const map<int, Point>& Data::points() const {
	return _points;
}

//Point& Data::point(int id) {
//	return _points[id];
//}
