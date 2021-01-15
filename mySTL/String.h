#ifndef _MY_STRING
#define _MY_STRING

#define STRING_DEFAULT_SIZE 50

#include<iostream>

class String
{
private:
	char *_elements;
	int _size;
	int _capacity;

	//扩容
	void expand();
public:
	//求指定字符串常量的长度
	static int lengthOfStr(const char *ptr);
	//判断是否为数字
	static inline bool isdigit(char word)
	{
		return word >= '0'&&word <= '9';
	}
	//判断是否为大写字母
	static inline bool isupper(char word)
	{
		return word >= 'A'&&word <= 'Z';
	}
	//判断是否为小写字母
	static inline bool islower(char word)
	{
		return word >= 'a'&&word <= 'z';
	}
	//判断是否为字母
	static inline bool isalpha(char word)
	{
		return isupper(word) || islower(word);
	}
	//判断是否为空
	static inline bool isblank(char word)
	{
		return word == '\0';
	}
public:
	//默认构造函数
	String();
	//复制构造函数
	String(const String&);
	//字符串常量方式的构造
	String(const char*);
	//指定长度的构造方式
	String(const char*,int);
	//字符成倍的构造
	String(int, char);

	//析构函数
	~String();

	//重载取下标运算符
	inline char& operator[](int index);
	//重载等号运算符
	String& operator=(const String& s);
	//重载字符串常量的等号运算符
	String& operator=(const char*);
	//重载输入输出
	friend std::istream& operator>>(std::istream &in,String& s);
	friend std::ostream& operator<<(std::ostream &out,const String& s);
	//重载==运算符
	bool operator==(const String& s);
	//重载+运算符
	String operator+(const String& s);
	//重载+=运算符
	String& operator+=(const String& s);

	//清空字符串
	void clear();

	//返回字符串常量
	const char * c_str()const;

	//返回字符串长度
	int length()const;

	//友元类
	friend class BigInterger;
};

//默认构造函数
String::String()
{
	this->_capacity = STRING_DEFAULT_SIZE;
	this->_size = 0;
	//根据默认容量大小分配空间
	this->_elements = new char[_capacity];
	this->_elements[0] = '\0';
	if (_elements == nullptr)
		;
}

//复制构造函数
String::String(const String& s)
{
	this->_capacity = s._capacity;
	this->_size = s._size;
	//分配空间
	this->_elements = new char[_capacity];
	if (_elements == nullptr)
		;

	//复制
	for (int i = 0; i <= _size; ++i)
		this->_elements[i] = s._elements[i];
}

//字符串常量方式的构造
String::String(const char*s)
{
	//获取字符串常量长度
	int size = 0;
	while (s[size] != '\0')
		size++;
	
	this->_size = size;
	this->_capacity = (size / STRING_DEFAULT_SIZE + 1)*STRING_DEFAULT_SIZE;
	this->_elements = new char[_capacity];

	//一一复制
	for (int i = 0; i <= _size; ++i)
		this->_elements[i] = s[i];
}

//指定长度的构造方式
String::String(const char*s, int length)
{
	int strLength = this->lengthOfStr(s);
	this->_capacity = (length / STRING_DEFAULT_SIZE + 1)*STRING_DEFAULT_SIZE;
	//计算有效长度
	if (strLength >= length)
		this->_size = length;
	else
		this->_size = strLength;
	//申请空间
	this->_elements = new char[_capacity];
	for (int i = 0; i < _size; ++i)
		this->_elements[i] = s[i];
	this->_elements[_size] = '\0';
}

//字符成倍的构造
String::String(int num,char word)
{
	this->_size = num;
	this->_capacity = (_size / STRING_DEFAULT_SIZE + 1)*STRING_DEFAULT_SIZE;
	this->_elements = new char[_capacity];
	for (int i = 0; i < _size; ++i)
		this->_elements[i] = word;
	this->_elements[_size] = '\0';

}

//析构函数
String::~String()
{
	delete[]_elements;
}

//重载取下标运算符
inline char& String::operator[](int index)
{
	if (index < 0 || index >= _size)
		;

	return _elements[index];
}

//重载等号运算符
String& String::operator=(const String& s)
{
	if (this->_elements == s._elements)
		return *this;

	//清空所有元素
	delete[] _elements;

	//一一对应
	this->_capacity = s._capacity;
	this->_size = s._size;
	//分配空间
	this->_elements = new char[_capacity];
	if (_elements == nullptr)
		;

	//复制
	for (int i = 0; i <= _size; ++i)
		this->_elements[i] = s._elements[i];

	return *this;
}

//重载字符串常量的等号运算符
String& String::operator=(const char*s)
{
	//清空所有元素
	delete[] _elements;

	//获取字符串常量长度
	int size = 0;
	while (s[size] != '\0')
		size++;

	this->_size = size;
	this->_capacity = (size / STRING_DEFAULT_SIZE + 1)*STRING_DEFAULT_SIZE;
	this->_elements = new char[_capacity];

	//一一复制
	for (int i = 0; i <= _size; ++i)
		this->_elements[i] = s[i];

	return *this;
}


//清空字符串
void String::clear()
{
	//清空所有元素
	delete[] _elements;

	//调用默认构造函数
	this->_capacity = STRING_DEFAULT_SIZE;
	this->_size = 0;
	//根据默认容量大小分配空间
	this->_elements = new char[_capacity];
	if (_elements == nullptr)
		;
}

//扩大容量
void String::expand()
{
	this->_capacity += STRING_DEFAULT_SIZE;

	char* oldElements = this->_elements;

	//复制
	this->_elements = new char[_capacity];
	for (int i = 0; i <= _size; ++i)
		_elements[i] = oldElements[i];

	delete[] oldElements;
}

std::istream& operator>>(std::istream &in,String& s)
{
	in >> s._elements;
	//注意需要更改_size
	s._size = s.lengthOfStr(s._elements);
	return in;
}

std::ostream& operator<<(std::ostream &out,const String& s)
{
	out << s._elements;
	return out;
}

//重载==运算符
bool String::operator==(const String& s)
{
	//判断长度
	if (this->_size != s._size)
		return false;
	//逐一对比
	for (int i = 0; i < this->_size; ++i)
		if (this->_elements[i] != s._elements[i])
			return false;
	
	return true;
}

//重载+运算符
String String::operator+(const String& s)
{
	String str(this->_elements, this->_size + s._size);
	str._size = this->_size + s._size;
	for (int i = this->_size; i < str._size; ++i)
		str._elements[i] = s._elements[i - this->_size];
	str._elements[str._size] = '\0';
	return str;
}

//重载+=运算符
String& String::operator+=(const String& s)
{
	this->_capacity = ((this->_size+s._size) / STRING_DEFAULT_SIZE + 1)*STRING_DEFAULT_SIZE;
	char* newStr = new char[_capacity];
	for (int i = 0; i < this->_size; ++i)
		newStr[i] = this->_elements[i];
	this->_size += s._size;
	for (int i = this->_size - s._size; i < this->_size; ++i)
		newStr[i] = s._elements[i - this->_size + s._size];
	newStr[this->_size] = '\0';
	delete this->_elements;
	this->_elements = newStr;
	return *this;
}

//求指定字符串常量的长度
int String::lengthOfStr(const char *ptr)
{
	int size = 0;
	while (ptr[size] != '\0')
		++size;
	return size;
}

//返回字符串常量
const char * String::c_str()const
{
	return _elements;
}

int String::length()const
{
	return this->lengthOfStr(this->c_str());
}




#endif // !_MY_STRING
