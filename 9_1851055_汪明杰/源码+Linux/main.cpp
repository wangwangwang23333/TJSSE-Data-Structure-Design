#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<string>
#include "class.h"
using namespace std;

struct Course
{
	string id;
	string name;
	int term;//开课学期
	int number;//学时数
	Course** p;//先修课程
};

int courseNum;
Vector<Course> courses;
Vector<Vector<string>> preCourse;
Vector<Vector<Vector<int>>> courseTable(8, Vector<Vector<int>>(5, Vector<int>(10, -1)));

void arrangeCourse(int index);
void topoSort();

int main()
{
	//读取文件
	cout << "请输入读取文件的位置(输入0读取默认文件):";
	string fileLoad;
	ifstream file(fileLoad);
	//读取文件
	while (true)
	{
		cin >> fileLoad;
		if (fileLoad.length() == 0 || fileLoad == "0")
		{
			cout << "读取默认文件input.txt";
			fileLoad = "input.txt";
		}
		file.open(fileLoad);
		//查看文件是否存在
		if (file.is_open())
			break;
		cout << endl << fileLoad << "不存在！" << endl;
	}
	//读取课程总数
	file >> courseNum;
	courses.resize(courseNum);
	preCourse.resize(courseNum);
	//读取每一门课程信息
	for (int i = 0; i < courseNum; ++i)
	{
		//读取到文件末尾
		if (file.eof())
			break;
		getline(file, fileLoad);
		//定义字符串流
		stringstream sr(fileLoad);
		sr >> courses[i].id >> courses[i].name >>
			courses[i].number >> courses[i].term;
		//读取前置课程信息
		while (!sr.eof())
		{
			sr >> fileLoad;
			preCourse[i].push_back(fileLoad);
		}
	}
	file.close();
	//检查输入是否正确
	if (courses.size() != courseNum)
	{
		cout << "课程总数有误，请检查数据" << endl;
		courseNum = courses.size();
	}

	topoSort();

	//写文件
	cout << "请输入输出文件位置(输入0存储到默认位置): ";
	string saveFile;
	cin >> saveFile;
	if (saveFile == "0")
		saveFile = "output.txt";
	ofstream save(saveFile);
	for (int curterm = 0; curterm < 8; curterm++)
	{
		save << "第" << curterm + 1 << "学期课表" << endl;
		for (int curcourse = 0; curcourse < 10; curcourse++)
		{
			for (int curday = 0; curday < 5; curday++)
			{
				int index = courseTable[curterm][curday][curcourse];
				if (index == -1) 
					save << left << setw(20) << "--------------" << "\t";
				else 
					save << left << setw(20) << courses[index].name + courses[index].id << "\t";
			}
			save << endl;
		}
		save << endl;
	}
	cout << "已存储至" << saveFile << endl;
	save.close();

	cin.clear();
	cin.ignore(1024, '\n');
	cout << endl << "Enter to Exit";
	cin.get();

	return 0;
}

//拓扑排序
void topoSort()
{
	//入度为0顶点组成的队列
	Queue<int> procedure;
	//记录入度数
	Vector<int> inDegrees(courseNum);
	//遍历，找出入度为0的点
	for (int i = 0; i < courseNum; ++i)
	{
		inDegrees[i] = preCourse[i].size();
		if (inDegrees[i] == 0)
		{
			procedure.push(i);
		}
	}
	//拓扑过程
	while (!procedure.empty())
	{
		int index = procedure.front();
		procedure.pop();
		//对该课程进行安排
		arrangeCourse(index);
		//将所以该课程的入度设为0
		for (int i = 0; i < courseNum; ++i)
		{
			for (int j = 0; j < preCourse[i].size(); ++j)
			{
				if (preCourse[i][j] == courses[index].id)
				{
					--inDegrees[i];
					//如果入度为0
					if (inDegrees[i] == 0)
					{
						//将最早安排学期置为下一学期
						if (courses[i].term < courses[index].term + 1)
							courses[i].term = courses[index].term + 1;
						procedure.push(i);
					}
				}
			}
		}
	}
}

//安排编号为index的课程
int findThree(int curterm, int& curday, int index) 
{
	for (int i = 0; i < 5; curday = (curday + 2) % 5, i++)
	{
		if (courseTable[curterm][curday][2] == -1 && courseTable[curterm][curday][3] == -1 && courseTable[curterm][curday][4] == -1) 
		{
			courseTable[curterm][curday][2] = courseTable[curterm][curday][3] = courseTable[curterm][curday][4] = index;
			curday = (curday + 2) % 5;
			return 3;
		}
		if (courseTable[curterm][curday][7] == -1 && courseTable[curterm][curday][8] == -1 && courseTable[curterm][curday][9] == -1) 
		{
			courseTable[curterm][curday][7] = courseTable[curterm][curday][8] = courseTable[curterm][curday][9] = index;
			curday = (curday + 2) % 5;
			return 3;
		}
	}
	return 0;
}

int findTwo(int curterm, int& curday, int index) 
{
	for (int i = 0; i < 5; curday = (curday + 2) % 5, i++)
	{
		if (courseTable[curterm][curday][0] == -1 && courseTable[curterm][curday][1] == -1) 
		{
			courseTable[curterm][curday][0] = courseTable[curterm][curday][1] = index;
			curday = (curday + 2) % 5;
			return 2;
		}
		if (courseTable[curterm][curday][7] == -1 && courseTable[curterm][curday][8] == -1) 
		{
			courseTable[curterm][curday][7] = courseTable[curterm][curday][8] = index;
			curday = (curday + 2) % 5;
			return 2;
		}
	}
	return 0;
}

int findOne(int curterm, int& curday, int index) 
{
	for (int i = 0; i < 5; curday = (curday + 2) % 5, i++)
	{
		for (int curc = 0; curc < 10; curc++)
		{
			if (courseTable[curterm][curday][curc] == -1) 
			{
				courseTable[curterm][curday][curc] = index;
				curday = (curday + 2) % 5;
				return 1;
			}
		}
	}
	return 0;
}

//安排课程index
void arrangeCourse(int index)
{
	cout << courses[index].id << " " << courses[index].name;
	int curday = 0;
	int puted = 0;
	while (puted < courses[index].number && courses[index].term < 8)
	{
		int newspace;
		if (courses[index].number - puted >= 3)
			newspace = findThree(courses[index].term, curday, index);
		else if (courses[index].number - puted >= 2)
			newspace = findTwo(courses[index].term, curday, index);
		else
			newspace = findOne(courses[index].term, curday, index);

		puted += newspace;
		if (newspace == 0) 
		{
			courses[index].term++;
			curday = 0;
		}
	}
	cout << "\t√" << endl;
}
