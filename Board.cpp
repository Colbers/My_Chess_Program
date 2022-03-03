#include "Board.h"

Board::Board() : Board(8, 8) {}

Board::Board(vector2d<int> const& vec) : Board(vec.x, vec.y) {}

Board::Board(int size_w, int size_h) :
	size{ size_w, size_h } {
	for (auto i{ 0 }; i < (size_w * size_h); ++i) {
		b_space.emplace_back(Cell());
	}
}
