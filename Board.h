#ifndef BOARD_H
#define BOARD_H

#include "includes.h"
#include "vector.h"

const uint8_t CELL_WIDTH{ 16 };
const uint8_t CELL_HEIGHT{ 16 };

class Piece;

struct Cell {
	Cell() = default;
	std::shared_ptr<Piece> piece{};
	bool isEmpty() const { return !piece; }
	bool notEmpty() const { return !isEmpty(); }
	void nowHolds(std::shared_ptr<Piece>& _piece) { piece = std::move(_piece); }
	void release() { piece = nullptr; }
};

struct Board {
	Board();
	Board(position2d_t& vec);
	Board(pos_t size_w, pos_t size_h);

	Cell* cell_position(const pos_t&, const pos_t&);
	Cell* cell_position(const char file, const char rank);
	Cell* cell_position(const position2d_t&);
	Cell* cell_position(const Piece*);
    
    std::shared_ptr<Piece>& get_sharedPiece(const Piece* piece){
        return cell_position(piece)->piece;
    }

	const position2d_t size;
	const position2d_t cell_size;
	std::vector<Cell> b_space;
};

#endif
