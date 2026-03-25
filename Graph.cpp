#include "Graph.h"

using namespace std;

// конструктор по-умолчанию
Graph::Graph() {
	vertexCount = 0;
	edgeCount = 0;
}

// конструктор с параметром
Graph::Graph(int vertex, int edge) {
	vertexCount = vertex;
	edgeCount = edge;
	matrix.resize(vertexCount);
	visited.resize(vertexCount);
}

// конструктор копий
Graph::Graph(Graph& g) {
	vertexCount = g.vertexCount;
	edgeCount = g.edgeCount;
	matrix = g.matrix;
	visited = g.visited;
}

// метод ввода объекта класса грав через поток
void Graph::in(istream& stream) {
	int a, b, i;
	matrix.clear();
	way.clear();
	visited.clear();
	if (&stream == &cin) {
		cout << "¬ведите количество вершин и ребер графа соответственно: ";
		stream >> vertexCount >> edgeCount;
		cout << endl << "¬ведите " << edgeCount << " пар вершин, которые соеденены ребрами:" << endl;
		matrix.resize(vertexCount);
		visited.resize(vertexCount);
		for (i = 0; i < edgeCount; i++) {
			stream >> a >> b;
			matrix[a].push_back(b);
			matrix[b].push_back(a);
		}
	}

	else {
		stream >> vertexCount >> edgeCount;
		matrix.resize(vertexCount);
		visited.resize(vertexCount);
		for (i = 0; i < edgeCount; i++) {
			stream >> a >> b;
			matrix[a].push_back(b);
			matrix[b].push_back(a);
		}
	}
}

// метод вывода в консоль
void Graph::out(ostream& stream)const {
	int i, j;
	for (i = 0; i < vertexCount; i++) {
		stream << i << "| ";

		for (j = 0; j < matrix[i].size(); j++) {
			stream << matrix[i][j] << " ";
		}
		stream << endl;
	}
	
}

// добавить новую вершину в граф
void Graph::addVertex() {
	vertexCount++;
	matrix.resize(vertexCount);
	visited.resize(vertexCount);

	int edge, a;
	cout << "¬ведите количество ребер выход€щих из этой новой вершины: ";
	cin >> edge;
	edgeCount += edge;

	if (edge != 0) {
		cout << "¬ведите " << edge << " вершин которые св€заны с новой: ";
		for (int i = 0; i < edge; i++) {
			cin >> a;
			matrix[a].push_back(vertexCount - 1);
			matrix[vertexCount - 1].push_back(a);
		}
	}
}

// добавить ребро между двум€ заданными вершинами графа
void Graph::addEdge(int a, int b) {
	matrix[a].push_back(b);
	matrix[b].push_back(a);
}

// удалить все св€зи заданной вершины графа
void Graph::delVertex(int index) {
	matrix[index].clear();
	for (int i = 0; i < vertexCount; i++) {
		for (auto j = matrix[i].begin(); j != matrix[i].end(); j++) {
			//cout << *j + 1 <<" ";
			if (*j == index) {
				matrix[i].erase(j);
				break;
			}
		}
	}
}

// удалить ребро между двум€ заданными вершинами графа
void Graph::delEdge(int a, int b) {
	for (auto i = matrix[a].begin(); i != matrix[a].end(); i++) {
		if (*i == b) {
			matrix[a].erase(i);
			break;
		}
	}

	for (auto i = matrix[b].begin(); i != matrix[b].end(); i++) {
		if (*i == a) {
			matrix[b].erase(i);
			break;
		}
	}
}

// функци€ возвращающа€ путь между двум€ вершинами графа
// путь находитс€ по алгоритму поиска в глубину
vector<int> Graph::DFS(int start, int finish) {
	vector<int> res;
	visited[start] = 1;
	way.push_back(start);

	if (start == finish)
		return way;

	for (int to : matrix[start]) {
		if (!visited[to]) {
			res = DFS(to, finish);
			if (!res.empty())
				return res;
		}
	}

	way.pop_back();
	return {};
}


const int INF = 1e9;
// функци€ возвращающа€ путь между двум€ вершинами графа
// путь находитс€ по алгоритму поиска в ширину
vector<int> Graph::BFS(int start, int finish) {
	vector<int> dist(vertexCount, INF);
	vector<int> from(vertexCount, -1);
	queue<int> q;

	dist[start] = 0;
	q.push(start);

	int vertex;
	while (!q.empty()) {
		vertex = q.front();
		q.pop();

		for (int to : matrix[vertex]) {
			if (dist[to] > dist[vertex]) {
				dist[to] = dist[vertex] + 1;
				from[to] = vertex;
				q.push(to);
			}
		}
	}

	way.clear();
	for (int i = finish; i != -1; i = from[i]) {
		way.push_back(i);
	}

	reverse(way.begin(), way.end());

	return way;
}

// вывести путь в консоль
void Graph::wayOut() const {
	for (auto i = way.begin(); i != way.end(); i++) {
		cout << *i;
		if(i != way.end()-1)
			cout << " -> ";
	}
	cout << endl;
}

// перегрузка оператора ввода
istream& operator>>(istream& stream, Graph& g) {
	g.in(stream);
	return stream;
}

// перегрузка оператора вывода
ostream& operator<<(ostream& stream, Graph& g) {
	g.out(stream);
	return stream;
}