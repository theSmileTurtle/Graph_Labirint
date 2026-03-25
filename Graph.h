#pragma once
#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<queue>

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

// граф представл€етс€ в виде списков смежности
class Graph {
	int vertexCount, edgeCount;
	vector<vector<int>> matrix;
	vector<int> way;
	vector<int> visited;

public:
	Graph();
	Graph(int vertex, int edge);
	Graph(Graph& g);

	void in(istream& stream);
	void out(ostream& stream) const;

	void addVertex();
	void addEdge(int a, int b);

	void delVertex(int index);
	void delEdge(int a, int b);

	vector<int> DFS(int start, int finish);

	vector<int> BFS(int start, int finish);

	void wayOut() const;
};

istream& operator>>(istream& stream, Graph& g);

ostream& operator<<(ostream& stream, Graph& g);

#endif