#pragma once

#include <iostream>
#include <stack>

template<typename T>
class UndirectedGraph
{
public:
	UndirectedGraph(T* vertex, int vertex_num);
	bool BuildBridge(int vertex1, int vertex2);
	void DFS(int vertex);	// 实现DFS深度优先遍历算法
	void BFS(int vertex);
	~UndirectedGraph();
private:
	T* vertex_;	// 顶点数组
	int** adj_matrix_;	// 邻接矩阵
	int vertex_num_;	// 顶点个数
};

template<typename T>
inline UndirectedGraph<T>::UndirectedGraph(T* vertex, int vertex_num)
{
	this->vertex_num_ = vertex_num;
	this->vertex_ = new T[vertex_num_];
	for (int i = 0; i < this->vertex_num_; ++i)
	{
		this->vertex_[i] = vertex[i];
		std::cout << "vertex: " << this->vertex_[i] << std::endl;
	}
	this->adj_matrix_ = new int* [vertex_num_];
	for (int i = 0; i < this->vertex_num_; ++i)
	{
		this->adj_matrix_[i] = new int[vertex_num_];
		for (int j = 0; j < this->vertex_num_; ++j)
		{
			this->adj_matrix_[i][j] = 0;
			std::cout << "adj_matrix" << "[" << i << "]" << "[" << j << "]" << " " << "init success!" << " " << "value: " << adj_matrix_[i][j] << std::endl;
		}
	}
}

template<typename T>
inline bool UndirectedGraph<T>::BuildBridge(int vertex1, int vertex2)
{
	if (vertex1 == vertex2 || vertex1 >= this->vertex_num_ || vertex2 >= this->vertex_num_ || adj_matrix_[vertex1][vertex2] == 1)
	{
		std::cout << "invalid arg: " << vertex1 << " " << vertex2 << std::endl;
		return false;
	}
	this->adj_matrix_[vertex1][vertex2] = 1;
	this->adj_matrix_[vertex2][vertex1] = 1;
	std::cout << vertex1 << " to " << vertex2 << std::endl;
	return true;
}

template<typename T>
inline void UndirectedGraph<T>::DFS(int vertex)
{
	bool* vertex_flag = new bool[vertex_num_];
	for (int i = 0; i < this->vertex_num_; ++i)
	{
		vertex_flag[i] = true;
	}
	std::cout << "DFS vertex" << "[" << vertex << "]" << " output: " << this->vertex_[vertex] << std::endl;
	vertex_flag[vertex] = false;
	std::stack<int> vertex_stack;
	vertex_stack.push(vertex);
	while (!vertex_stack.empty())
	{
		vertex = vertex_stack.top();
		int adj = 0;
		while (adj < vertex_num_)
		{
			std::cout << "vertex: " << vertex << " " << "adj: " << adj << std::endl;
			if (adj != vertex && this->adj_matrix_[vertex][adj] == 1 && vertex_flag[adj])
			{
				vertex = adj;
				std::cout << "DFS vertex" << "[" << vertex << "]" << " output: " << this->vertex_[vertex] << std::endl;
				vertex_flag[vertex] = false;
				vertex_stack.push(vertex);
				adj = 0;
			}
			else
			{
				++adj;
			}
		}
		vertex_stack.pop();
	}
	delete[] vertex_flag;
}

template<typename T>
inline void UndirectedGraph<T>::BFS(int vertex)
{
	bool* vertex_flag = new bool[vertex_num_];
	for (int i = 0; i < this->vertex_num_; ++i)
	{
		vertex_flag[i] = true;
	}
	std::cout << "BFS vertex" << "[" << vertex << "]" << " output: " << this->vertex_[vertex] << std::endl;
	vertex_flag[vertex] = false;
	std::stack<int> vertex_stack;
	vertex_stack.push(vertex);
	while (!vertex_stack.empty())
	{
		int adj = 0;
		while (adj < this->vertex_num_)
		{
			if (adj != vertex && adj_matrix_[vertex][adj] && vertex_flag[adj])
			{
				std::cout << "BFS vertex" << "[" << adj << "]" << " output: " << this->vertex_[adj] << std::endl;
				vertex_stack.push(adj);
				vertex_flag[adj] = false;
			}
			++adj;
		}
		vertex = vertex_stack.top();
		vertex_stack.pop();
	}
}

template<typename T>
inline UndirectedGraph<T>::~UndirectedGraph()
{
	delete[] this->vertex_;
	for (int i = 0; i < this->vertex_num_; ++i)
	{
		delete[] this->adj_matrix_[i];
		std::cout << "adj_matrix" << "[" << i << "]" << " " << "free" << "success!" << std::endl;
	}
	delete[] this->adj_matrix_;
	std::cout << "adj_matrix free success!" << std::endl;
}
