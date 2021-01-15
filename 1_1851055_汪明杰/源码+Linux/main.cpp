#include "Student.h"
#include <fstream>
#include <sstream>
using namespace std;

//学生数据库
class DataBase
{
private:
	List<Student> table;
public:
	DataBase() {};
	~DataBase() {};
	//数据库的初始化
	void init();
	void show();
	void find();
	void insert();
	void erase();
	void count();
	void update();
	void stat();
	void saveFile();
	int size();
	void wait();
private:
	void insertProperPlace(Student& s);
};

void DataBase::init()
{
	int count_Student = 0;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请选择初始化数据库方法:" << endl;
	cout << "1.从文件中读取(默认)" << endl;
	cout << "2.手动输入" << endl;

	int temp;
	cin >> temp;
	switch (temp)
	{
	case 1:
	{
		cout << "请输入要存储文件的名称(输入0代表读取默认文件)" << endl;
		string loadFile;
		cin >> loadFile;
		if (loadFile.length() == 0)
		{
			cout << "无效名称，自动读取名为Student.txt的文件" << endl;
			loadFile = "Student.txt";
		}
		else if (loadFile == "0")
		{
			cout << "开始读取默认文件" << endl;
			loadFile = "Student.txt";
		}
		else
		{
			loadFile += ".txt";
		}

		ifstream file(loadFile);
		cout << endl << "开始读取数据:" << endl;

		Student temp;
		while (file.peek() != EOF)
		{
			file >> temp;
			this->insertProperPlace(temp);
		}

		cout << "成功读取数据！" << endl;

		this->show();

		break;
	}
	case 2:
	{
		cout << "请输入考生人数：" << endl;
		//循环输入，直到输入合理正整数
		while (true)
		{
			cin >> count_Student;
			if (cin.fail() || count_Student < 0)
			{
				cout << "请输入一个正整数！" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			else
				break;
		}
		if (count_Student == 0)
			break;
		cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
		Student temp;
		for (int i = 0; i < count_Student; ++i)
		{
			cin >> temp;
			if (table.find(temp) != table.end())
			{
				cout << "该考号对应的考生已存在！" << endl;
			}
			else
			{
				this->insertProperPlace(temp);
			}
		}
		this->show();
		break;
	}
	}

}

void DataBase::show()
{
	for (int i = 0; i < 40; ++i)
		cout << "─ ";
	cout<<endl;
	cout << "考号     \t│  姓名     \t│  性别     \t│  年龄     \t│  报考类别\n";
	for (int i = 0; i < 40; ++i)
		cout << "─ ";
	cout<<endl;
	if (table.empty())
	{
		cout << "报名系统内暂无数据！\n";
	}
	else
	{
		for (auto i = table.begin(); i != table.end(); ++i)
		{
			printf("%-10d\t│  %-10s\t│  %-10s\t│  %-10d\t│  %-10s\n", (*i)._id, (*i)._name.c_str(),
				((*i)._gender == Student::male ? "男" : "女"), (*i)._age,
				(*i)._type.c_str());
		}
		for (int i = 0; i < 40; ++i)
			cout << "─ ";
		cout << endl;
	}

}

void DataBase::insert()
{
	cout << "请输入要插入的考生的考号：";
	int StudentID;

	while (true)
	{
		cin >> StudentID;
		if (cin.fail())
		{
			cout << "请输入一个数字" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}

	Student temp;
	temp._id = StudentID;
	//查找
	if (table.find(temp) != table.end())
	{
		cout << "该考号对应的考生已存在！" << endl;
	}
	else
	{
		//插入数据
		Student temp(StudentID);
		cout << "请输入该考生的姓名，性别，年龄及报考类别！";
		input_no_id(cin, temp);
		this->insertProperPlace(temp);
	}
}

void DataBase::erase()
{
	int id;
	cout << "请选择您要删除的考生的考号：";
	cin >> id;
	auto it = table.find(id);  //迭代器
	if (it == table.end()) 
	{
		cout << "找不到考号为 " << id << " 的考生" << endl;
		return;
	}
	cout << "您删除的考生信息是：" << (*it)._id << endl;
	table.remove(it);  //使用迭代器删除
}

void DataBase::find()
{
	cout << "请输入要查找的考生的考号：";
	int StudentID;
	cin >> StudentID;
	//查找
	auto result = table.find(StudentID);
	if (result != table.end())
	{
		cout << (*result);
	}
	else
	{
		cout << "不存在考号为" << StudentID << "的考生！" << endl;
	}
	wait();
}

void DataBase::count()
{
	cout << "当前系统内共有" << table.size() << "名考生" << endl;
}

int DataBase::size()
{
	return table.size();
}

void DataBase::update()
{
	int id;
	cout << "请选择您要修改的考生的考号：";
	cin >> id;
	auto it = table.find(id);  //迭代器
	if (it == table.end())
	{
		cout << "找不到考号为 " << id << " 的考生" << endl;
		return;
	}
	cout << "请依次输入要修改的考生的姓名，性别，年龄及报考类别！" << endl;
	Student stu(id);
	input_no_id(cin, stu);
	//更新
	(*it) = stu;
}

void DataBase::stat()
{
	int sumStudent = table.size();
	int sumMale = 0;
	for (auto i = table.begin(); i != table.end(); ++i)
	{
		if ((*i)._gender == Student::male)
			++sumMale;
	}

	Vector<Pair<int, int>> age;
	int sumAge = 0, index = -1;
	int sumTeenager = 0;


	if (sumStudent == 0)
	{
		cout << "当前系统内暂无考生！" << endl;
		return;
	}
	cout << endl;
	cout << "------------------------------------------" << endl;
	cout << "考生总数:" << sumStudent << endl;
	cout << "------------------------------------------" << endl;
	cout << "性别统计" << endl;

	int drawSumMale = sumMale, drawSumFemale = sumStudent - sumMale;
	//调整个数，让绘图更美观
	while (drawSumMale > 10 && drawSumFemale > 10)
	{
		drawSumMale /= 10;
		drawSumFemale /= 10;
	}
	while (drawSumMale > 16)
		drawSumMale /= 2;
	while (drawSumFemale > 20)
		drawSumFemale /= 2;


	cout << "男生总数:";
	for (int i = 0; i < drawSumMale; ++i)
		cout << "■";

	cout << sumMale << endl;
	cout << "女生总数:";
	for (int i = 0; i < drawSumFemale; ++i)
		cout << "■";
	cout << sumStudent - sumMale << endl;

	wait();
}

void DataBase::saveFile()
{
	cout << endl;
	int size = table.size();
	if (size == 0)
	{
		cout << "当前系统内无考生，不需要保存！" << endl;
		return;
	}

	cout << "请输入要存储文件的名称(输入0存储到默认文件)" << endl;
	string saveFile;
	cin >> saveFile;
	if (cin.fail())
	{
		cout << "无效名称，自动存储为Student.txt" << endl;
		saveFile = "Student.txt";
	}
	else if (saveFile == "0")
	{
		cout << "自动存储到Student.txt" << endl;
		saveFile = "Student.txt";
	}
	else
	{
		saveFile += ".txt";
	}

	ofstream file(saveFile);
	cout << endl << "开始保存数据，进度:↓100%" << endl;

	int index = 0;
	bool firstSave = true;
	for (auto i = table.begin();
		i != table.end(); ++i, ++index)
	{
		if (firstSave)
			firstSave = false;
		else
			file << endl;
		file << (*i)._id << " " << (*i)._name << " " <<
			((*i)._gender == Student::male ? "男" : "女") << " "
			<< (*i)._age << " " << (*i)._type;
		if (size > 10)
		{
			if (index == size / 10)
			{
				cout << "■";
				index = 0;
			}
		}
	}
	if (size <= 10)
		for (int i = 0; i < 10; ++i)
			cout << "■";
	cout << endl << "成功存储数据！" << endl << endl;

	file.close();
	wait();
}

void DataBase::wait()
{
	cout << endl << "回车键继续操作" << endl;
	cin.clear();
	cin.ignore(1024, '\n');
	cin.get();
	return;
}

void DataBase::insertProperPlace(Student& s)
{
	if (table.empty())
		table.push_back(s);
	else
	{
		//找到插入位置
		for (auto i = table.begin(); i != table.end(); ++i)
		{
			if ((*i)._id > s._id)
			{
				//在i前插入
				table.insert(i, s);
				return;
			}
		}
		//如果没找到，则直接加入尾部
		table.push_back(s);
	}
}

int main()
{

	DataBase db;
	db.init();

	string operation;
	bool quit = false;
	while (!quit)
	{
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为"
			"统计，6为保存数据，0为退出系统）\n\n";
		cin >> operation;
		switch (operation[0])
		{
		case '0':
			quit = true;
			//退出系统
			cout << "退出系统前是否需要保存数据?" << endl;
			cout << "1.是" << endl;
			cout << "2.否(默认)" << endl;
			int index;
			cin >> index;
			if (cin.fail() || index != 1)
				return 0;
			else
			{
				db.saveFile();
			}
			break;
		case '1':
			db.insert();
			break;
		case '2':
			db.erase();
			break;
		case '3':
			db.find();
			break;
		case '4':
			db.update();
			break;
		case '5':
			db.stat();
			break;
		case '6':
			db.saveFile();
			break;
		default:
			cout << "未知操作,请重新输入" << endl;
			cout << "(输入提示: "
				"1为插入，2为删除，3为查找，4为修改，5为统计，0为"
				"退出系统)"
				<< endl;
			break;
		}
		if (db.size() < 50)
			db.show();
		cout << "当前系统内共有 " << db.size() << " 条数据" << endl
			<< endl;

	}
	return 0;

}