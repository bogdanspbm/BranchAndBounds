#include <vector>
#include "VertexUtils.h"
//#include "DistanceMatrix.h"

using namespace std; 

class Bound {
	DistanceMatrix bound_matrix;
	vector<vector<float>> fines_matrix;
	bool fines_calculated = false;
	bool isFree = true;

public:
	float length;

	Bound(DistanceMatrix matrix, float len) {
		this->bound_matrix = matrix;
		this->length = len;
	}

	Bound *including_edge;
	Bound *not_including_edge;


	void setFineMatrix(vector<vector<float>> matrix) {
		this->fines_matrix = matrix;
		this->fines_calculated = true;
	}

	bool calculateChildrenBounds() {
		
		if (this->bound_matrix.matrix.size() == 1) {
			return false;
		}

		MatrixAndLength reduction_result = rowsAndColumnsReduction(bound_matrix.matrix);;
		if (this->length == 0) {
			this->length = reduction_result.lenght;
			reduction_result.lenght = 0;
		}

		this->setFineMatrix(calculateFinesMatrix(reduction_result.matrix));

		DistanceMatrix matrix_with_headers = DistanceMatrix();
		matrix_with_headers.matrix = this->fines_matrix;
		matrix_with_headers.horizontal_headers = bound_matrix.horizontal_headers;
		matrix_with_headers.vertical_headers = bound_matrix.vertical_headers;

		FineCoords coords = getMaxFineCoords(matrix_with_headers);
		matrix_with_headers.matrix = reduction_result.matrix;

		DistanceMatrix matrix_including_edge = matrixReduction(matrix_with_headers, coords.x, coords.y);
		
		//MatrixAndLength edge_reduction = rowsAndColumnsReduction(matrix_including_edge);

		DistanceMatrix matrix_not_including_edge = blockEdge(matrix_with_headers, coords.x, coords.y);

		MatrixAndLength reduction_for_additional_len = rowsAndColumnsReduction(matrix_including_edge.matrix);;

		Bound *edge_bound = new Bound(matrix_including_edge, this->length + reduction_for_additional_len.lenght);
		Bound *block_edge_bound = new Bound(matrix_not_including_edge, coords.fine + this->length);

		this->isFree = false;
		this->including_edge = edge_bound;
		this->not_including_edge = block_edge_bound;

		return true;
	}

	Bound* getShortestFreeBound() {
		if (this->isFree) {
			return this;
		}
		else {
			Bound *first = this->including_edge->getShortestFreeBound();
			Bound *second = this->not_including_edge->getShortestFreeBound();

			if (first->length < second->length) {
				return first;
			}
			else {
				return second;
			}
		}
	}

	int getDepth(int depth) {
		if (!this->isFree) {
			int a = this->including_edge->getDepth(depth + 1);
			int b = this->not_including_edge->getDepth(depth + 1);

			if (a > b) {
				return a;
			}
			else {
				return b;
			}
		}
		else {
			return depth;
		}
	}

	void displayBound() {
		int depth = this->getDepth(0);
		printf(" ");
		for (int i = 0; i <= depth; i++) {
			printf("%i", i);
			printf("       ");
		}
		cout << endl << endl;
		this->printBoundByDepthAndCoord(1, 0, depth);
	}

	void printBoundByDepthAndCoord(int coord, int depth, int max_depth) {
		if (!this->isFree) {
			this->including_edge->printBoundByDepthAndCoord(coord * 2 - 1, depth + 1, max_depth);
		}
		// print self;
		for (int i = 0; i < depth; i++) {
			printf("        ");
			
		}
		printf("%6.2f\n",this->length);

		if (!this->isFree) {
			this->not_including_edge->printBoundByDepthAndCoord(coord * 2, depth + 1, max_depth);
		}
	}

};