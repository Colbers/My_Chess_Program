#include "Piece.h"

static pos_t s_x{ 0 };
static pos_t s_y{ 0 };


Piece::Piece(Team _team = Team::null,
			 Type _type = Type::null,
		 const pos_t& x = s_x,
		 const pos_t& y = s_y) :
				p_team{ _team },
				p_type{ _type },
				atPos{ x, y },
				pos{ atPos }
{}

Piece::Piece(Type type, const pos_t& x, const pos_t& y) :
	Piece(Team::null, type, x, y) 
{}

Piece::Piece(Team team, Type type,
	const position2d_t& pos = { s_x, s_y }) :
	Piece(team, type, pos.x, pos.y) 
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

bool king_canMove(const position2d_t& atPos, const position2d_t& toPos) {
	return (difference(atPos, toPos) == position2d_t(1, 1))
		|| (difference(atPos, toPos) == position2d_t(0, 1))
		|| (difference(atPos, toPos) == position2d_t(1, 0));
}
bool queen_canMove(const position2d_t& atPos, const position2d_t& toPos) {
	return true;
}
