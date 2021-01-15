#include<iostream>
#include<string>
#include "source.h"
using namespace std;

#define MAX_LENGTH 10000000

class Graph
{
private:
	//顶点
	Vector<string> Vertex;
	//邻接表
	Vector<List<Pair<int,int>>> adjacentList;
	//Prim算法的最小生成树
	Vector<Pair<int,int>> mstPrim;
public:
	Graph() {};
	void CreateVertex();
	void AddEdge();
	void BuildMST();
	void PrintMST();
private:
	int findVertex(const string& vetex);
	void clear();
	void prim(int index);
	void kruskal();
};

//创建顶点
void Graph::CreateVertex()
{
	//清空顶点数据
	this->clear();
	
	int numVertex;
	cout << "请输入顶点的个数：";
	cin >> numVertex;
	cout << "请依次输入各顶点的名称：" << endl;
	for (int i = 0; i < numVertex; ++i)
	{
		string vertexName;
		cin >> vertexName;
		//判断是否已存在
		if (findVertex(vertexName) != -1)
		{
			cout << "顶点" << vertexName << "已存在！" << endl;
		}
		else
		{
			Vertex.push_back(vertexName);
		}
	}
	for (int i = 0; i < Vertex.size(); ++i)
		adjacentList.push_back(List<Pair<int,int>>());
}

//添加边
void Graph::AddEdge()
{
	string vertexA, vertexB;
	int edgeLength;
	while (true)
	{
		cout << "请输入两个顶点及边：";
		cin >> vertexA >> vertexB >> edgeLength;
		if (edgeLength <= 0)
			break;
		int indexA = findVertex(vertexA);
		int indexB = findVertex(vertexB);
		if (indexA == -1)
		{
			cout << "顶点 " << vertexA << " 不存在" << endl;
			continue;
		}
		if (indexB == -1)
		{
			cout << "顶点 " << vertexB << " 不存在" << endl;
			continue;
		}
		adjacentList[indexA].push_back(Pair<int, int>(indexB, edgeLength));
		adjacentList[indexB].push_back(Pair<int, int>(indexA, edgeLength));
	}
}

//产生最小生成树
void Graph::BuildMST()
{
	if (Vertex.size() == 1)
	{
		cout << "只含一个顶点，无需生成最小树！" << endl;
		return;
	}
	string vertex;
	cout << "请输入起始顶点：";
	cin >> vertex;
	int index = findVertex(vertex);
	if (index == -1)
	{
		cout << "顶点 " << vertex << " 不存在" << endl;
		return;
	}
	//开始生成最小树
	cout << "生成Prim最小树！" << endl;
	prim(index);
}

void Graph::PrintMST()
{
	if (!mstPrim.size())
	{
		cout << "请先生成最小树！" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为：" << endl << endl;
	for (int i = 0; i < mstPrim.size(); i++) {
		cout << Vertex[mstPrim[i].first] << "-(";
		
		for (auto j = adjacentList[mstPrim[i].first].begin(); j != adjacentList[mstPrim[i].first].end(); ++j)
		{
			if ((*j).first == mstPrim[i].second)
			{
				cout << (*j).second << ")->";
				break;
			}
		}

		cout << Vertex[mstPrim[i].second] << "\t";
	}
	cout << endl;
}

int Graph::findVertex(const string& vertex)
{
	for (int i = 0; i < Vertex.size(); ++i)
	{
		if (Vertex[i] == vertex)
			return i;
	}
	return -1;
}

void Graph::clear()
{
	Vertex.clear();
	adjacentList.clear();
	mstPrim.clear();
}

void Graph::prim(int index)
{
	//删除之前生成的最小生成树
	mstPrim.clear();

	//标记是否访问过
	Vector<bool> visited(Vertex.size());
	visited.fillData(false);
	visited[index] = true;

	Vector<int> visitedPrim;
	visitedPrim.push_back(index);

	while (visitedPrim.size() < Vertex.size())
	{
		int start = -1, end = -1, min = MAX_LENGTH;
		for (auto i = visitedPrim.begin(); i != visitedPrim.end(); ++i)
		{
			for (auto j = adjacentList[(*i)].begin(); j != adjacentList[(*i)].end(); ++j)
			{
				//尚未加入
				if (!visited[(*j).first] && (*j).second < min)
				{
					start = *i;
					end = (*j).first;
					min = (*j).second;
				}
			}
		}
		//加入
		visited[end] = true;
		visitedPrim.push_back(end);
		mstPrim.push_back(Pair<int, int>(start, end));
	}
	
}

void Graph::kruskal()
{
	//从所有边中选出最短的一个边,直到所有的点都被加入
	Vector<bool>visited(Vertex.size());
	visited.fillData(false);
	Vector<int> visitedPrim;
	
	while (visitedPrim.size() != Vertex.size())
	{
		int start = -1, end = -1, min = MAX_LENGTH;


	}
}

int main()
{
	cout << "**\t\t电网造价模拟系统\t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\tA --- 创建电网顶点\t\t**" << endl;
	cout << "**\t\tB --- 添加电网的边\t\t**" << endl;
	cout << "**\t\tC --- 构建最小生成树\t\t**" << endl;
	cout << "**\t\tD --- 显示最小生成树\t\t**" << endl;
	cout << "**\t\tE --- 退出   程序\t\t**" << endl;
	cout << "==================================================" << endl;

	Graph g;
	bool quit = false;
	char op;
	while (!quit) {
		cout << "\n请选择操作：";
		cin >> op;
		switch (op) {
		case 'a':
		case 'A': 
			g.CreateVertex();
			break;
		case 'b':
		case 'B': 
			g.AddEdge();
			break;
		case 'c':
		case 'C': 
			g.BuildMST(); 
			break;
		case 'd':
		case 'D': 
			g.PrintMST(); 
			break;
		case 'e':
		case 'E': 
			quit = true; 
			break;
		default: 
			cout << "输入有误，请重新输入！" << endl; 
			cin.clear();
			cin.ignore(1024, '\n');
			break;
		}
	}
	return 0;
}
