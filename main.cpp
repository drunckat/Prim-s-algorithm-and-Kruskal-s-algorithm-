#include <iostream>
#include <vector>
#include "graph.h"
#include "function.h"
#include <ctime>


//Это творение не мое, скопировал алгоритм с гугла, чтобы не терять время
void siftDown(vector<edge>& edges, int root, int bottom)
{
  int maxChild; 
  int done = 0; 
  while ((root * 2 <= bottom) && (!done)) 
  {
    if (root * 2 == bottom)    
      maxChild = root * 2;    
    else if (edges[root * 2].weight  > edges[root * 2 + 1].weight )
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
    if (edges[root].weight < edges[maxChild].weight ) 
    {
      edge temp = edges[root]; 
      edges[root] = edges[maxChild];
      edges[maxChild] = temp;
      root = maxChild;
    }
    else 
      done = 1; 
  }
}

void heapSort(vector<edge>& edges, int array_size) 
{
  for (int i = (array_size / 2); i >= 0; i--)
    siftDown(edges, i, array_size - 1);
  for (int i = array_size - 1; i >= 1; i--)
  {
    edge temp = edges[0];
    edges[0] = edges[i];
    edges[i] = temp;
    siftDown(edges, 0, i - 1);
  }
}
//Отсюда и дальше мой код

	
struct component
	{
		vector<int> references;
		int dimension;	
		void fill(int n)
		{
			for (int i=0; i<n; i++)
			{
				references.push_back(-1);
			}
			dimension = references.size();
		}
		int part(int vertex)
		{
	
			while (references[vertex]>0)
			{
				vertex=references[vertex];
			}
			return vertex;
		}
		void push_part(int i, int j)
		{
				references[i]=dimension;
				references[j]=dimension;
				references.push_back(-dimension);
				dimension++;
		}
		
	};

