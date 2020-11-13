#include <vector>
#include "Vertexes.h"
#include "MatrixAndLength.h"
#include "FineCoords.h"
#include "DistanceMatrix.h"

using namespace std;

vector<vertex> generateVertexArray(int size) {

	vector<vertex> result;
	for (int i = 0; i < size; i++) {
		float x = rand() % 100;
		float y = rand() % 100;
		vertex dot = vertex(x, y);
		result.push_back(dot);
	}

	return result;
}

DistanceMatrix generateDistanceMatrix(vector<vertex> points) {
	DistanceMatrix result;

	vector<vector<float>> matrix = vector<vector<float>>();
	vector<int> horiz = vector<int>();
	vector<int> vert = vector<int>();

	for (size_t i = 0; i < points.size(); i++) {
		vector<float> row = vector<float>();
		horiz.push_back(i);
		vert.push_back(i);
		for (size_t k = 0; k < points.size(); k++) {
			if (i != k) {
				row.push_back(points.at(i).distanceTo(points.at(k)));
			}
			else {
				row.push_back(1000);
			}
		}
		matrix.push_back(row);
	}
	result.matrix = matrix;
	result.horizontal_headers = horiz;
	result.vertical_headers = vert;
	return result;
}

MatrixAndLength rowsAndColumnsReduction(vector<vector<float>> matrix) {
	size_t len = matrix.size();
	float lenght = 0;

	// Row reduction
	for (size_t i = 0; i < len; i++) {
		float h_i = -1;

		for (size_t k = 0; k < len; k++) {
			if (h_i == -1 || matrix.at(i).at(k) < h_i) {
				h_i = matrix.at(i).at(k);
			}
		}

		for (size_t k = 0; k < len; k++) {
			matrix.at(i).at(k) -= h_i;
		}

		lenght += h_i;
	}

	// Column reduction
	for (size_t i = 0; i < len; i++) {
		float h_j = -1;

		for (size_t k = 0; k < len; k++) {
			if (h_j == -1 || matrix.at(k).at(i) < h_j) {
				h_j = matrix.at(k).at(i);
			}
		}

		for (size_t k = 0; k < len; k++) {
			matrix.at(k).at(i) -= h_j;
		}

		lenght += h_j;
	}

	MatrixAndLength result;
	result.matrix = matrix;
	result.lenght = lenght;

	return result;
}

vector<vector<float>> calculateFinesMatrix(vector<vector<float>> matrix) {
	size_t len = matrix.size();
	vector<vector<float>> r_matrix = vector<vector<float>>();

	for (size_t i = 0; i < len; i++) {
		vector<float> row = vector<float>();
		for (size_t k = 0; k < len; k++) {
			if (matrix.at(i).at(k) != 0) {
				row.push_back(0);
			}
			else {
				// Calculate Fine
				float min_row = -1, min_col = -1;

				for (size_t j = 0; j < len; j++)
				{
					if (j != i) {
						if (min_row == -1 || matrix.at(j).at(k) < min_row) {
							min_row = matrix.at(j).at(k);
						}
					}

					if (j != k) {
						if (min_col == -1 || matrix.at(i).at(j) < min_col) {
							min_col = matrix.at(i).at(j);
						}
					}
				}

				row.push_back(min_col + min_row);
			}
		}
		r_matrix.push_back(row);
	}
	return r_matrix;
}


DistanceMatrix blockEdge(DistanceMatrix matrix, int row, int col) {
	for (size_t i = 0; i < matrix.horizontal_headers.size(); i++) {
		if (matrix.horizontal_headers.at(i) == row) {
			for (size_t k = 0; k < matrix.vertical_headers.size(); k++) {
				if (matrix.vertical_headers.at(k) == col)
				{
					matrix.matrix.at(i).at(k) = 1000;
					return matrix;
				}
			}
		}
	}
	return matrix;
}

FineCoords getMaxFineCoords(DistanceMatrix matrix) {
	float max_fine = -1;
	size_t len = matrix.matrix.size();
	int x, y;

	for (size_t i = 0; i < len; i++) {
		for (size_t k = 0; k < len; k++) {
			if (matrix.matrix.at(i).at(k) > max_fine)
			{
				max_fine = matrix.matrix.at(i).at(k);
				x = i;
				y = k;
			}
		}
	}

	FineCoords result;
	result.x = matrix.horizontal_headers.at(x);
	result.y = matrix.vertical_headers.at(y);
	result.fine = max_fine;
	return result;
}

DistanceMatrix matrixReduction(DistanceMatrix matrix, int row, int col) {
	matrix = blockEdge(matrix, col, row);
	int x, y;

	for (size_t i = 0; i < matrix.horizontal_headers.size(); i++) {
		if (matrix.horizontal_headers.at(i) == row) {
			for (size_t k = 0; k < matrix.vertical_headers.size(); k++) {
				if (matrix.vertical_headers.at(k) == col)
				{
					x = i;
					y = k;
				}
			}
		}
	}

	matrix.matrix.erase(matrix.matrix.begin() + x);

	for (size_t i = 0; i < matrix.matrix.size(); i++) {
		matrix.matrix.at(i).erase(matrix.matrix.at(i).begin() + y);
	}

	matrix.horizontal_headers.erase(matrix.horizontal_headers.begin() + x);
	matrix.vertical_headers.erase(matrix.vertical_headers.begin() + y);

	return matrix;
}

vector<vector<float>> fineMatrixReduction(vector<vector<float>> matrix, int row, int col) {
	matrix.at(col).at(row) = 0;

	matrix.erase(matrix.begin() + row);

	for (size_t i = 0; i < matrix.size(); i++) {
		matrix.at(i).erase(matrix.at(i).begin() + col);
	}

	return matrix;
}


void displayMatrix(vector<vector<float>> matrix) {
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t k = 0; k < matrix.at(i).size(); k++) {
			printf("%6.2f ", matrix.at(i).at(k));
		}
		cout << endl;
	}
	cout << endl;
}

DistanceMatrix array2Vec(float *arr, int size) {
	vector<vector<float>> matrix = vector<vector<float>>();
	vector<int> vertical_headers = vector<int>();
	vector<int> horizontal_headers = vector<int>();
	DistanceMatrix result = DistanceMatrix();

	for (int i = 0; i < size; i++)
	{	
		vertical_headers.push_back(i);
		horizontal_headers.push_back(i);
		vector<float> row = vector<float>();
		for (int k = 0; k < size; k++) {
			row.push_back(arr[i*size + k]);
		}
		matrix.push_back(row);
	}

	result.matrix = matrix;
	result.horizontal_headers = horizontal_headers;
	result.vertical_headers = vertical_headers;

	return result;
}