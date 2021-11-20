#include <vector>
#include "graph.h"


using namespace std;

int sum_weight(vector<edge>&  edges)
{
	int sum=0;
	for (int i=0; i<edges.size(); i++)
	{
		sum+=edges[i].weight;
	}
	return sum;
}

