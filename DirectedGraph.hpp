#pragma once

#include <iostream>
#include <stack>

// 边结点
class ArcNode
{
public:
	int adj_;	// 邻接点
	ArcNode* next_{ nullptr };
};

// 顶点结点
template<typename T>
class VertexNode
{
public:
	T vertex_;	// 顶点
	ArcNode* first_edge_{ nullptr };	// 邻接点指针
};

template<typename T>
class DirectedGraph
{
public:
	DirectedGraph(T vertex[], int vertex_num);
	// 判断start和end是否连通
	bool IsConnect(int start, int end) const;
	// 连通start和end
	bool BuildBridge(int start, int end);
	~DirectedGraph();
private:
	VertexNode<T>* adj_list_;	// 邻接表
	int vertex_num_;	// 所有顶点的个数
};

template<typename T>
inline DirectedGraph<T>::DirectedGraph(T vertex[], int vertex_num)
{
	this->vertex_num_ = vertex_num;
	// 创建邻接表
	this->adj_list_ = new VertexNode<T>[vertex_num_];
	for (int i = 0; i < vertex_num_; ++i)
	{
		this->adj_list_[i].vertex_ = vertex[i];
	}
}

template<typename T>
inline bool DirectedGraph<T>::IsConnect(int start, int end) const 
{
	if (start >= this->vertex_num_ || end >= this->vertex_num_ || start < 0 || end < 0)
	{
		return false;
	}
	ArcNode* arc = this->adj_list_[start].first_edge_;
	while (arc != nullptr)
	{
		if (arc->adj_ == end)
		{
			return true;
		}
		arc = arc->next_;
	}
	return false;
}

template<typename T>
inline bool DirectedGraph<T>::BuildBridge(int start, int end)
{
	if (start >= this->vertex_num_ || end >= this->vertex_num_ || start < 0 || end < 0 || IsConnect(start, end))
	{
		std::clog << "Invalid arg!" << std::endl;
		return false;
	}
	ArcNode* arc = new ArcNode;
	arc->adj_ = end;
	arc->next_ = this->adj_list_[start].first_edge_;
	this->adj_list_[start].first_edge_ = arc;
	return true;
}

template<typename T>
inline DirectedGraph<T>::~DirectedGraph()
{
	// 释放所有边结点的内存
	for (int i = 0; i < this->vertex_num_; ++i)
	{
		while (this->adj_list_[i].first_edge_ != nullptr)
		{
			ArcNode* temp = this->adj_list_[i].first_edge_;
			this->adj_list_[i].first_edge_ = this->adj_list_[i].first_edge_->next_;
			delete[] temp;
		}
	}
	// 释放邻接表的内存
	delete[] this->adj_list_;
}
