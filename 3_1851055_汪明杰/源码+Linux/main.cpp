#include<iostream>
#include<ctime>
#include<map>
#include<cstring>
#include "maze.h"
using namespace std;

//枚举迷宫内
enum BLOCK_TYPE
{
	WALL, BLANK
};

//位置坐标
typedef Pair<int, int> Position;

//定义四个方向的
const Position step[4] = { {-1,0},{0,1},{1,0},{0,-1} };

//地图信息
int mapX;
int mapY;
BLOCK_TYPE **blockMap;

//判断坐标是否有效
inline bool isValid(const Position& pos)
{
	return pos.first >= 0 && pos.first < mapX &&
		pos.second >= 0 && pos.second < mapY;
}


inline bool isWall(const Position& pos)
{
	return isValid(pos) && blockMap[pos.first][pos.second] == WALL;
}

inline bool isRoad(const Position& pos)
{
	return isValid(pos) && blockMap[pos.first][pos.second] == BLANK;
}

inline bool isUnreachable(const Position& pos)
{
	return !isValid(pos) || blockMap[pos.first][pos.second] == WALL;
}

//迷宫样式
#define WALL_BLOCK "□"
#define ROAD_BLOCK "  "
#define WAY_BLOCK "⊙"

//绘制地图
void printMap(const Vector<Position>* path = nullptr)
{
	//上边框
	printf("   " WALL_BLOCK);
	for (int j = 0; j < mapY; ++j)
		printf(WALL_BLOCK);
	printf(WALL_BLOCK "\n");

	//中间行
	for (int i = 0; i < mapX; ++i) {
		printf("   %2s", (i == 0 ? ROAD_BLOCK : WALL_BLOCK));
		for (int j = 0; j < mapY; ++j) {
			if (path && path != nullptr &&
				mySTL::find(path->begin(), path->end(), Position(i, j)) != path->end())
				printf(WAY_BLOCK);
			else
				printf("%2s", (blockMap[i][j] == WALL ? WALL_BLOCK : ROAD_BLOCK));
		}
		printf("%2s\n", (i == mapX - 1 ? ROAD_BLOCK : WALL_BLOCK));
	}

	//下边框
	printf("   " WALL_BLOCK);
	for (int j = 0; j < mapY; ++j)
		printf(WALL_BLOCK);
	printf(WALL_BLOCK "\n");
}

void initMap(BLOCK_TYPE type = WALL)
{
	for (int i = 0; i < mapX; ++i)
		for (int j = 0; j < mapY; ++j)
			blockMap[i][j] = type;
}

//Prim算法
void randomizedPrim(Position seed);

//递归分割法
void recursiveDivision(Position leftup, Position rightdown);

void recursiveDivision();

//递归回溯法
void recursiveBacktrack(Position seed);

bool dfs(Vector<Position> &path, Position start, Position end);


int main()
{
	//随机生成种子
	srand(time(NULL));
	char ch;

	while (true)
	{
		cout << "请输入地图的行数和列数, 以空格分隔: ";
		cin >> mapX >> mapY;
		if (cin.fail())
			printf("输入有误\n");
		else if (mapX <= 0)
			printf("行数有误\n");
		else if (mapY <= 0)
			printf("列数有误\n");
		else if (mapX > 100)
			printf("行数过大\n");
		else if (mapY > 100)
			printf("列数过大\n");
		else
			break;
		cin.clear();             //重置错误标志位
		cin.ignore(4096, '\n');  //跳过后续的输入
	}

	printf("迷宫大小: %d x %d\n\n", mapX, mapY);
	blockMap = new BLOCK_TYPE *[mapX];
	for (int i = 0; i < mapX; i++)
		blockMap[i] = new BLOCK_TYPE[mapY];

	cout << "迷宫生成方式: " << endl;
	cout << "0. 随机Prim算法 (默认)" << endl;
	cout << "1. 递归回溯法" << endl;
	cout << "2. 递归分割法" << endl;
	cout << "请选择迷宫生成方式: ";
	cin >> ch;
	switch (ch)
	{
	case '1':
		recursiveBacktrack(Position(0, 0));
		break;
	case '2':
		recursiveDivision();
		break;
	default:
		randomizedPrim(Position(0, 0));
		break;
	}
	cout << endl;
	printMap();
	Position start, end;
	while (true)
	{
		cout << "请输入起点坐标和终点坐标(行 列): ";
		cin >> start.first >> start.second >> end.first >> end.second;
		if (cin.fail())
			printf("输入有误\n");
		else if (isUnreachable(start))
			printf("起点有误, 请重新输入\n");
		else if (isUnreachable(end))
			printf("终点有误, 请重新输入\n");
		else
			break;
		cin.clear();             
		cin.ignore(4096, '\n');  
	}
	printf("迷宫起点为(%d, %d), 终点为(%d, %d)\n\n", start.first, start.second,
		end.first, end.second);

	Vector<Position> route; 
	cout << "开始求解..." << endl;
	dfs(route, start, end);

	//打印结果
	if (route.empty())
		cout << "找不到路径,请检查起点和终点坐标" << endl;
	else 
	{
		cout << endl;
		printMap(&route);
		cout << endl;
		//打印路径
		for (int i = 0; i < route.size(); i++) 
		{
			if (i != 0) cout << " ---> ";
			printf("(%d, %d)", route[i].first, route[i].second);
		}
	}
	cin.clear();
	cin.ignore(4096, '\n');
	cout << endl << "Enter to Exit" << endl;
	cin.get();
	return 0;
}

