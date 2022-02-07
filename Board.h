#ifndef BOARD_H
#define BOARD_H

#include "includes.h"
#include "vector.h"

const uint8_t CELL_WIDTH{ 16 };
const uint8_t CELL_HEIGHT{ 16 };

class Piece;

struct Cell {
	Cell() = default;
	Piece* piece{ nullptr };
	bool isEmpty() const { return !piece; }
	bool notEmpty() const { return piece; }
	void nowHolds(Piece* _piece) { piece = _piece; }
	void release() { piece = nullptr; }
};

struct Board {
	Board();
	Board(position2d_t& vec);
	Board(pos_t size_w, pos_t size_h);

	void put(Piece*);

	Cell* position(const pos_t&, const pos_t&);
	Cell* position(const char file, const char rank);
	Cell* position(const position2d_t&);
	Cell* position(const Piece*);

	const position2d_t size;
	const position2d_t cell_size;
	std::vector<Cell> b_space;
};

#endif
