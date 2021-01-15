#include <iostream>
#include<string>
#include "source.h"
using namespace std;

#define MAX(x,y) (((x)>(y))?(x):(y))
#define MIN(x,y) (((x)<(y))?(x):(y))

struct familyTreeNode
{
	string name;
	Vector<familyTreeNode*> children;
	//构造函数
	familyTreeNode(const string& name) :name(name) {};
private:
	Pair<int, int> position;
	int childHorizonalLength;
	friend class familyTree;
};

class familyTree
{
private:
	familyTreeNode *root = nullptr;
public:
	familyTree() {};
	void BuildTree();
	void BuildFamily();
	void AddFamilyMember();
	void DelFamily();
	void RenameFamilyMember();
	void ShowTree();
public:
	familyTreeNode* search(const string& name)const;
	inline int count(const string& name)const;
	void showFamilyVertical(familyTreeNode* ptr, Vector<Pair<int, bool>>& memberPlace,
		bool lastMember)const;
	void showFamilyHorizontal();
private:	
	familyTreeNode* searchAt(familyTreeNode* root, const string& name)const;
	int maxPile(familyTreeNode* ptr);
	int maxHorizontalDistance(familyTreeNode* ptr);
	void setNodeY();
	void setNodeY(familyTreeNode* ptr, int pile);
	void setNodeX();
	void setNodeX(familyTreeNode* ptr);
	void setNodePosition(); 
	void offsetX(familyTreeNode* ptr);
private:
	int maxHorizontalLength;
	int maxVerticalPile;
	int minPositionX;
public:
	bool showVertical = true;
};

void familyTree::BuildTree()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string name;
	cin >> name;
	root = new familyTreeNode(name);
	cout << "此家谱的祖先是：" << root->name << endl;
}

void familyTree::BuildFamily()
{
	cout << "请输入要建立家庭的人的姓名：";
	string name;
	cin >> name;
	familyTreeNode* familyMember = search(name);
	if (familyMember == nullptr)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	if (!familyMember->children.empty())
	{
		cout << "该成员已经建立过家庭！" << endl;
		return;
	}

	int numChildren;
	cout << "请输入" << name << "的儿女个数：";
	cin >> numChildren;
	if (cin.fail() || numChildren < 0)
	{
		cout << "请输入一个正整数！" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		return;
	}

	cout << "请依次输入" << name << "的儿女的姓名";
	for (int i = 0; i < numChildren; ++i)
	{
		cin >> name;
		if (!count(name))
		{
			familyMember->children.push_back(new familyTreeNode(name));
		}
		else
		{
			cout << "姓名为" << name << "的成员已存在！" << endl;
		}
	}
}

void familyTree::AddFamilyMember()
{
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	string name;
	cin >> name;
	familyTreeNode* familyMember = search(name);
	if (familyMember == nullptr)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	cout << "请输入" << name << "新添加儿子（或女儿）的姓名：";
	cin >> name;
	if (!count(name))
	{
		familyMember->children.push_back(new familyTreeNode(name));
	}
	else
	{
		cout << "姓名为" << name << "的成员已存在！" << endl;
	}
}

void familyTree::DelFamily()
{
	cout << "请输入要解散家庭的人的姓名";
	string name;
	cin >> name;
	familyTreeNode* familyMember = search(name);
	if (familyMember == nullptr)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	cout << "要解散家庭的人是" << name << endl;
	familyMember->children.clear();
}

void familyTree::RenameFamilyMember()
{
	cout << "请输入要更改姓名的人的目前姓名";
	string name;
	cin >> name;
	familyTreeNode* familyMember = search(name);
	if (familyMember == nullptr)
	{
		cout << "本家谱内不存在该家庭成员！" << endl;
		return;
	}
	cout << "请输入更改后的姓名：";
	cin >> name;
	if (!count(name))
	{
		cout << familyMember->name << "已更名为" << name << endl;
		familyMember->name = name;
	}
	else
	{
		cout << "姓名为" << name << "的成员已存在！" << endl;
	}
}