void randomizedPrim(Position seed)
{
	Vector<Position> stack;
	stack.push_back(seed);

	initMap();
	while (!stack.empty())
	{
		int randd = rand() % stack.size();
		Position current = stack[randd];
		stack.erase(stack.begin() + randd);

		int road_count = 0;
		for (int i = 0; i < 4; i++)
		{
			Position nextPlace = current + step[i];
			if (isRoad(nextPlace)) 
				road_count++;
		}
		if (road_count <= 1)
		{
			blockMap[current.first][current.second] = BLANK;
			for (int i = 0; i < 4; i++)
			{
				Position nextPlace = current + step[i];
				if (isWall(nextPlace)) 
					stack.push_back(nextPlace);
			}
		}
	}
}

//递归分割法
void recursiveDivision(Position leftup, Position rightdown)
{
	if (rightdown.first - leftup.first < 3 ||
		rightdown.second - leftup.second < 3)
		return;
	//分割点
	Position divisionPoint(RAND_ODD_RANGE(leftup.first, rightdown.first),
		RAND_ODD_RANGE(leftup.second, rightdown.second));

	for (int i = leftup.first; i < rightdown.first; i++)
		blockMap[i][divisionPoint.second] = WALL;
	for (int i = leftup.second; i < rightdown.second; i++)
		blockMap[divisionPoint.first][i] = WALL;

	int randomNumber = rand() % 4;
	if (randomNumber != 0)
	{
		blockMap[RAND_EVEN_RANGE(leftup.first, divisionPoint.first)][divisionPoint.second] =
			BLANK;
	}
	if (randomNumber != 1)
	{
		blockMap[divisionPoint.first]
			[RAND_EVEN_RANGE(divisionPoint.second + 1, rightdown.second)] = BLANK;
	}
	if (randomNumber != 2)
	{
		blockMap[(RAND_EVEN_RANGE(divisionPoint.first + 1, rightdown.first))]
			[divisionPoint.second] = BLANK;
	}
	if (randomNumber != 3)
	{
		blockMap[divisionPoint.first][RAND_EVEN_RANGE(leftup.second, divisionPoint.second)] =
			BLANK;
	}

	//递归
	recursiveDivision(leftup, divisionPoint);
	recursiveDivision(Position(leftup.first, divisionPoint.second + 1),
		Position(divisionPoint.first, rightdown.second));
	recursiveDivision(Position(divisionPoint.first + 1, leftup.second),
		Position(rightdown.first, divisionPoint.second));
	recursiveDivision(
		Position(divisionPoint.first + 1, divisionPoint.second + 1), rightdown);
}

void recursiveDivision()
{
	initMap(BLANK);
	for (int i = 0; i < mapX; i++)
		blockMap[i][mapY - 1] = WALL;
	for (int j = 0; j < mapY; j++)
		blockMap[mapX - 1][j] = WALL;
	Position rightdown(TO_ODD(mapX), TO_ODD(mapY));
	recursiveDivision(Position(0, 0), rightdown);
}

//递归回溯法
void recursiveBacktrack(Position seed)
{
	Vector<Position> stack;
	stack.push_back(seed);

	initMap();
	while (!stack.empty())
	{
		Position current = *stack.last(); stack.pop_back();

		int road_count = 0;
		for (int i = 0; i < 4; i++)
		{
			Position nextPlace = current + step[i];
			if (isRoad(nextPlace))
				road_count++;
		}
		if (road_count <= 1)
		{
			blockMap[current.first][current.second] = BLANK;
			Vector<Position> nextPlaces;
			for (int i = 0; i < 4; i++)
			{
				Position nextPlace = current + step[i];
				if (isWall(nextPlace)) 
					nextPlaces.push_back(nextPlace);
			}
			mySTL::random_shuffle(nextPlaces.begin(), nextPlaces.end());
			for (int i = 0; i < nextPlaces.size(); i++)
				stack.push_back(nextPlaces[i]);
		}
	}
}

bool dfs(Vector<Position> &path, Position start, Position end)
{
	bool **visited = new bool*[mapX];
	for (int i = 0; i < mapX; i++)
	{
		visited[i] = new bool[mapY];
		memset(visited[i], 0, mapY * sizeof(bool));
	}

	path.clear();
	path.push_back(start);  //用参数path作栈
	visited[start.first][start.second] = true;

	Position current;
	while (!path.empty())
	{
		current = *path.last();
		if (current == end)
			break;
		bool no_way = true;
		for (int i = 0; i < 4; i++)
		{
			Position next = current + step[i];
			if (!isUnreachable(next) && !visited[next.first][next.second])
			{
				path.push_back(next);
				visited[next.first][next.second] = true;
				no_way = false;
				break;
			}
		}
		if (no_way)
			path.pop_back();
	}

	for (int i = 0; i < mapX; i++)
		delete[] visited[i];
	delete[] visited;

	if (path.empty())
		return false;
	return true;
}
