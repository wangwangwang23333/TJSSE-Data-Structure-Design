#ifndef _MY_QUEUE_
#define _MY_QUEUE_



//结点类
template<class Type>
struct ListNode
{
	//数据
	Type data;
	ListNode<Type>* next, *prev;

	//构造函数
	//默认构造函数
	ListNode() :next(nullptr), prev(nullptr) {};
	//构造函数
	ListNode(Type datas, ListNode<Type>* nexts = nullptr, ListNode<Type>* prevs = nullptr) :data(datas), next(nexts), prev(prevs) {};

};


template<class Type>
class List
{
	typedef ListNode<Type>* _iterator;



private:
	//头指针
	ListNode<Type>* head;
	//尾指针
	ListNode<Type>* tail;
	//链表长度
	int _size;

public:
	//默认构造函数
	List();
	//复制构造函数
	List(const List<Type>& li);

	//析构函数
	~List();

	//迭代器类
	class iterator
	{
	private:
		_iterator data;//一个指针
	public:

		//默认构造函数
		iterator() :data(nullptr) {};
		//构造函数
		iterator(_iterator datas) :data(datas) {};
		iterator(Type d)
		{
			data = new ListNode<Type>;
			data->data = d;
		}

		//运算符重载
		//读数据操作
		Type& operator*()
		{
			return data->data;
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
		inline List<Type>::iterator& operator++()
			//前置自增
		{
			if (this->data != nullptr)
				this->data = this->data->next;
			return (*this);
		}
		List<Type>::iterator operator++(int)
			//后置自增
		{
			List<Type>::iterator old = (*this);
			++(*this);
			return old;
		}
		//自减运算符
		inline List<Type>::iterator& operator--()
			//前置自减
		{
			if (this->data != nullptr)
				this->data = this->data->prev;
			return (*this);
		}
		List<Type>::iterator operator--(int)
			//后置自减
		{
			List<Type>::iterator old = (*this);
			--(*this);
			return old;
		}
		//后加上一个数
		List<Type>::iterator operator+(int index)
		{
			List<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//前加上一个数
		friend typename List<Type>::iterator operator+(int index, typename List<Type>::iterator data)
		{
			List<Type>::iterator old = data;
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//后减去一个数
		List<Type>::iterator operator-(int index)
		{
			List<Type>::iterator old = (*this);
			for (int i = 0; i < index; ++i)
				--old;
			return old;
		}
		//自加
		List<Type>::iterator& operator+=(int index)
		{
			for (int i = 0; i < index; ++i)
				++(*this);
			return (*this);
		}
		//自减
		List<Type>::iterator& operator-=(int index)
		{
			for (int i = 0; i < index; ++i)
				--(*this);
			return (*this);
		}
		//计算两个迭代器之间的距离
		int operator-(List<Type>::iterator i)
		{
			//计算i->data通过几次取next运算能够到达this->data
			int index = 0;
			while (i->data != this->data)
			{
				++i;
				index++;
			}
			return index;
		}

		//友元类
		friend class List<Type>;
	};

	//链表长度
	inline int size()const;
	//判断链表是否为空
	inline bool empty()const;

	//在尾部插入新数据
	void push_back(Type data);
	//在头部插入新数据
	void push_front(Type data);

	//查找指定数据，返回迭代器
	List<Type>::iterator find(const Type& data)const;

	//删除指定迭代器对应的结点
	Type remove(List<Type>::iterator index);
	//删除尾结点
	void erase_last();
	//删除第一个结点
	void erase_first();
	//清空链表
	void clear();
	//插入结点
	bool insert(List<Type>::iterator index, Type i);

	//返回指定位置的一系列函数
	//起始位置迭代器
	inline List<Type>::iterator begin();
	inline const List<Type>::iterator begin()const;
	//最后位置迭代器
	inline List<Type>::iterator end();
	inline const List<Type>::iterator end()const;

	//重载等号运算符
	List<Type>& operator=(const List<Type>& li);

	//友元类
	template<class T>
	friend class Stack;
	template<class T>
	friend class Queue;
};

//默认构造函数
template<class Type>
List<Type>::List()
{
	head = new ListNode<Type>();
	tail = head;
	_size = 0;
}

//复制构造函数
template<class Type>
List<Type>::List(const List<Type>& li)
{
	head = new ListNode<Type>();
	tail = head;
	_size = 0;
	//一个一个结点的复制过去
	for (auto i = li.begin(); i != li.end(); ++i)
		this->push_back(*i);
}

//判断链表是否为空
template<class Type>
inline bool List<Type>::empty()const
{
	return tail == head;
}

//在尾部插入新数据
template<class Type>
void List<Type>::push_back(Type data)
{
	//判断链表是否为空
	if (empty())
	{
		//建立新结点
		ListNode<Type>* newNode = new ListNode<Type>(data, nullptr, head);

		//改变头指针和尾指针
		head->next = newNode;
		tail = newNode;
	}
	else
	{
		//建立新结点
		ListNode<Type>* newNode = new ListNode<Type>(data, nullptr, tail);

		//改变尾指针
		tail->next = newNode;
		tail = newNode;
	}

	++_size;
}

//在头部插入新数据
template<class Type>
void List<Type>::push_front(Type data)
{
	//判断链表是否为空
	if (empty())
	{
		//建立新结点
		ListNode<Type>* newNode = new ListNode<Type>(data, nullptr, head);

		//改变头指针和尾指针
		head->next = newNode;
		tail = newNode;
	}
	else
	{
		//建立新结点
		ListNode<Type>* newNode = new ListNode<Type>(data, head->next, head);

		//改变头结点之后的结点指针
		head->next->prev = newNode;

		//改变头结点指针
		head->next = newNode;
	}

	++_size;
}

//链表长度
template<class Type>
inline int List<Type>::size()const
{
	return _size;
}

//返回链表的起始位置
template<class Type>
inline typename List<Type>::iterator List<Type>::begin()
{
	return List<Type>::iterator(this->head->next);
}

template<class Type>
inline const  typename List<Type>::iterator List<Type>::begin()const
{
	return List<Type>::iterator(this->head->next);
}

//返回链表的最后位置
template<class Type>
inline typename List<Type>::iterator List<Type>::end()
{
	return List<Type>::iterator(this->tail->next);
}

template<class Type>
inline const typename List<Type>::iterator List<Type>::end()const
{
	return List<Type>::iterator(this->tail->next);
}

//删除指定迭代器对应的结点
template<class Type>
Type List<Type>::remove(typename List<Type>::iterator i)
{
	ListNode<Type>* node = i.data;
	Type value = node->data;

	//对node结点进行处理
	if (node == tail)
		//如果是尾结点
	{
		tail = node->prev;
		tail->next = nullptr;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	//释放空间
	delete node;

	return value;
}

template<class Type>
bool List<Type>::insert(List<Type>::iterator index, Type i)
{
	ListNode<Type>* node = index.data;
	node->prev->next = new ListNode<Type>(i, node, node->prev);
	node->prev = node->prev->next;
	return true;
}

//删除尾结点
template<class Type>
void List<Type>::erase_last()
{
	if (!empty())
	{
		//删除tail所对应的结点
		ListNode<Type>* delData = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete delData;
	}
}

//删除头结点
template<class Type>
void List<Type>::erase_first()
{
	if (!empty())
	{
		//删除tail的后继结点
		ListNode<Type>* delData = head->next;
		//判断尾结点
		if (delData == tail)
		{
			tail = head;
			head->next = nullptr;
			delete delData;
		}
		else
		{
			head->next = delData->next;
			delData->next->prev = head;
			delete delData;
		}

	}
}

//清空链表
template<class Type>
void List<Type>::clear()
{
	this->_size = 0;
	List<Type>::iterator cur = this->begin();
	while (cur.data != nullptr)
	{
		ListNode<Type>* delData = cur.data;
		cur++;
		delete delData;
	}
	this->tail = this->head;
	this->head->next = nullptr;
}

//析构函数
template<class Type>
List<Type>::~List()
{
	this->clear();
	delete this->head;
}


//重载等号运算符
template<class Type>
List<Type>& List<Type>::operator=(const List<Type>& li)
{
	//清空原来的结点
	this->clear();
	//一个一个结点的复制过去
	for (auto i = li.begin(); i != li.end(); ++i)
		this->push_back(*i);

	return *this;
}

//查找指定数据，返回迭代器
template<class Type>
typename List<Type>::iterator List<Type>::find(const Type& data)const
{
	for (auto i = begin(); i != end(); ++i)
	{
		if (*i == data)
		{
			return i;
		}
	}
	return List<Type>::iterator(nullptr);
}




template<class Type>
class Queue
{
private:
	//内部定义一个链表
	List<Type> data;

public:
	//构造函数
	//默认构造函数
	Queue();

	//判断队列是否为空
	inline bool empty()const;
	//返回队列大小
	inline int size()const;

	//入队
	void push(const Type& i);
	//出队
	void pop();

	//获取队首元素
	const Type& front()const;
	Type& front();
};

//默认构造函数
template<class Type>
Queue<Type>::Queue()
{

}

//判断队列是否为空
template<class Type>
inline bool Queue<Type>::empty()const
{
	return this->data.empty();
}

//返回队列大小
template<class Type>
inline int Queue<Type>::size()const
{
	return this->data._size;
}

//入队
template<class Type>
void Queue<Type>::push(const Type& i)
{
	this->data.push_back(i);
}

//出队
template<class Type>
void Queue<Type>::pop()
{
	this->data.erase_first();
}

//获取队首元素
template<class Type>
const Type& Queue<Type>::front()const
{
	return this->data.head->next->data;
}

template<class Type>
Type& Queue<Type>::front()
{
	return this->data.head->next->data;
}

#endif // !_MY_QUEUE_
