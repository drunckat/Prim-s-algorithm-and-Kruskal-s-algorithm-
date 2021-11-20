#include <vector>
#include "graph.h"
#include <iostream>

using namespace std;

void showEdges(vector<edge>&  edges)
{

	printf ("\n    x    y    weight");
	for (int i=0; i<edges.size(); i++)
	{
		printf ("\n%5i%5i%5i", edges[i].x, edges[i].y, edges[i].weight);
	}
}

