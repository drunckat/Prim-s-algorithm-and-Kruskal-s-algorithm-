#include <vector>
#include "graph.h"
#include <iostream>
void filledges(vector<edge>&  edges, const adjacencyMatrix&  graph)
{
	edge T;
	for (int i=0; i< graph.vertex; i++)
	{
		for (int j=i; j< graph.vertex; j++)
		{
			if (graph.relation[i][j])
			{
				T.x=i;
				T.y=j;
				T.weight=graph.relation[i][j];
				edges.push_back(T);
			}
		}
	}
}
