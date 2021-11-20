
#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;


struct edge
{
	int x;
	int y;
	int weight;
	
};
struct adjacencyMatrix
{
	int vertex;
	int **relation;

	void showMatrix()
	{
		cout << endl;
		cout << "     ";
		for (int x = 0; x < vertex; x++)
		{
			cout << "  x";
			printf("%-2i", x);
			cout << " ";
		}
		for (int x = 0; x < vertex; x++)
		{
			cout << endl << " x" << x << " ";
			for (int j = 0; j < vertex; j++)
			{
				cout << "  ";
				printf("%3i", relation[j][x]);
				cout << " ";
			}
		}
	}
	void fillRandom(int n)
	{
		srand(time(NULL));
		int sum;
		relation = new int* [n];
		for (int x = 0; x < n; x++)
			relation[x] = new int[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				relation[i][j] = 0;

		for (int i=0; i<n; i++)
			for (int j = 0; j < i; j++)
			{
					relation[i][j] = rand() % 100;
					relation[j][i] = relation[i][j];
			}
		for (int i=0; i<n; i++)
		{
			sum=0;
			for (int j=0; j<n; j++)
			{
				if (relation[i][j])
					sum++;
			}
			
			while(!sum)
			{
				for (int j = 0; j < n; j++)
				{
					relation[i][j] = rand() % 100;
					relation[j][i] = relation[i][j];
					if (relation[i][j])
						sum++;
				}
				
			}
		}
		vertex = n;
	}
	
	void fillManual()
	{
		int sum=0, n;
		cout<<"Enter dimension: ";
		cin>>n;
		relation = new int* [n];
		for (int x = 0; x < n; x++)
			relation[x] = new int[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				relation[i][j] = 0;

		for (int i=0; i<n; i++)
			for (int j = 0; j < i; j++)
			{
				cout<<i<<" "<<j<<" weight>>";
				cin>>relation[i][j];
				relation[j][i] = relation[i][j];
				
			}
			
		for (int i=0; i<n; i++)
		{
			sum=0;
			for (int j=0; j<n; j++)
			{
				if (relation[i][j])
					sum++;
			}
			
			while(!sum)
			{
				for (int j = 0; j < n; j++)
				{
					if (i==j)
						continue;
					cout<<i<<" "<<j<<" weight>>";
					cin>>relation[i][j];
					relation[j][i] = relation[i][j];
					if (relation[i][j])
						sum++;
				}	
			}
		}
		vertex = n;
	}
	
	
	int sumRelation()
	{
		int counter = 0;
		for (int i=0; i<vertex; i++)
			for (int j = 0; j <= i; j++)
				if (relation[i][j])
					counter++;
		return counter;
	}
	~adjacencyMatrix()
	{
		for (int i = 0; i < vertex; i++)
		{
			delete[] relation[i];
		}
	}

};


