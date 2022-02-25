#include "Board.h"

Board::Board() : Board(8, 8) {}

Board::Board(position2d_t& vec) : Board(vec.x, vec.y) {}

Board::Board(pos_t size_w, pos_t size_h) :
	size{ size_w, size_h }, cell_size{ CELL_WIDTH, CELL_HEIGHT } {
	for (auto i{ 0 }; i < (size_w * size_h); ++i) {
		b_space.push_back(Cell());
	}
}

Cell* Board::cell_position(const pos_t& pos_x, const pos_t& pos_y) {
	return &b_space[pos_y * size.x + pos_x];
}

Cell* Board::cell_position(const position2d_t& pos) {
	return cell_position(pos.x, pos.y);
}
