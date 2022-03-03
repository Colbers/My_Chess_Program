#ifndef BOARD_H
#define BOARD_H

#include "includes.h"

class Piece;
using piece_ptr = std::shared_ptr<Piece>;

struct Cell {
	Cell() = default;
	piece_ptr piece{ nullptr };
	bool isEmpty() const { return piece == nullptr; }
	bool notEmpty() const { return !isEmpty(); }
	void nowHolds(piece_ptr& _piece) { piece = std::move(_piece); }
	void release() { piece.reset(); }
};

struct Board {
	Board();
	Board(vector2d<int> const& vec);
	Board(int size_w, int size_h);

    
    constexpr Cell const& cell_position(pos_t const& x, pos_t const& y) const {
        return b_space[y * size.x + x];
    }
    constexpr Cell const& cell_position(pos2d_t const& pos) const {
        return cell_position(pos.x, pos.y);
    }
   
    constexpr Cell& get_cell_at(pos_t const&x, pos_t const& y){
        return b_space[y * size.x + x];
    }
    constexpr Cell& get_cell_at(pos2d_t const& pos) {
        return get_cell_at(pos.x, pos.y);
    }
    
    constexpr piece_ptr& get_sharedPiece(pos2d_t const& pos) {
        return get_cell_at(pos).piece;
    }

	const vector2d<int> size;
    int const& width{ size.x };
    int const& height{ size.y };
	std::vector<Cell> b_space;
};

#endif
