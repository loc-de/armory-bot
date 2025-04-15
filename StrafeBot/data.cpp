#include "data.h"
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "constants.h"

using namespace std;

void Data::load() {
	fstream file;
	file.open(vars::graph_path, fstream::in);
	
	string line;
	map<int, vector<int>> mp_ns;
	while (getline(file, line)) {
		if (line[0] == '#')
			continue;

		stringstream l_ss(line);
		MapPoint mp;
		string ns_str;
		l_ss >> mp.id() >> mp.p().x() >> mp.p().y() >> mp.p().z() >> ns_str >> mp.jump();
		_map_points[mp.id()] = mp;
		mp_ns[mp.id()] = {};

		stringstream ns_ss(ns_str);
		string neighbor_id;

		while (getline(ns_ss, neighbor_id, ','))
			mp_ns[mp.id()].push_back(stoi(neighbor_id));
	}

	for (auto ns : mp_ns) {
		for (int id : ns.second) {
			if (mp_ns.find(id) != mp_ns.end())
				_graph.addEdge(ns.first, id, mapPoint(ns.first).p().distanceTo(mapPoint(id).p()));
		}
	}
		
}

const Graph& Data::graph() const {
	return _graph;
}

const map<int, MapPoint>& Data::mapPoints() const {
	return _map_points;
}

const MapPoint& Data::mapPoint(const int id) const {
	return _map_points.at(id);
}

const Path& Data::path(const int s_id, const int e_id) {
	if (_paths.find(s_id) != _paths.end())
		return _paths[s_id];

	_paths[s_id] = _graph.pathTo(s_id, e_id);;
	return _paths[s_id];
}
