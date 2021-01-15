#ifndef _MY_RBTREE_
#define _MY_RBTREE_

#include "Pair.h"
#include "Functional.h"
#include "Algorithm.h"

enum rbtree_node_color
{
	_node_color_black = 0,
	_node_color_red = 1
};

//红黑树节点
template<class Key,class Type>
struct rbtree_node
{
	rbtree_node_color _color;//颜色
	rbtree_node *_parent;
	rbtree_node *_left;
	rbtree_node *_right;
	Key _key;
	Type _value;
	//默认构造函数
	rbtree_node()
	{
		_left = nullptr;
		_right = nullptr;
		_parent = nullptr;
	}
	//构造函数
	rbtree_node(const Key &key, const Type &val, rbtree_node* parent = nullptr, rbtree_node *left = nullptr,
		rbtree_node* right = nullptr, rbtree_node_color color = _node_color_red) :
		_key(key), _value(val), _parent(parent), _left(left), _right(right), _color(color) {};
};

template<class Key,class Val>
class tree_iterator
{
	typedef rbtree_node<Key,Val>* pointer;
	typedef tree_iterator<Key, Val> self;
public:
	pointer _iterator;
public:
	tree_iterator() :_iterator(nullptr) {};
	tree_iterator(pointer data) :_iterator(data) {};
	//取值
	pointer operator*()const
	{
		return this->_iterator;
	}
	//前置自增
	self& operator++()
	{
		
		if (_iterator->_right)
			//一路右下
		{
			_iterator = _iterator->_right;
			while (_iterator->_left)
				_iterator = _iterator->_left;
		}
		else
		{
			pointer p = _iterator->_parent;
			while (_iterator == p->_right)
			{
				_iterator = p;
				p = p->_parent;
			}
			if (_iterator->_right != p)
				_iterator = p;
		}

		return *this;
	}
	//前置自减
	self& operator--()
	{
		if (_iterator->_left)
		{
			_iterator = _iterator->_left;
			while (_iterator->_right)
				_iterator = _iterator->_right;
		}
		else
		{
			pointer p = _iterator->_parent;
			while (_iterator == p->left)
			{
				_iterator = p;
				p = p->_parent;
			}
			if (_iterator != p)
				_iterator = p;
		}
		
		return *this;
	}

	self operator++(int)
	{
		self old(*this);
		++*this;
		return old;
	}
	self operator--(int)
	{
		self old(*this);
		--*this;
		return old;
	}

};

//重载==运算符
template<class Key, class Val>
inline bool operator==(const tree_iterator<Key, Val>& iterator_a,
	const tree_iterator<Key, Val>& iterator_b)
{
	return iterator_a._iterator == iterator_b._iterator;
}

//重载！=运算符
template<class Key, class Val>
inline bool operator!=(const tree_iterator<Key, Val>& iterator_a,
	const tree_iterator<Key, Val>& iterator_b)
{
	return iterator_a._iterator != iterator_b._iterator;
}

template<class Key,class Val,class ValtoKey,class Compare>
class Rbtree
{
	typedef rbtree_node<Key,Val>* pointer;
	typedef tree_iterator<Key,Val> iterator;
private:
	pointer _head;//头节点，父节点为root,_left为最小节点，_right为最大节点
	int _size;//红黑树的节点个数
public:
	//默认构造函数
	Rbtree()
	{
		_head = new rbtree_node<Key,Val>();
		_head->_color = _node_color_red;
		_head->_parent = _head;
		_head->_left = _head;
		_head->_right = _head;
		_size = 0;
	}
private:
	//获取节点的Key值
	inline static Key _key(pointer ptr) { return ValtoKey()(ptr->_value); };
	//获取节点的Value
	inline static Val _value(pointer ptr) { return ptr->_value; };
	//将Value值转化为Key值
	inline static Val ValToKey(const Val &value) { return ValtoKey()(value); };
public:
	
