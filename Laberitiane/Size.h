#pragma once
template <typename T>
class Size
{

	T x_f;
	T y_f;

public:
	Size() {}
	Size(T x_, T y_) :
		x_f(x_),
		y_f(y_) {}
	~Size() {}

	T x()
	{
		return x_f;
	}
	T y()
	{
		return y_f;
	}

	void x(T x_)
	{
		x_f = x_;
	}
	void y(T y_)
	{
		y_f = y_;
	}
};