#include <vector>

using namespace std;

struct DistanceMatrix {
	vector<vector<float>> matrix;
	vector<int> horizontal_headers, vertical_headers;
};