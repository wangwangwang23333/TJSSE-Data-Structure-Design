#pragma once
#include "Rbtree.h"
#include "Pair.h"
template<class Key, class Val,class Compare=Less<Key>>
class Map
{
public:
	typedef Pair<const Key, Val> val_type;

	typedef Rbtree<Key, Val, Self<Val>,Compare> data_type;
	typedef typename tree_iterator<Key,Val> iterator;
	typedef rbtree_node<Key, Val>* pointer;
private:
	//内部用一个红黑树存储数据
	data_type data;

public:
	inline bool empty()const
	{
		return data.empty();
	}

	inline int size()const
	{
		return data.size();
	}

	iterator begin()const
	{
		return data.begin();
	}

	iterator end()const
	{
		return data.end();
	}
	
	//插入
	Pair<iterator, bool> insert_key(const Key& key)
	{
		return data.insert_key(key);
	}

	//重载[]运算符
	Val& operator[](const Key &key)
	{
		Pair<iterator, bool> p = insert(key); //key存在则返回key的迭代器, key不存在则用初始值创建
		return (*p.first).second;
	}

	//确认是否存在
	size_t count(const Key&key)
	{
		pointer ptr = data.findKeyReturnPointer(data.begin()._iterator, key);
		if (ptr == nullptr || ptr == data._head)
			return 0;
		else
			return 1;
	}

	//查找Key，返回迭代器
	iterator find(const Key&key)const
	{
		return iterator(data.findKeyReturnPointer(data.begin()._iterator, key));
	}

	template<class isFit>
	int sumFitableStudent(isFit cmp)const
	{
		return data.sumFitablePoint(cmp);
	}

	void erase(iterator pos)
	{
		data.erase(pos);
	}

	Pair<iterator, bool> insert(const Key &x) 
	{ 
		return x.insert_key(x);
};