	//插入Key
	Pair<iterator, bool> insert_key(const Key&key)
	{
		Key keyOfValue = key;
		Val value;

		//????????????????????????????????(??????????????)
		if (_head->_parent == _head)
		{
			_head->_parent = new rbtree_node<Key,Val>(keyOfValue,value, _head, nullptr, nullptr, _node_color_black);
			//??????С?????????
			_head->_left = _head->_parent;
			_head->_right = _head->_parent;
			++_size;
			return Pair<iterator, bool>(_head->_parent, false);
		}

		//????key???????????λ??
		Pair<pointer, bool> result = findKeyReturnPair(_head->_parent, keyOfValue);
		
		//????????,???????????????
		if (result.second)
		{
			return Pair<iterator, bool>(result.first, false);
		}

		//?????????????????result.first???????λ???????????
		pointer father = result.first;
		++_size;
		//???son??λ??
		pointer son = new rbtree_node<Key,Val>(keyOfValue,value, father);
		if (father->_key < keyOfValue)
			father->_right = son;
		else
			father->_left = son;

		//???????????С???仯
		if (keyOfValue > _head->_right->_key)
		{
			_head->_right = son;
		}
		else if (keyOfValue < _head->_left->_key)
		{
			_head->_left = son;
		}

		//???????
		//???????????adjust????
		adjustPointer(son);

		//????????????????????
		return Pair<iterator, bool>(son, true);
	}
private:
	//调整节点
	void adjustPointer(pointer ptr)
	{
		pointer son = ptr;
		pointer father = ptr->_parent;

		//????0:???????????,??????????
		if (father == _head)
			return;

		//????1:?????????????????б????????????
		if (father->_color == _node_color_black)
			return;

		//???????ζ?????????????????
		//?????????游???
		pointer grandfather = father->_parent;
		pointer uncle = (father == grandfather->_left ? grandfather->_right : grandfather->_left);

		//????2:???????????????
		if (uncle != nullptr&&uncle->_color == _node_color_red)
		{
			//???????????????????????????
			//?????游??????????
			father->_color = _node_color_black;
			uncle->_color = _node_color_black;
			grandfather->_color = _node_color_red;
			//??????
			adjustPointer(grandfather);
		}
		else
			//?????????:????????????????
		{
			//????3:??????????????游??????????
			if (father == grandfather->_left)
			{
				//3.1:???????????????????
				if (son == father->_left)
				{
					//1.??????????????
					father->_color = _node_color_black;
					//2.???游??????????
					grandfather->_color = _node_color_red;
					//3.????
					//??????????????
					if (grandfather == grandfather->_parent->_parent)
					{
						grandfather->_parent->_parent = father;
					}
					else if (grandfather == grandfather->_parent->_right)
					{
						grandfather->_parent->_right = father;
					}
					else
					{
						grandfather->_parent->_left = father;
					}
					grandfather->_left = father->_right;
					if (father->_right != nullptr)
					{
						father->_right->_parent = grandfather;
					}
					father->_right = grandfather;
					father->_parent = grandfather->_parent;
					grandfather->_parent = father;

				}
				else
					//3.2:???????????????????
				{
					//1.?????????????
					grandfather->_left = son;
					son->_parent = grandfather;
					father->_parent = son;
					father->_right = son->_left;
					if (father->_right != nullptr)
					{
						father->_right->_parent = father;
					}
					son->_left = father;
					//2.??father(??????????son)???е???
					adjustPointer(father);
				}
			}
			else
				//????4:??????????????游??????????
			{
				//4.1:???????????????????
				if (son == father->_right)
				{
					//1.??????????????
					father->_color = _node_color_black;
					//2.???游??????????
					grandfather->_color = _node_color_red;
					//3.????
					//??????????????
					if (grandfather == grandfather->_parent->_parent)
					{
						grandfather->_parent->_parent = father;
					}
					else if (grandfather == grandfather->_parent->_right)
					{
						grandfather->_parent->_right = father;
					}
					else
					{
						grandfather->_parent->_left = father;
					}
					grandfather->_right = father->_left;
					if (father->_left != nullptr)
					{
						father->_left->_parent = grandfather;
					}
					father->_left = grandfather;
					father->_parent = grandfather->_parent;
					grandfather->_parent = father;


				}
				else
					//???????????????????
				{
					//1.?????????????
					grandfather->_right = son;
					son->_parent = grandfather;
					father->_parent = son;
					father->_left = son->_right;
					if (father->_left != nullptr)
					{
						father->_left->_parent = father;
					}
					son->_right = father;
					//2.??father(??????????son)???е???
					adjustPointer(father);
				}
			}
		}

	}

public:
	inline bool empty()const noexcept
	{
		return _size == 0;
	}
	inline int size()const
	{
		return _size;
	}
	iterator begin()const
	{
		return _head->_left;
	}
	iterator end()const
	{
		return _head;
	}
private:
	//查找Key是否存在
	bool findKey(const Key& key)const
	{
		if (_head->_parent == nullptr)
			return false;
		pointer ptr = _head->_parent;
		while (ptr != nullptr)
		{
			if (key > ptr->_key)
				ptr = ptr->_right;
			else if (key < ptr->_key)
				ptr = ptr->_left;
			else
				return true;
		}
		return false;
	}

