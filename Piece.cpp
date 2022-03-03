#include "Piece.h"

  // various ways to construct a Piece
 //
//      duh...

Piece::Piece(pos_t const& x, pos_t const& y) :
    atPos{x,y} {} // our main Piece constructor

Piece::Piece(pos2d_t const& pos) :
	Piece(pos.x, pos.y) {} // delegating constructor

        /* can we move that way? */

bool Piece::canMove(pos2d_t const& position) {
    // generic pieces are not chess pieces, so they have no move rules
	return false;
}

/*
    syntax: (difference(at, to) == pos2d_t(x, y))
     refers to the change in the X and Y axis,
     where the X and Y values are the amount
     of cells from origin to destination.
                                                        */

bool King::canMove(pos2d_t const& toPos) {
	return (difference(atPos, toPos) <= pos2d_t(1, 1));
}

bool Queen::canMove(pos2d_t const& toPos) {
	return (Rook(atPos).canMove(toPos))
		|| (Bishop(atPos).canMove(toPos));
}

bool Bishop::canMove(pos2d_t const& toPos) {
	return difference(atPos, toPos).equalized();
} // equalized() means X == Y;

bool Knight::canMove(pos2d_t const& toPos) {
	return (difference(atPos, toPos) == pos2d_t(1, 2))
		|| (difference(atPos, toPos) == pos2d_t(2, 1));
}

bool Rook::canMove(pos2d_t const& toPos) {
	return (file(atPos) == file(toPos)) 
		|| (rank(atPos) == rank(toPos));
}

bool Pawn::canMove(pos2d_t const& toPos) {

	auto forward = [&](int n=1) { // compare that our toPos
                                 // is 'forward' N cells
                                // from our atPos
		return toPos == proceed(atPos, facing, n);
	};

	if (initial_position()) // if initial position,
                           // we may double jump
		return (forward() || forward(2));
	else 
		return forward();
}
