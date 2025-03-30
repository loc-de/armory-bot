#include "graph.h"
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

void Graph::addVertex(int id) {
	if (_adj.find(id) == _adj.end()) {
		_adj[id] = {};
		_vertex_c++;
	}
}

void Graph::addEdge(int id1, int id2) {
	addVertex(id1);
	addVertex(id2);
	
	for (int id : _adj[id1]) 
		if (id == id2) return;

	_adj[id1].push_back(id2);
	_adj[id2].push_back(id1);
	_edge_c++;
}

vector<int> Graph::pathTo(int s_id, int e_id) const {
	queue<int> q;
	map<int, int> parent;
	map<int, bool> visited;

	for (const auto& i : _adj)
		parent[i.first] = -1;
	for (const auto& i : _adj) 
		visited[i.first] = false;

	q.push(s_id);
	visited[s_id] = true;

	while (!q.empty()) {
		int c = q.front();
		q.pop();

		if (c == e_id)
			break;

		for (int n_id : _adj.at(c)) {
			if (!visited[n_id]) {
				q.push(n_id);
				visited[n_id] = true;
				parent[n_id] = c;
			}
		}
	}
	vector<int> path;
	path.push_back(e_id);
	while (path.back() != s_id) {
		path.push_back(parent[path.back()]);
	}
	reverse(path.begin(), path.end());
	return path;
}

void Graph::print() const {
	for (const auto& i : _adj) {
		cout << i.first << ": ";
		for (int n : i.second) {
			cout << n << ", ";
		}
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
