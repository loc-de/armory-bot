#include "path.h"

Path::Path(const double dis, const vector<int>& path) : 
	dis(dis), path(path) {}

ostream& operator<<(ostream& os, const Path& path) {
	os << "dis: " << path.dis << " (";
	for (const int id : path.path)
		os << id << ", ";
	return os << ')';
}