int main() {
	int n;
	cout<<"Number of vertexes>>";
	cin>>n;
	adjacencyMatrix graph;
//	graph.fillManual();
	graph.fillRandom(n);
//	graph.showMatrix();
	vector<edge> edges;
	filledges(edges, graph);

	clock_t t;
	//Kruskal's algorithm
	bool* touchedV = new bool[graph.vertex*graph.vertex];
	bool* checking = new bool[graph.vertex];
	int* components = new int[graph.vertex];
	for (int i=0; i<graph.vertex*graph.vertex; i++)
		touchedV[i]=0;
	t= clock();
	heapSort(edges, edges.size());
	cout<<"\nTime for sort:"<<clock()-t;
	{
		vector< edge > tree;
		int index=-1;
		t= clock();
	
		int i;
		int j;
		
		 
		component piramid;
		piramid.fill(graph.vertex);
	//	cout<<"\ndimension: "<<piramid.dimension;
		
		do
		{
			index++; 
			i=piramid.part(edges[index].y);
			j=piramid.part(edges[index].x);
		 //   piramid.references[edges[index].y]=i;
		 //   piramid.references[edges[index].x]=j;
			if  ( j != i )
			{
				tree.push_back(edges[index]);
				
				if (!( (i!=edges[index].y) ^ (j!=edges[index].x) )) 
				{
					piramid.push_part(j, i);
					piramid.references[edges[index].y]=piramid.dimension-1;
		       		piramid.references[edges[index].x]=piramid.dimension-1;
				}
				else if (i!=edges[index].y) 
				{
					piramid.references[j]=i;
				}
				else 
				{
					piramid.references[i]=j;
				}
			}		
		}while (tree.size() != (graph.vertex-1));
	//	cout<<"here";		
	//	cout<<"\ndimension: "<<piramid.dimension;
	//	showEdges(tree);
		cout<<endl<<"Sum of weight (Kraskala piramid): "<<sum_weight(tree)<<"\n time spent:"<<clock()-t;
	}
	{
		vector< edge > tree;
		int index=-1;
			t= clock();
		do
		{
			index++; 
			if  ((components[edges[index].y] != components[edges[index].x]) | (!components[edges[index].y]) )
			{
				tree.push_back(edges[index]);
				
				if (!(components[edges[index].y] or components[edges[index].x]))
				{
					components[edges[index].y]=index+1;
					components[edges[index].x]=index+1;
				}
				else if (!components[edges[index].y])
				{
					components[edges[index].y]=components[edges[index].x];
				}
				else if (!components[edges[index].x])
				{
					components[edges[index].x]=components[edges[index].y];
				}
				else
				{
					for (int i=0; i<edges[index].x; i++)
					{
						if (components[i]==components[edges[index].x])
							components[i]=components[edges[index].y];
					}
					for (int i=edges[index].x+1; i<graph.vertex; i++)
					{
						if (components[i]==components[edges[index].x])
							components[i]=components[edges[index].y];
					}
					components[edges[index].x]=components[edges[index].y];
				}
			}		
		}while (tree.size() != (graph.vertex-1));
	//	showEdges(tree);		
		cout<<endl<<"Sum of weight (Kraskala array): "<<sum_weight(tree)<<"\n time spent:"<<clock()-t;
	}
	{
		vector< edge > tree;
		int index=-1;
	

		
		t= clock();
		do
		{
			index++;
			if  (!(touchedV[edges[index].y + graph.vertex*edges[index].x])) 
			{
				
				tree.push_back(edges[index]);
				if (!(touchedV[edges[index].x] & touchedV[edges[index].y]))
				{
					touchedV[edges[index].x + graph.vertex*(edges[index].x) ]=1;
					touchedV[edges[index].y + graph.vertex*(edges[index].y) ]=1;
				}
				
				touchedV[edges[index].y + graph.vertex*(edges[index].x)]=1;
				touchedV[edges[index].x + graph.vertex*(edges[index].y)]=1;
				for (int i=0; i<graph.vertex; i++)
				{
					touchedV[edges[index].y + graph.vertex*i] = (touchedV[edges[index].y + graph.vertex*i] | touchedV[edges[index].x + graph.vertex*i]);
	   				touchedV[edges[index].x + graph.vertex*i] =  touchedV[edges[index].y + graph.vertex*i];
				}
				
				
				for (int i=0; i<(graph.vertex); i++)
				{
					if (touchedV[i+ graph.vertex*i])
						if (touchedV[edges[index].x + graph.vertex*i])
						{
							for (int j=0; j<graph.vertex; j++)
							{
						
								touchedV[i + graph.vertex*j]=touchedV[edges[index].x + graph.vertex*j];
							}
				
						}
				}
				
	
			}

			else
				continue;
		}while (tree.size() != (graph.vertex-1));
	//	showEdges(tree);
		cout<<endl<<"Sum of weight (Kraskala matrix): "<<sum_weight(tree)<<"\n time spent:"<<clock()-t;
	}
	//Prim's algorithm
	for (int i=0; i<graph.vertex; i++)
		checking[i]=0;
	{
		t=clock();	
		vector< edge > tree;
		int index=0;
		int index_min=-1;
		
		
		do
		{
			index_min=-1;
		//	min=2147483647;
			if (!index)
			{
				for (int i=0; i<edges.size(); i++)
				{
					if  (edges[i].x==0 | edges[i].y==0)
					{
						index_min=i;
						break;
					}
				}
				tree.push_back(edges[index_min]);
			
					checking[edges[index_min].x]=1;
		
					checking[edges[index_min].y]=1;
		
				edges.erase(edges.begin()+index_min);
				index++;
			}
			else
			{
				for (int i=0; i<edges.size(); i++)
				{					
					if (checking[edges[i].x] & checking[edges[i].y])
					{
					/*	edges.erase(edges.begin()+i);
						i--;*/
						continue;
					}
					if (checking[edges[i].x] ^ checking[edges[i].y])
					{
					//	min=edges[i].weight;
						index_min=i;
						break;
					}

				}
				tree.push_back(edges[index_min]);
			
				if (checking[edges[index_min].x])
					checking[edges[index_min].y]=1;
				else 
					checking[edges[index_min].x]=1;
				
			//	edges.erase(edges.begin()+index_min);
			}
		}while (tree.size() != (graph.vertex-1));
		
	//	showEdges(tree);
		cout<<endl<<"Sum of weight (Prima): "<<sum_weight(tree)<<"\n time spent:"<<clock()-t;
	}
	system("Pause>nul");
	delete[] touchedV;
	delete[] checking;
	delete[] components;
	//showEdges(edges);
	return 0;
}
