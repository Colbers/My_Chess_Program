#ifndef DIRECTION_H
#define DIRECTION_H

#include "includes.h"
#include "vector.h"

template <typename T>
vector2d<T> North(vector2d<T> vec, int32_t N=1) { 
	return vector2d<T>(vec.x, vec.y + N);
}

template <typename T>
vector2d<T> South(vector2d<T> vec, int32_t N=1) {
	return vector2d<T>(vec.x, vec.y - N);
}

template <typename T>
vector2d<T> East(vector2d<T> vec, int32_t N=1) {
	return vector2d<T>(vec.x + N, vec.y);
}

template <typename T>
vector2d<T> West(vector2d<T> vec, int32_t N=1) {
	return vector2d<T>(vec.x - N, vec.y);
}

enum class cardinal {
	null = 0,
	north, east, south, west,
	northeast, northwest,
	southeast, southwest  
};

struct Direction {

	cardinal facing{cardinal::null};

	Direction() = default;
	Direction(cardinal face) : facing{ face } {}

	inline operator bool() const { return !(facing == cardinal::null); }
};

template <typename T>
Direction create_direction(const vector2d<T>& og, const vector2d<T>& to) {

	cardinal face{};

	int32_t X{ (int32_t) to.x - og.x };
	int32_t Y{ (int32_t) to.y - og.y };

	if (!X && !Y) face = cardinal::null;

	else if (X == 0)
		face = (Y > 0) ? cardinal::north : cardinal::south;

	else if (Y == 0)
		face = (X > 0) ? cardinal::east : cardinal::west;

	else if (X > 0)
		face = (Y > 0) ? cardinal::northeast : cardinal::southeast;

	else if (X < 0)
		face = (Y > 0) ? cardinal::northwest : cardinal::southwest;

	return face;
}

template <typename T>
vector2d<T> proceed(vector2d<T> pos, Direction dir, uint32_t n = 1) {
	switch (dir.facing) {
	case cardinal::north:
		return North(pos, n);
		break;

	case cardinal::south:
		return South(pos, n);
		break;

	case cardinal::east:
		return East(pos, n);
		break;

	case cardinal::west:
		return West(pos, n);
		break;

	case cardinal::northeast:
		return North(East(pos, n), n);
		break;

	case cardinal::northwest:
		return North(West(pos, n), n);
		break;

	case cardinal::southeast:
		return South(East(pos, n), n);
		break;

	case cardinal::southwest:
		return South(West(pos, n), n);
		break;

	default:
		return pos;
	}
}

#endif