void familyTree::ShowTree()
{
	cout << endl << "当前家谱树为：" << endl;
	
	if (showVertical)
		showFamilyHorizontal();
	else
	{
		Vector<Pair<int,bool>> memberPlace;
		showFamilyVertical(root, memberPlace, false);
	}
}

familyTreeNode* familyTree::searchAt(familyTreeNode* root, const string& name)const
{
	//查看当前结点是否为所需要查找的家族成员
	if (root->name == name)
		return root;
	familyTreeNode* findResult = nullptr;
	for (auto i = root->children.begin(); i != root->children.end(); ++i)
	{
		findResult = searchAt(*i, name);
		if (findResult != nullptr)
			return findResult;
	}
	return nullptr;
}

familyTreeNode* familyTree::search(const string& name)const
{
	if (root == nullptr)
		return nullptr;
	else
		return searchAt(root, name);
}

inline int familyTree::count(const string& name)const
{
	return search(name) != nullptr ? 1 : 0;
}

void familyTree::showFamilyVertical(familyTreeNode* ptr, Vector<Pair<int, bool>>& memberPlace,
	bool lastMember)const
{
	if (memberPlace.empty())
	{
		cout << ptr->name << endl;
		memberPlace.push_back(Pair<int, bool>(ptr->name.length(), true));
	}
	else
	{
		//将memberPlace除最后一项外的元素全部以|形式输出(或者为空格)
		//最后一项根据是否为lastMember确定
		int blankNumber = 0;
		//对于前面n-2个元素
		for (int i = 0; i < memberPlace.size() - 1; ++i)
		{
			while (memberPlace[i].first > blankNumber++)
			{
				cout << " ";
			}

			if (memberPlace[i].second)
				cout << "│";
			else
				cout << "   ";
		}

		while (memberPlace[memberPlace.size() - 1].first > blankNumber++)
		{
			cout << " ";
		}
		if (lastMember)
			cout << "└  ";
		else
			cout << "├  ";
		cout << ptr->name << endl;
		memberPlace.push_back(Pair<int,bool>(ptr->name.length() + (*memberPlace.last()).first,true));
	}
	
	if (!ptr->children.empty())
	{
		for (auto i = ptr->children.begin(); i != ptr->children.last(); ++i)
		{
			showFamilyVertical(*i, memberPlace, false);
		}
		//到最后一个了，此时应该把上一层的second更改为false
		if (!memberPlace.empty())
			memberPlace[memberPlace.size() - 1].second = false;
		showFamilyVertical(*ptr->children.last(), memberPlace, true);
	}
	memberPlace.pop_back();
}

