#include "Piece.h"

Piece::Piece(Type type) : p_type{type}
{}

Piece::Piece(Type type,
             const pos_t& x,
             const pos_t& y) :
    p_type{type},
    atPos{x,y}
{}

Piece::Piece(Type type,
	const position2d_t& pos) :
	Piece(type, pos.x, pos.y)
{}

bool Piece::canMove(const position2d_t& position) {
	return true;
}

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
}

bool Knight::canMove(const position2d_t& toPos) {
	return (difference(atPos, toPos) == position2d_t(1, 2))
		|| (difference(atPos, toPos) == position2d_t(2, 1));
}

bool Rook::canMove(const position2d_t& toPos) {
	return (file(atPos) == file(toPos)) 
		|| (rank(atPos) == rank(toPos));
}

bool Pawn::canMove(const position2d_t& toPos) {

	auto forward = [&](int n=1) {
		return toPos == proceed(atPos, facing, n);
	};

	if (initial_position())
		return (forward() || forward(2));
	else 
		return forward();
}
