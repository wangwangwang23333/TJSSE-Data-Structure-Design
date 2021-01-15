#pragma once

template<class Type>
struct Less
{
	bool operator()(const Type&x, const Type&y)
	{
		return x < y;
	}
};

template<class Type>
struct Greater
{
	bool operator()(const Type&x, const Type&y)
	{
		return x > y;
	}
};

template<class Type>
struct Self
{
	Type operator()(const Type&x)
	{
		return x;
	}
};

//自己实现的向量类
#define VECTOR_DEFAULT_SIZE 5 //容量大小

template<class Type>
class Vector
{
	typedef Type* Pointer;
	typedef Pointer _iterator;

private:
	//数据大小
	int _size;
	//当前容量
	int _capacity;
	//数据
	Type* _elements;

	//从data指针中复制[low,high)的一段数据
	Type* copyFrom(Type *data, int low, int high, int size = 0);

	//扩大元素容量
	void expand();
public:
	//构造函数
	Vector();//默认构造函数
	Vector(int size);//初始大小的构造函数
	Vector(const Vector &v);//复制构造函数
	Vector(int sz, Type data)
	{
		this->_size = sz;
		this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1)*VECTOR_DEFAULT_SIZE;

		//分配空间
		this->_elements = new Type[_capacity];
		if (_elements == nullptr)
			;
		for (int i = 0; i < sz; ++i)
			this->_elements[i] = data;
	}

	//析构函数
	~Vector();

	//迭代器类
	class iterator
	{
	private:
		_iterator data;//一个指针
	public:
		typedef Type value_type;
		//默认构造函数
		iterator() :data(nullptr) {};
		//构造函数
		iterator(_iterator datas) :data(datas) {};

		//运算符重载
		//读数据操作
		Type& operator*()
		{
			return *data;
		}
		//比较运算符
		inline bool operator==(const iterator& v)const
		{
			return this->data == v.data;
		}
		inline bool operator<(const iterator& v)const
		{
			return this->data < v.data;
		}
		inline bool operator>(const iterator& v)const
		{
			return this->data > v.data;
		}
		inline bool operator>=(const iterator& v)const
		{
			return this->data >= v.data;
		}
		inline bool operator<=(const iterator& v)const
		{
			return this->data <= v.data;
		}
		inline bool operator!=(const iterator& v)const
		{
			return this->data != v.data;
		}
		//自增运算符
		inline Vector<Type>::iterator& operator++()
			//前置自增
		{
			this->data++;
			return (*this);
		}
		Vector<Type>::iterator operator++(int)
			//后置自增
		{
			Vector<Type>::iterator old = (*this);
			++(*this);
			return old;
		}
		//自减运算符
		inline Vector<Type>::iterator& operator--()
			//前置自减
		{
			this->data--;
			return (*this);
		}
		Vector<Type>::iterator operator--(int)
			//后置自减
		{
			Vector<Type>::iterator old = (*this);
			--(*this);
			return old;
		}
		//后加上一个数
		Vector<Type>::iterator operator+(int index)
		{
			Vector<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//前加上一个数
		friend typename Vector<Type>::iterator operator+(int index, typename Vector<Type>::iterator data)
		{
			typename Vector<Type>::iterator old = data;
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//后减去一个数
		Vector<Type>::iterator operator-(int index)
		{
			Vector<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i)
				--old;
			return old;
		}
		//自加
		Vector<Type>::iterator& operator+=(int index)
		{
			for (int i = 0; i < index; ++i)
				++(*this);
			return (*this);
		}
		//自减
		Vector<Type>::iterator& operator-=(int index)
		{
			for (int i = 0; i < index; ++i)
				--(*this);
			return (*this);
		}
		friend int operator-(const Vector<Type>::iterator& i, const Vector<Type>::iterator& j)
		{
			return i.data - j.data;
		}
	};



	//向量大小
	inline int size()const;
	//判断向量是否为空
	inline bool empty()const;

	//尾部插入数据
	void push_back(const Type data);
	//删除数据
	Type pop_back();
	//在指定迭代器前插入数据
	bool insert(const Vector<Type>::iterator place, Type item);
	//删除指定迭代器的数据
	bool erase(const Vector<Type>::iterator place);
	//清空数据
	void clear();
	//在指定范围内查找数据，返回其位置所对应的迭代器

	//统一赋值
	void fillData(const Type data);

	//返回指定位置的一系列函数
	//起始位置迭代器
	inline Vector<Type>::iterator begin();
	inline const Vector<Type>::iterator begin()const;
	//最后位置迭代器
	inline Vector<Type>::iterator end();
	inline const Vector<Type>::iterator end()const;
	//获取最后一个元素的迭代器
	inline Vector<Type>::iterator last();
	inline const Vector<Type>::iterator last()const;

	//第一个数据
	Type& front()const
	{
		return this->_elements[0];
	}

	//运算符重载
	//取下标运算符的重载[]
	inline Type& operator[](int i);
	//等号运算符
	Vector<Type>& operator=(const Vector<Type>& v);

	void resize(int sz)
	{
		while (this->_size < sz)
		{
			if (this->_size == this->_capacity)
				this->expand();

			_size++;
		}

		while (this->_size > sz)
		{
			_size--;
		}
	}

};

