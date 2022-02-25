#include "Piece.h"

  // various ways to construct a Piece
 //
//      duh...

Piece::Piece(Type type) : p_type{type}
{} // generic piece with only its type recorded

Piece::Piece(Type type,
             const pos_t& x,
             const pos_t& y) :
    p_type{type},
    atPos{x,y}
{} // our main Piece constructor

Piece::Piece(Type type,
	const position2d_t& pos) :
	Piece(type, pos.x, pos.y)
{} // delegating constructor

bool Piece::canMove(const position2d_t& position) {
    // Pieces can generally move.
	return true;
}

/*
    syntax: (difference(at, to) == position2d_t(x, y))
     refers to the change in the X and Y axis,
     where the X and Y values of position2d_t(x, y) are
     the amount of cells from origin to destination.
                                                           */

bool King::canMove(const position2d_t& toPos) {
	return (difference(atPos, toPos) == position2d_t(1, 1))
		|| (difference(atPos, toPos) == position2d_t(0, 1))
		|| (difference(atPos, toPos) == position2d_t(1, 0));
}

bool Queen::canMove(const position2d_t& toPos) {	
	return (Rook(atPos).canMove(toPos))
		|| (Bishop(atPos).canMove(toPos));
}

bool Bishop::canMove(const position2d_t& toPos) {
	return difference(atPos, toPos).equalized();
} // equalized() means X == Y;

bool Knight::canMove(const position2d_t& toPos) {
	return (difference(atPos, toPos) == position2d_t(1, 2))
		|| (difference(atPos, toPos) == position2d_t(2, 1));
}

bool Rook::canMove(const position2d_t& toPos) {
	return (file(atPos) == file(toPos)) 
		|| (rank(atPos) == rank(toPos));
}

bool Pawn::canMove(const position2d_t& toPos) {

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
