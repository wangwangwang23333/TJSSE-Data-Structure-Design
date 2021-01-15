#ifndef _MY_QUEUE_
#define _MY_QUEUE_

#include "List.h"

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