	//???????
	Pair<pointer, bool> findKeyReturnPair(pointer ptr,const Key&key)
	{
		//???????????ptr?????nullptr??????key??????
		if (ptr == nullptr)
		{
			return Pair<pointer, bool>(nullptr, false);
		}
		//????????????ptr????????
		if (ptr->_key == key)
		{
			//?????????????????????
			return Pair<pointer, bool>(ptr, true);
		}
		
		//????????????????
		Pair<pointer, bool> result(nullptr,false);
		//??????
		if (ptr->_key > key)
		{
			//???????????????????
			result = findKeyReturnPair(ptr->_left, key);
		}
		else
		{
			result = findKeyReturnPair(ptr->_right, key);
		}
		//???????????????nullptr??????????????????????λ???????
		//????nullptr??????????
		if (result.first == nullptr&&result.second == false)
		{
			result.first = ptr;
			return result;
		}
		else
			//??????????
		{
			return result;
		}
	}

public:
	//递归查找节点
	pointer findKeyReturnPointer(pointer ptr,const Key&key)const
	{
		if (ptr == _head ||ptr==nullptr)
			return _head;
		if (ptr->_key == key)
			return ptr;
		else if (ptr->_key > key)
		{
			return findKeyReturnPointer(ptr->_left, key);
		}
		else
		{
			return findKeyReturnPointer(ptr->_right, key);
		}
	}

	template<class Key, class Val, class Compare>
	friend class Map;

public:
	//??????????????????
	template<class isFit>
	int sumFitablePoint(isFit cmp)const
	{
		if (_head->_parent == _head)
			return 0;
		return sumFitablePoint(_head->_parent, cmp);
	}

private:
	template<class isFit>
	int sumFitablePoint(pointer ptr, isFit cmp)const
	{
		if (ptr == nullptr)
		{
			return 0;
		}
		if (cmp(ptr->_value))
		{
			return 1 + sumFitablePoint(ptr->_left, cmp) +
				sumFitablePoint(ptr->_right, cmp);
		}
		else
			return sumFitablePoint(ptr->_left, cmp) +
			sumFitablePoint(ptr->_right, cmp);
	}

	static pointer _local_min(pointer root)
	{
		while (root->_left != nullptr)
			root = root->_left;
		return root;
	}

	static pointer _local_max(pointer root)
	{
		while (root->_right != nullptr)
			root = root->_right;
		return root;
	}

	void _tree_rotate_left(pointer pos)
	{
		pointer rc = pos->_right;
		pointer rclc = rc->_left;
		pos->_right = rclc;
		rc->_left = pos;
		rc->_parent = pos->_parent;
		if (rclc)
			rclc->_parent = pos;
		if (pos == _head->_parent)
			_head->_parent = rc;
		else if (pos == pos->_parent->_left)
			pos->_parent->_left = rc;
		else
			pos->_parent->_right = rc;
		pos->_parent = rc;
	}

	void _tree_rotate_right(pointer pos)
	{
		pointer lc = pos->_left;
		pointer lcrc = lc->_right;
		pos->_left = lcrc;
		lc->_right = pos;
		lc->_parent = pos->_parent;
		if (lcrc)
			lcrc->_parent = pos;
		if (pos == _head->_parent)
			_head->_parent = lc;
		else if (pos == pos->_parent->_right)
			pos->_parent->_right = lc;
		else
			pos->_parent->_left = lc;
		pos->_parent = lc;
	}