void familyTree::showFamilyHorizontal()
{
	if (root == nullptr)
		return;
	//获取每一个结点的位置
	this->setNodePosition();

	//利用队列层次遍历输出
	Queue<familyTreeNode*> treeQueue;
	treeQueue.push(root);
	int nodeNumber = 1;//当前层队列结点数
	int positionX = 0, positionY = 1;

	Queue<Pair<familyTreeNode*, Pair<char,int>>> LineQueue;
	LineQueue.push(Pair<familyTreeNode*, Pair<char,int>>(root, Pair<char,int>('o',0)));

	int positionLineX = 0;
	while (!treeQueue.empty())
	{
		bool newPart = false;
		//绘制线条
		for (int i = 0; i < nodeNumber; ++i)
		{
			familyTreeNode* ptr = LineQueue.front().first;

			char mark = LineQueue.front().second.first;
			int halfPlace = LineQueue.front().second.second;
			LineQueue.pop();

			if (mark == 's' && !newPart)
				newPart = true;

			//把ptr的子结点加入
			for (int j = 0; j < ptr->children.size(); ++j)
			{
				if (ptr->children.size() == 1)
				{
					LineQueue.push(Pair<familyTreeNode*, Pair<char,int>>
						(ptr->children[j], Pair<char,int>('o',
							ptr->position.first+ptr->name.length()/2)));
				}
				else if (j == 0)
				{
					LineQueue.push(Pair<familyTreeNode*, Pair<char, int>>
						(ptr->children[j], Pair<char, int>('s',
							ptr->position.first + ptr->name.length() / 2)));
				}
				else if (j == ptr->children.size() - 1)
				{
					LineQueue.push(Pair<familyTreeNode*, Pair<char, int>>
						(ptr->children[j], Pair<char, int>('l',
							ptr->position.first + ptr->name.length() / 2)));
				}
				else
				{
					LineQueue.push(Pair<familyTreeNode*, Pair<char, int>>
						(ptr->children[j], Pair<char, int>('n',
							ptr->position.first + ptr->name.length() / 2)));
				}
			}

			if (ptr == root)
				break;

			//处理ptr
			while (positionLineX < ptr->position.first)
			{
				if (newPart&&positionLineX>=halfPlace)
				{
					cout << "┴";
					cout << " ";
					positionLineX += 2;
					newPart = false;
				}
				else
				{
					switch (mark)
					{
					case 'o':
					case 's':
						cout << " ";
						++positionLineX;
						break;
					case 'l':
					case 'n':
						cout << "─";
						cout << " ";
						positionLineX += 2;
						break;
					}
				}
			}

			switch (mark)
			{
			case 'o':
				cout << "│";
				cout << " ";
				break;
			case 's':
				cout << "┌";
				cout << " ";
				break;
			case 'l':
				cout << "┐";
				cout << " ";
				break;
			case 'n':
				cout << "┬";
				cout << " ";
				break;
			}
			positionLineX += 2;

			if (i == nodeNumber - 1)
				cout << endl;
		}

		positionLineX = 0;

		int newNodeNumber = 0;
		//绘制结点
		for (int i = 0; i < nodeNumber; ++i)
		{
			familyTreeNode* ptr = treeQueue.front();
			treeQueue.pop();
			//将ptr的元素全部入队
			newNodeNumber += ptr->children.size();
			for (auto i = ptr->children.begin(); i != ptr->children.end(); ++i)
			{
				treeQueue.push(*i);
			}
			//将ptr的name输出,注意需要利用空格到达当前的x坐标的位置
			while (positionX < ptr->position.first)
			{
				cout << " ";
				++positionX;
			}
			cout << ptr->name << " ";
			positionX += ptr->name.length() + 1;
		}
		//当前层结束,输出一个回车
		cout << endl;
		positionX = 0;
		++positionY;
		nodeNumber = newNodeNumber;
	}
}

int familyTree::maxPile(familyTreeNode* ptr)
{
	if (ptr->children.empty())
		return 1;
	else
	{
		int maxPileOfChild = 1;
		for (auto i = ptr->children.begin(); i != ptr->children.end(); ++i)
			maxPileOfChild = MAX(maxPileOfChild, maxPile(*i));
		return maxPileOfChild;
	}
}

int familyTree::maxHorizontalDistance(familyTreeNode* ptr)
{
	//首先获取自身字符串的长度
	int childLength = 0;
	if (ptr->children.empty())
	{
		ptr->childHorizonalLength = 0;
		return ptr->name.length();
	}
	else
	{
		for (auto i = ptr->children.begin(); i != ptr->children.end(); ++i)
		{
			childLength += maxHorizontalDistance(*i);
		}
		//空格
		childLength += (ptr->children.size() - 1) * 5;
	}
	ptr->childHorizonalLength = childLength; 

	return MAX(int(ptr->name.length()), childLength);
}

void familyTree::setNodeY(familyTreeNode* ptr, int pile)
{
	ptr->position.second = pile;
	for (auto i = ptr->children.begin(); i != ptr->children.end(); ++i)
		setNodeY(*i, pile + 1);
}

void familyTree::setNodeY()
{
	if (root != nullptr)
		setNodeY(root, 0);
}

void familyTree::setNodeX()
{
	//首先获取最大坐标
	if (root == nullptr)
		return;

	this->maxHorizontalLength = maxHorizontalDistance(root);

	root->position.first = maxHorizontalLength / 2 - int(root->name.length()) / 2;
	this->minPositionX = 0;
	this->setNodeX(root);

	if (minPositionX < 0)
		this->offsetX(root);
}

