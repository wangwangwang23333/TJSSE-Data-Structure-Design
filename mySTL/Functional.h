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