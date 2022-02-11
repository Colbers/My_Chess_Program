#include "board.h"

Board::Board() : Board(8, 8) {}

Board::Board(position2d_t& vec) : Board(vec.x, vec.y) {}

Board::Board(pos_t size_w=8, pos_t size_h=8) :
	size{ size_w, size_h }, cell_size{ CELL_WIDTH, CELL_HEIGHT } {
	for (auto i{ 0 }; i < (size_w * size_h); ++i) {
		b_space.push_back(Cell());
	}
}

Cell* Board::position(const pos_t& pos_x, const pos_t& pos_y) {
	return &b_space[pos_y * size.x + pos_x];
}

Cell* Board::position(const position2d_t& pos) {
	return position(pos.x, pos.y);
}

//Cell* Board::position(const char file, const char rank) {
//	return position(file, rank);
//}