	pointer &_left() const noexcept { return _head->_left; }
	pointer &_right() const noexcept { return _head->_right; }
	pointer &_root() const noexcept { return _head->_parent; }

public:
	void erase(iterator pos)
	{
		pointer rm = pos._iterator;
		pointer succ = nullptr;
		pointer rrm = nullptr;
		pointer succ_p = rm->_parent; //?????????????, succ?????null, ???????????

		//// Step 1: ??????
		if (rm->_left == nullptr) //1.????????,????????(???????)??????
			succ = rm->_right;
		else if (rm->_right == nullptr) //2.????????,????????,??????????????
			succ = rm->_left;
		else
		{ //3.???????,????????????,???????1
			++pos;
			rrm = pos._iterator;
			succ = rrm->_right; //?????????????????,????????????
		}
		//// Step 2: ????????????
		if (rrm != nullptr)
		{ //???????????3, ???rm???, ??rrm????????rm????λ??
			rm->_left->_parent = rrm;
			rrm->_left = rm->_left;
			if (rrm != rm->_right)
			{
				succ_p = rrm->_parent;
				if (succ)
					succ->_parent = succ_p;
				succ_p->_left = succ;
				rrm->_right = rm->_right;
				rm->_right->_parent = rrm;
			}
			else
				succ_p = rrm;
			if (_root() == rm)
				_root() = rrm;
			else if (rm->_parent->_left == rm)
				rm->_parent->_left = rrm;
			else
				rm->_parent->_right = rrm;
			rrm->_parent = rm->_parent;
			mySTL::swap(rrm->_color, rm->_color); //???????
		}
		else
		{ // rrm == nullptr ???????????1,2
			if (succ)
				succ->_parent = rm->_parent;
			if (_root() == rm)
				_root() = succ;
			else if (rm->_parent->_left == rm)
				rm->_parent->_left = succ;
			else
				rm->_parent->_right = succ;
			if (rm == _left())
				_left() = (rm->_right == 0 ? rm->_parent : _local_min(succ));
			if (rm == _right())
				_right() = (rm->_left == 0 ? rm->_parent : _local_max(succ));
		}
		//// Step 3: ???????????
		if (rm->_color != _node_color_red) //??б???????????????????
		{
			while (succ != _root() && (succ == nullptr || succ->_color == _node_color_black))
			{ //???????: succ????????succ????
				if (succ == succ_p->_left)
				{
					pointer s = succ_p->_right; //succ?????
					if (s->_color == _node_color_red)
					{ /* s?????????(??p????),????s??p??λ?ú???? */
						s->_color = _node_color_black;
						succ_p->_color = _node_color_red;
						_tree_rotate_left(succ_p);
						s = succ_p->_right; //???sibiling????????
					}
					/* ????, s???????? */
					if ((s->_left == nullptr || s->_left->_color == _node_color_black) &&
						(s->_right == nullptr || s->_right->_color == _node_color_black))
					{                               // s??к??????
						s->_color = _node_color_red; //??s?????,??rm?????????
						succ = succ_p;              //?????????????,???????
						succ_p = succ->_parent;
					}
					else
					{ // s?к????????
						if (s->_right == nullptr || s->_right->_color == _node_color_black)
						{                                       // ??????
							s->_left->_color = _node_color_black; //????????????
							s->_color = _node_color_red;         //??s??????
							_tree_rotate_right(s);
							s = succ_p->_right;
						}
						s->_color = succ_p->_color;
						succ_p->_color = _node_color_black;
						if (s->_right)
							s->_right->_color = _node_color_black;
						_tree_rotate_left(succ_p);
						break;
					}
				}
				else
				{                              // succ == succ_p->_right ??????
					pointer s = succ_p->_left; //succ?????
					if (s->_color == _node_color_red)
					{ /* s?????????(??p????),????s??p??λ?ú???? */
						s->_color = _node_color_black;
						succ_p->_color = _node_color_red;
						_tree_rotate_right(succ_p);
						s = succ_p->_left; //???sibiling????????
					}
					/* ????, s???????? */
					if ((s->_left == nullptr || s->_left->_color == _node_color_black) &&
						(s->_right == nullptr || s->_right->_color == _node_color_black))
					{                               // s??к??????
						s->_color = _node_color_red; //??s?????,??rm?????????
						succ = succ_p;              //?????????????,???????
						succ_p = succ->_parent;
					}
					else
					{ // s?к????????
						if (s->_left == nullptr || s->_left->_color == _node_color_black)
						{                                        // ??????
							s->_right->_color = _node_color_black; //????????????
							s->_color = _node_color_red;          //??s??????
							_tree_rotate_left(s);
							s = succ_p->_left;
						}
						s->_color = succ_p->_color;
						succ_p->_color = _node_color_black;
						if (s->_left)
							s->_left->_color = _node_color_black;
						_tree_rotate_right(succ_p);
						break;
					}
				}
			}
			if (succ)
				succ->_color = _node_color_black;
		}
		//// Step 4: ??????
		free(rm);
		--_size;
	}
};


#endif // !_MY_RBTREE_