#ifndef my_Vector_H
#define my_Vector_H

#include <string>
#include <compare>

template <typename T>
struct vector2d {
	T x{ 0 };
	T y{ 0 };
	vector2d() = default;
	vector2d(T _x, T _y) : x{ _x }, y{ _y }{}
	vector2d(const vector2d& vec) : vector2d(vec.x, vec.y) {}

	bool equalized() { return this->x == this->y; }

	vector2d transpose(const vector2d& vec) {
		return { vec.y, vec.x };
	}
    
	vector2d reflect(bool bX = 1, bool bY = 1) {
        T _x{ x }, _y{ y };
        if (bX) _x = -x;
        if (bY) _y = -y;
		return { _x, _y };
	}

	const std::string str() const {
		return 
			std::string("(")
			+ std::to_string(this->x) + ","
			+ std::to_string(this->y) + ")";
	}

    auto operator<=>(const vector2d& vec) const = default;
    
    vector2d& operator=(const vector2d& vec) = default;
    vector2d operator*(const T& rhs) { return vector2d(this->x * rhs, this->y * rhs); }
    vector2d operator+(const T& rhs) { return vector2d(this->x + rhs, this->y + rhs); }
    vector2d& operator*=(const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
    vector2d operator+(const vector2d& vec) { return vector2d(this->x + vec.x, this->y + vec.y); }
    vector2d operator-(const vector2d& vec) { return vector2d(this->x - vec.x, this->y - vec.y); }
    vector2d operator*(const vector2d& vec) { return vector2d(this->x * vec.x, this->y * vec.y); }
	vector2d operator/(vector2d const& vec) { return vector2d(this->x / vec.x, this->y / vec.y); }
	vector2d operator%(vector2d const& vec) { return vector2d(this->x % vec.x, this->y % vec.y); }
};

typedef vector2d<double>    vfloat_t;
typedef vector2d<int8_t>	vi8_t;
typedef vector2d<int16_t>	vi16_t;
typedef vector2d<int32_t>	vi32_t;
typedef vector2d<uint8_t>	vui8_t;
typedef vector2d<uint16_t>	vui16_t;
typedef vector2d<uint32_t>	vui32_t;
typedef vector2d<bool>		vbool_t;

template <typename T>
vector2d<T> abs(vector2d<T> vec) { return vector2d<T>(std::abs(vec.x), std::abs(vec.y)); }

template <typename T>
vector2d<T> difference(const vector2d<T>& vec_1, const vector2d<T>& vec_2) {
	auto _x = ((vec_1.x <= vec_2.x) ? (vec_2.x - vec_1.x) : (vec_1.x - vec_2.x));
	auto _y = ((vec_1.y <= vec_2.y) ? (vec_2.y - vec_1.y) : (vec_1.y - vec_2.y));
	return vector2d<T>(_x, _y);
}
template <typename T>
float slope(vector2d<T> vec) { return float(vec.y) / vec.x; }

#endif // !my_Vector_H

