#include "UndirectedGraph.hpp"

int main()
{
	int vertex[] = { 0, 1, 2, 3, 4, 5, 6 };
	UndirectedGraph<int> graph(vertex, 7);
	graph.BuildBridge(0, 1);
	graph.BuildBridge(1, 3);
	graph.BuildBridge(3, 6);
	graph.BuildBridge(3, 4);
	graph.BuildBridge(1, 4);
	graph.BuildBridge(1, 2);
	graph.BuildBridge(0, 2);
	graph.BuildBridge(2, 4);
	graph.BuildBridge(2, 5);
	graph.BuildBridge(4, 5);
	graph.BFS(5);
}