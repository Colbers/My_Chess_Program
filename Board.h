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
	constexpr void release() { piece.reset(); }
};

struct Board {
	Board();
	Board(position2d_t& vec);
	Board(pos_t size_w, pos_t size_h);

    
    constexpr Cell const& cell_position(pos_t const& x, pos_t const& y) const {
        return b_space[y * size.x + x];
    }
    constexpr Cell const& cell_position(position2d_t const& pos) const {
        return cell_position(pos.x, pos.y);
    }
   
    constexpr Cell& get_cell_at(pos_t const&x, pos_t const& y){
        return b_space[y * size.x + x];
    }
    constexpr Cell& get_cell_at(position2d_t const& pos) {
        return get_cell_at(pos.x, pos.y);
    }
    
    constexpr std::shared_ptr<Piece>& get_sharedPiece(position2d_t const& pos) {
        return get_cell_at(pos).piece;
    }

	const position2d_t size;
	const position2d_t cell_size;
	std::vector<Cell> b_space;
};

#endif
