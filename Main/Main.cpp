#include <iostream>
#include <vector>
#include "Vertexes.h"
#include "Bound.h"
#include "VertexUtils.h"

using namespace std;

int main()
{
	//vector<vertex> vertexes = generateVertexArray(15);
	float arr[25] = { 1000, 20, 18, 12, 8,5, 1000, 14, 7, 11,12, 18, 1000, 6, 11,11, 17, 11, 1000, 12,5, 5, 5, 5, 1000};
	DistanceMatrix matrix = array2Vec(arr, 5);
	Bound *parent_node = new Bound(matrix, 0);
	parent_node->calculateChildrenBounds();
	bool flag;
	do{
		Bound *last_bound = parent_node->getShortestFreeBound();
 		flag = last_bound->calculateChildrenBounds();
	} while (flag == true);

	parent_node->displayBound();

}