//默认构造函数
template<class Type>
Vector<Type>::Vector()
{
	this->_capacity = VECTOR_DEFAULT_SIZE;
	this->_size = 0;
	//根据默认容量大小分配空间
	this->_elements = new Type[_capacity];
	if (_elements == nullptr)
		;
}

//给定初始大小的构造函数
template<class Type>
Vector<Type>::Vector(int size)
{
	this->_size = size;
	this->_capacity = (_size / VECTOR_DEFAULT_SIZE + 1)*VECTOR_DEFAULT_SIZE;

	//分配空间
	this->_elements = new Type[_capacity];
	if (_elements == nullptr)
		;
}

//复制构造函数
template<class Type>
Vector<Type>::Vector(const Vector &v)
{


	this->_size = v._size;
	this->_capacity = v._capacity;

	//元素一一复制
	this->_elements = copyFrom(v._elements, 0, _size, _capacity);
}

//从data指针中复制[low,high)的一段数据
template<class Type>
Type* Vector<Type>::copyFrom(Type *data, int low, int high, int size)
{
	if (size == 0)
		size = high - low;

	//申请空间
	Type *newData = new Type[size];

	if (newData == nullptr)
		;

	//一一复制
	for (int i = low; i < high; ++i)
		newData[i] = data[low + i];

	return newData;
}

//获取向量元素个数
template<class Type>
inline int Vector<Type>::size()const
{
	return this->_size;
}

//扩大元素容量
template<class Type>
void Vector<Type>::expand()
{
	this->_capacity += VECTOR_DEFAULT_SIZE;

	Type* oldElements = this->_elements;

	//复制
	this->_elements = copyFrom(this->_elements, 0, _size, _capacity);

	delete[] oldElements;
}

//插入数据
template<class Type>
void Vector<Type>::push_back(const Type data)
{
	//判断容量
	if (this->_size == this->_capacity)
		this->expand();

	this->_elements[_size++] = data;
}

//取下标运算符的重载[]
template<class Type>
inline Type& Vector<Type>::operator[](int i)
{
	if (i < 0 || i >= _size)
		;

	return _elements[i];
}

//删除数据
template<class Type>
Type Vector<Type>::pop_back()
{
	if (_size == 0)
		;

	//返回最后一个数据
	return _elements[--_size];
}

