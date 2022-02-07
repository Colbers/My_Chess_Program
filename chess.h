#pragma once
#include <string>
#include <iostream>

template <typename T>
struct vector2d {
	T _x{ 0 };
	T _y{ 0 };
	vector2d() = default;
	vector2d(T x, T y) : _x{ x }, _y{ y }{}
	vector2d(vector2d& vec) : vector2d(vec._x, vec._y) {}
	
	bool inBounds(vector2d& vec) { return (this->_x < vec._x) && (this->_y < vec._y) ? true : false; }

	std::string str() { return "( " + std::to_string(_x) + ", " + std::to_string(_y) + " )"; }

	vector2d& operator=(vector2d& vec) = default;
	void operator*(vector2d& vec) { return vector2d(this->_x * vec._x, this->_x * vec._x); }

	typedef vector2d<int> v2di_t;
};