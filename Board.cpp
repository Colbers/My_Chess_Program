#include "Board.h"

Board::Board() : Board(8, 8) {}

Board::Board(position2d_t& vec) : Board(vec.x, vec.y) {}

Board::Board(pos_t size_w, pos_t size_h) :
	size{ size_w, size_h }, cell_size{ CELL_WIDTH, CELL_HEIGHT } {
	for (auto i{ 0 }; i < (size_w * size_h); ++i) {
		b_space.push_back(Cell());
	}
}