//返回向量的起始位置
template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::begin()
{
	return _size > 0 ? typename Vector<Type>::iterator(&_elements[0]) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::begin()const
{
	return _size > 0 ? typename Vector<Type>::iterator(&_elements[0]) :
		typename Vector<Type>::iterator();
}

//返回向量的最后位置
template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::end()
{
	return _size > 0 ? ++(typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::end()const
{
	return _size > 0 ? ++(typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline typename Vector<Type>::iterator Vector<Type>::last()
{
	return _size > 0 ? (typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

template<class Type>
inline const typename Vector<Type>::iterator Vector<Type>::last()const
{
	return _size > 0 ? (typename Vector<Type>::iterator(&_elements[_size - 1])) :
		typename Vector<Type>::iterator();
}

//前置加一个数
template<class Type>
typename Vector<Type>::iterator operator+(int index, typename Vector<Type>::iterator data)
{
	typename Vector<Type>::iterator old = data;
	for (int i = 0; i < index; ++i)
		++old;
	return old;
}

//判断向量是否为空
template<class Type>
inline bool Vector<Type>::empty()const
{
	return this->_size == 0;
}

//在指定迭代器前插入数据
template<class Type>
bool Vector<Type>::insert(const typename Vector<Type>::iterator place, Type item)
{
	//提前记录位置(expand后位置发生变化)
	auto places = place;
	int j = places - this->begin();

	//判断是否需要扩容
	if (this->_size == this->_capacity)
		this->expand();

	//把place迭代器后面的元素依次后移一位
	int i;

	for (i = _size - 1; i >= j; --i)
		this->_elements[i + 1] = this->_elements[i];

	//最后插入新元素
	this->_elements[i + 1] = item;
	this->_size++;

	return true;
}

//删除指定迭代器的数据
template<class Type>
bool Vector<Type>::erase(const typename Vector<Type>::iterator place)
{
	//获取place的下标位置
	int index = place - this->begin();

	if (index < 0 || index >= this->_size)
		return false;

	while (index < this->_size - 1)
	{
		this->_elements[index] = this->_elements[index + 1];
		++index;
	}

	this->_size--;

	return true;
}

//清空数据
template<class Type>
void Vector<Type>::clear()
{
	//清空所有元素
	delete[] _elements;

	//调用默认构造函数
	this->_capacity = VECTOR_DEFAULT_SIZE;
	this->_size = 0;
	//根据默认容量大小分配空间
	this->_elements = new Type[_capacity];
	if (_elements == nullptr)
		;
}

//析构函数
template<class Type>
Vector<Type>::~Vector()
{
	//清空所有元素
	delete[] _elements;
}

//重载等号运算符
template<class Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& v)
{
	//防止自我等于
	if (v._elements == this->_elements)
		return *this;
	this->clear();
	//一个一个结点的复制过去
	for (auto i = v.begin(); i != v.end(); ++i)
		this->push_back(*i);

	return *this;
}

//统一赋值
template<class Type>
void Vector<Type>::fillData(const Type data)
{
	for (auto i = begin(); i != end(); ++i)
		*i = data;
}

#include<cstdlib>
namespace mySTL
{

	template <class Iter, typename T>
	Iter find(Iter begin, Iter end, const T &value)
	{
		while (begin != end) {
			if (*begin == value) return begin;
			++begin;
		}
		return end;
	}

	template<typename T>
	void swap(T& t1, T& t2) {
		T tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

	template <typename Iter>
	void random_shuffle(Iter first, Iter last)
	{
		int rest = last - first;
		while (first != last) {
			swap(*first, *(first + rand() % rest));
			--rest;
			++first;
		}
	}
}




//将*(end-1)调整到合适的位置, 使得[start,end)变成堆
template <class Iter>
void pushHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	siftFix(start, 0, end - start - 1, *(end - 1), Less<value_type>());
}

template <class Iter, class Compare>
void pushHeap(Iter start, Iter end, Compare &comp)
{
	siftFix(start, 0, end - start - 1, *(end - 1), comp);
}

//功能：将*(start)交换到*(end-1)处(以便删去), [start,end-1)变成堆
template <class Iter>
void popHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	value_type value = *(end - 1);  //将原来的末尾值保存起来
	*(end - 1) = *(start);  //将*(start)移动到*(end-1),*(start)处出现hole
	sinkFix(start, end - start - 1, 0, value, Less<value_type>());
}
template <class Iter, class Compare>
void popHeap(Iter start, Iter end, Compare &comp)
{
	typedef typename Iter::value_type value_type;
	value_type value = *(end - 1);  //将原来的末尾值保存起来
	*(end - 1) = *(start);  //将*(start)移动到*(end-1),*(start)处出现hole
	sinkFix(start, end - start - 1, 0, value, comp);
}


//功能：将[start,end)变成堆

template <class Iter>
void makeHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	ptrdiff_t len = end - start;
	if (len < 2) return;
	ptrdiff_t hole = (len - 2) / 2;
	while (hole >= 0) {
		//调整 hole 节点
		sinkFix(start, len, hole, *(start + hole), Less<value_type>());
		--hole;
	}
}

template <class Iter, class Compare>
void makeHeap(Iter start, Iter end, Compare comp)
{
	ptrdiff_t len = end - start;
	if (len < 2) return;
	ptrdiff_t hole = (len - 2) / 2;
	while (hole > 0) {
		//调整 hole 节点
		sinkFix(start, len, hole, *(start + hole), comp);
		--hole;
	}
}



//功能：向上调整hole的位置, 找到合适的位置将value存入

template <class Iterator, typename T, class Compare>
void siftFix(Iterator first,
	ptrdiff_t top,
	ptrdiff_t hole,
	T value,
	Compare comp)
{
	ptrdiff_t parent = (hole - 1) / 2;
	while (parent >= top && comp(*(first + parent), value)) {
		*(first + hole) = *(first + parent);
		hole = parent;
		parent = (hole + 1) / 2 - 1;
	}
	*(first + hole) = value;
}

//功能：向下调整hole的位置, 找到合适的位置将value存入

template <class Iterator, typename T, class Compare>
void sinkFix(Iterator first,
	ptrdiff_t len,
	ptrdiff_t hole,
	T value,
	Compare comp)
{
	/* 1.将hole下移到叶子处 */
	ptrdiff_t bigChild = 2 * hole + 2;  //从右孩子开始考虑
	while (bigChild < len) {
		if (comp(*(first + bigChild), *(first + bigChild - 1)))
			bigChild--;  //左孩子大于右孩子
		*(first + hole) = *(first + bigChild);
		hole = bigChild;
		bigChild = 2 * hole + 2;
	}
	if (len % 2 == 0 &&
		bigChild == len) {  //特殊情况：最后一个节点为左节点, 没有兄弟节点
		*(first + hole) = *(first + bigChild - 1);
		hole = bigChild - 1;
	}
	/* 2.转化为向上调整问题 */
	siftFix(first, 0, hole, value, comp);
}




template <typename T, class Compare = Less<T>, class Sequence = Vector<T>>
class PriorityQueue
{
public:

public:
	Sequence _container;
	Compare _comparer;

public:
	PriorityQueue() : _container() {}
	PriorityQueue(const Compare &comp) : _container(), _comparer(comp) {}
	template <class iterator>
	PriorityQueue(iterator first, iterator last) : _container(first, last)
	{
		makeHeap(first, last, _comparer);
	}
	template <class iterator>
	PriorityQueue(iterator first, iterator last, const Compare &comp)
		: _container(first, last), _comparer(comp)
	{
		makeHeap(first, last, _comparer);
	}
	~PriorityQueue() {}

	bool empty() const { return _container.empty(); }
	int size() const { return _container.size(); }
	const T top() const { return _container.front(); }

	void push(const T x)
	{
		_container.push_back(x);
		pushHeap(_container.begin(), _container.end(), _comparer);
	}

	void pop()
	{
		popHeap(_container.begin(), _container.end(), _comparer);
		_container.pop_back();
	}
};