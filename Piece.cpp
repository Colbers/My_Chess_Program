#include "Piece.h"

  // various ways to construct a Piece
 //
//      duh...

Piece::Piece(pos_t const& x, pos_t const& y) :
    atPos{x,y} {} // our main Piece constructor

Piece::Piece(position2d_t const& pos) :
	Piece(pos.x, pos.y) {} // delegating constructor

        /* can we move that way? */

bool Piece::canMove(position2d_t const& position) {
    // Pieces can generally move.
	return true;
}

/*
    syntax: (difference(at, to) == position2d_t(x, y))
     refers to the change in the X and Y axis,
     where the X and Y values are the amount
     of cells from origin to destination.
                                                        */

bool King::canMove(position2d_t const& toPos) {
	return (difference(atPos, toPos) == position2d_t(1, 1))
		|| (difference(atPos, toPos) == position2d_t(0, 1))
		|| (difference(atPos, toPos) == position2d_t(1, 0));
}

bool Queen::canMove(position2d_t const& toPos) {
	return (Rook(atPos).canMove(toPos))
		|| (Bishop(atPos).canMove(toPos));
}

bool Bishop::canMove(position2d_t const& toPos) {
	return difference(atPos, toPos).equalized();
} // equalized() means X == Y;

bool Knight::canMove(position2d_t const& toPos) {
	return (difference(atPos, toPos) == position2d_t(1, 2))
		|| (difference(atPos, toPos) == position2d_t(2, 1));
}

bool Rook::canMove(position2d_t const& toPos) {
	return (file(atPos) == file(toPos)) 
		|| (rank(atPos) == rank(toPos));
}

bool Pawn::canMove(position2d_t const& toPos) {

	auto forward = [&](int n=1) { // compare that our toPos
                                 // is 'forward' N cells
                                // from our atPos
		return toPos == proceed(atPos, facing, n);
	};

	if (initial_position()) // if we at our initial position,
                           // we may choose to double jump
		return (forward() || forward(2));
	else 
		return forward();
}
