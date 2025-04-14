#include "graph.h"
#include <vector>
#include <queue>
#include <set>
#include <iostream>
using namespace std;

const map<int, vector<pair<int, double>>>& Graph::adj() const {
	return _adj;
}

const set<pair<int, int>>& Graph::edges() const {
    return _edges;
}

void Graph::addVertex(int id) {
	if (_adj.find(id) == _adj.end()) {
		_adj[id] = {};
		_vertex_c++;
	}
}

void Graph::addEdge(int id1, int id2, double dis) {
	addVertex(id1);
	addVertex(id2);
	
	for (pair<int, double> item : _adj[id1])
		if (item.first == id2) return;

	_adj[id1].push_back(pair<int, double>(id2, dis));
    _edges.insert(pair<int, int>(min(id1, id2), max(id1, id2)));
	_edge_c++;
}

Path Graph::pathTo(const int s_id, const int e_id) const {
    map<int, double> dis;
    map<int, int> parent;
    set<pair<double, int>> pq;

    for (const auto& i : _adj) {
        dis[i.first] = (numeric_limits<double>::max)();
        parent[i.first] = -1;
    }

    dis[s_id] = 0.0;
    pq.insert({ 0.0, s_id });

    while (!pq.empty()) {
        int current = pq.begin()->second;
        double currentDist = pq.begin()->first;
        pq.erase(pq.begin());

        if (current == e_id)
            break;

        for (const auto& item : _adj.at(current)) {
            double newDist = currentDist + item.second;
            if (newDist < dis[item.first]) {
                pq.erase({ dis[item.first], item.first });
                dis[item.first] = newDist;
                parent[item.first] = current;
                pq.insert({ newDist, item.first });
            }
        }
    }

    vector<int> path;
    if (dis[e_id] == (numeric_limits<double>::max)())
        throw runtime_error("path to point not available");

    for (int at = e_id; at != -1; at = parent[at])
        path.push_back(at);
    reverse(path.begin(), path.end());
    return Path(dis[e_id], path);
}

//vector<int> Graph::pathTo(int s_id, int e_id) const {
//	queue<int> q;
//	map<int, int> parent;
//	map<int, bool> visited;
//
//	for (const auto& i : _adj)
//		parent[i.first] = -1;
//	for (const auto& i : _adj) 
//		visited[i.first] = false;
//
//	q.push(s_id);
//	visited[s_id] = true;
//
//	while (!q.empty()) {
//		int c = q.front();
//		q.pop();
//
//		if (c == e_id)
//			break;
//
//		for (int n_id : _adj.at(c)) {
//			if (!visited[n_id]) {
//				q.push(n_id);
//				visited[n_id] = true;
//				parent[n_id] = c;
//			}
//		}
//	}
//	vector<int> path;
//	path.push_back(e_id);
//	while (path.back() != s_id) {
//		path.push_back(parent[path.back()]);
//	}
//	reverse(path.begin(), path.end());
//	return path;
//}

void Graph::print() const {
	for (const auto& i : _adj) {
		cout << i.first << ": ";
        for (const auto& n : i.second)
            cout << "(" << n.first << ", " << n.second << "), ";
		cout << endl;
	}
	cout << endl;
}

//void Graph::verify(const map<int, Point>& ps) {
//	for (const auto& i_p : ps) {
//		for (int is : _adj[i_p.first]) {
//			cout << is << endl;
//		}
//	}
//}