void familyTree::setNodeX(familyTreeNode* ptr)
{
	if (ptr->children.empty())
		return;
	else if (ptr->children.size() == 1)
		//一个孩子
	{
		ptr->children[0]->position.first = ptr->position.first + int(ptr->name.length()) / 2
			- int(ptr->children[0]->name.length()) / 2;
		if (minPositionX > ptr->children[0]->position.first)
		{
			minPositionX = ptr->children[0]->position.first;
		}
		setNodeX(ptr->children[0]);
		return;
	}
	//获取其下一层结点的长度(从第一个名字的起始位置到最后一个名字的末尾位置)
	int childLength = ptr->childHorizonalLength
		+
		(-MAX(int(ptr->children[0]->childHorizonalLength), int(ptr->children[0]->name.length()))
			+ int(ptr->children[0]->name.length())
			- MAX(ptr->children[ptr->children.size() - 1]->childHorizonalLength,
				int(ptr->children[ptr->children.size() - 1]->name.length()))
			+ int(ptr->children[ptr->children.size() - 1]->name.length())) / 2;
	
	//计算起始位置
	int startPosition = ptr->position.first + (-childLength
		+ int(ptr->name.length())) / 2;

	if (minPositionX > startPosition)
	{
		minPositionX = startPosition;
	}

	for (auto i = ptr->children.begin(); i != ptr->children.end(); ++i)
	{
		if (i != ptr->children.begin())
		{
			startPosition += (MAX((*i)->childHorizonalLength, int((*i)->name.length())) -
				int((*i)->name.length())) / 2 ;
		}

		(*i)->position.first = startPosition;
		//处理该结点
		setNodeX(*i);
		//开始位置
		startPosition += (MAX((*i)->childHorizonalLength, int((*i)->name.length())) +
			int((*i)->name.length())) / 2 + 5;
	}
}

void familyTree::setNodePosition()
{
	this->setNodeX();
	this->setNodeY();
}

//修正偏移量
void familyTree::offsetX(familyTreeNode* ptr)
{
	ptr->position.first += -minPositionX;
	for (auto i = ptr->children.begin(); i != ptr->children.end(); ++i)
		offsetX(*i);
	return;
}

int main()
{
	cout << endl << "**                 家谱管理系统                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA --- 完善    家庭\t\t**" << endl;
	cout << "**\t\tB --- 添加家庭成员\t\t**" << endl;
	cout << "**\t\tC --- 解散局部家庭\t\t**" << endl;
	cout << "**\t\tD --- 更改家庭成员姓名\t\t**" << endl;
	cout << "**\t\tE --- 退出    程序\t\t**" << endl;
	cout << "**\t\tF --- 切换树形显示模式\t\t**" << endl;
	cout << "==================================================" << endl;
	familyTree tree;
	tree.BuildTree();

	char op;
	bool exitTree = false;
	while (!exitTree)
	{
		cout << endl << "请选择要执行的操作：";
		cin >> op;
		switch (op)
		{
		case 'A':
		case 'a':
			tree.BuildFamily();
			tree.ShowTree();
			break;
		case 'B':
		case 'b':
			tree.AddFamilyMember();
			tree.ShowTree();
			break;
		case 'C':
		case 'c':
			tree.DelFamily();
			tree.ShowTree();
			break;
		case 'D':
		case 'd':
			tree.RenameFamilyMember();
			tree.ShowTree();
			break;
		case 'E':
		case 'e':
			exitTree = true;
			break;
		case 'F':
		case 'f':
			if (tree.showVertical)
			{
				cout << "当前树的显示模式已切换为横向显示！" << endl;
				tree.showVertical = false;
			}
			else
			{
				cout << "当前树的显示模式已切换为竖向显示！" << endl;
				tree.showVertical = true;
			}
			tree.ShowTree();
			break;
		default:
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "请输入合法的执行操作符" << endl;
		}
	}

	return 0;
}
