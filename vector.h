#ifndef my_Vector_H
#define my_Vector_H

struct biBoolean {
	biBoolean(bool _a, bool _b) :
		a {_a}, b {_b}
	{}

	bool a{};
	bool b{};

	void set_A(bool _a) { a = _a; }
	void set_B(bool _b) { b = _b; }

	inline operator bool() const { return (a && b); }
	inline bool operator!() const { return (!a && !b); }

	const bool& x{ a };
	const bool& y{ b };
	const bool& one{ a };
	const bool& two{ b };
};

template <class T>
struct vector2d {
	T x{ 0 };
	T y{ 0 };
	vector2d() = default;
	vector2d(T _x, T _y) : x{ _x }, y{ _y }{}
	vector2d(const vector2d& vec) : vector2d(vec.x, vec.y) {}

	bool holds(const T val) { return (x == val) || (y == val); }

	bool inBounds(const vector2d& vec) const { return (this->x <= vec.x) && (this->y <= vec.y); }
	bool equalized() { return this->x == this->y; }

	vector2d mod(const vector2d& vec) {
		return  { this->x % vec.x, this->y % vec.y };
	}
	vector2d towards(const vector2d& vec) {
		return	{ int(vec.x) - this->x, int(vec.y) - this->y };
	}
	vector2d transpose(const vector2d& vec) {
		return { vec.y, vec.x };
	}
	//vector2d reflect(bool bX = 1, bool bY = 1) {
	//	if (bX && bY) return vector2d(-x, -y);
	//	if (bX) return vector2d(-x, y);
	//	if (bY) return vector2d(x, -y);
	//	else    return vector2d(x, y);

	//}

	vector2d reflect(biBoolean bib) {
		T _x{ x }, _y{ y };
		if(bib.a) _x = -x;
		if(bib.b) _y = -y;
		return { x, y };
	}

	const std::string str() const {
		return 
			std::string("(")
			+ std::to_string(this->x) + ","
			+ std::to_string(this->y) + ")";
	}

	inline bool operator<(vector2d& vec) { return (this->x < vec.x) && (this->y < vec.y); }

	vector2d& operator=(const vector2d& vec) = default; 
	vector2d operator*(const T& rhs) { return vector2d(this->x * rhs, this->y * rhs); }
	vector2d operator+(const T& rhs) { return vector2d(this->x + rhs, this->y + rhs); }
	vector2d& operator*=(const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
	vector2d operator+(const vector2d& vec) { return vector2d(this->x + vec.x, this->y + vec.y); }
	vector2d operator-(const vector2d& vec) { return vector2d(this->x - vec.x, this->y - vec.y); }
	vector2d operator*(const vector2d& vec) { return vector2d(this->x * vec.x, this->y * vec.y); }
	inline bool operator==(const vector2d& vec) const { return (this->x == vec.x && this->y == vec.y); }
	inline bool operator!=(const vector2d& vec) const { return (this->x != vec.x || this->y != vec.y); }
};
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

