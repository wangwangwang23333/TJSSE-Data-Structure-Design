#ifndef _MY_PAIR_
#define _MY_PAIR_

template<class T1,class T2>
struct Pair
{
	T1 first;
	T2 second;
	//构造函数
	Pair() {};
	Pair(const T1&, const T2&);
	Pair(const Pair&);
	template<class T3,class T4>
	Pair(const T3& first, const T4& second) :first(first), second(second) {};
	
	//运算符重载
	Pair& operator=(const Pair& rhs)
	{
		this->first = rhs.first;
		this->second = rhs.second;
		return *this;
	}
	inline bool operator==(const Pair<T1, T2>& rhs)
	{
		return first == rhs.first &&second == rhs.second;
	}
	inline bool operator!=(const Pair<T1, T2>& rhs)
	{
		return first != rhs.first || second != rhs.second;
	}

};

template<class T1,class T2>
Pair<T1,T2>::Pair(const T1&first, const T2&second)
{
	this->first = first;
	this->second = second;
}

template<class T1, class T2>
Pair<T1, T2>::Pair(const Pair<T1, T2>& rhs)
{
	this->first = rhs.first;
	this->second = rhs.second;
}

template<class T1,class T2>
bool operator<(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return rhs1.first < rhs2.first || (rhs1.first == rhs2.first&&rhs1.second < rhs2.second);
}

template<class T1, class T2>
bool operator>(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return rhs1.first > rhs2.first || (rhs1.first == rhs2.first&&rhs1.second > rhs2.second);
}

template<class T1, class T2>
bool operator<=(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return rhs1.first <= rhs2.first || (rhs1.first == rhs2.first&&rhs1.second <= rhs2.second);
}

template<class T1, class T2>
bool operator>=(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return rhs1.first >= rhs2.first || (rhs1.first == rhs2.first&&rhs1.second >= rhs2.second);
}

template<class T1, class T2>
Pair<T1, T2> operator+(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return Pair<T1,T2>(rhs1.first + rhs2.first, rhs1.second + rhs2.second);
}

template<class T1, class T2>
Pair<T1, T2> operator-(const Pair<T1, T2>& rhs1, const Pair<T1, T2>& rhs2)
{
	return Pair<T1, T2>(rhs1.first - rhs2.first, rhs1.second - rhs2.second);
}



#endif // !_MY_PAIR_