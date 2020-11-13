#pragma once
#include <vector>
#include "Vertexes.h"
#include "MatrixAndLength.h"
#include "FineCoords.h"
#include "DistanceMatrix.h"

vector<vertex> generateVertexArray(int size);
DistanceMatrix generateDistanceMatrix(vector<vertex> points);
void displayMatrix(vector<vector<float>> matrix);
MatrixAndLength rowsAndColumnsReduction(vector<vector<float>> matrix);
vector<vector<float>> calculateFinesMatrix(vector<vector<float>> matrix);
DistanceMatrix matrixReduction(DistanceMatrix matrix, int row, int col);
vector<vector<float>> fineMatrixReduction(vector<vector<float>> matrix, int row, int col);
FineCoords getMaxFineCoords(DistanceMatrix matrix);
DistanceMatrix blockEdge(DistanceMatrix matrix, int row, int col);
DistanceMatrix array2Vec(float *arr, int size);