#ifndef _MY_STACK_
#define _MY_STACK_

#include "List.h"

template<class Type>
class Stack
{
private:
	//内部定义一个链表
	List<Type> data;

public:
	//构造函数
	//默认构造函数
	Stack();

	//判断栈是否为空
	inline bool empty()const;
	//返回栈大小
	inline int size()const;

	//入栈
	void push(const Type& i);
	//出栈
	void pop();


	//获取栈顶元素
	const Type& top()const;
	Type& top();
};

//默认构造函数
template<class Type>
Stack<Type>::Stack()
{
	//没有需要被构造的对象
}

//判断栈是否为空
template<class Type>
inline bool Stack<Type>::empty()const
{
	return this->data.empty();
}

//入栈
template<class Type>
void Stack<Type>::push(const Type& i)
{
	this->data.push_back(i);
}

//出栈
template<class Type>
void Stack<Type>::pop()
{
	this->data.erase_last();
}

//获取栈顶元素
template<class Type>
const Type& Stack<Type>::top()const
{
	return this->data.tail->data;
}

template<class Type>
Type& Stack<Type>::top()
{
	return this->data.tail->data;
}

//返回栈大小
template<class Type>
inline int Stack<Type>::size()const
{
	return this->data._size;
}


#endif // !_STACK_
