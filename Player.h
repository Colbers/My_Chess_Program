#ifndef PLAYER_H
#define PLAYER_H

#include "Piece.h"

struct Board;

static int p_id{ 0x0 };

class Player {
public:
	Player() = default;
	Player(Team t) : pl_team{ t } {}
		
	Team pl_team{ Team::null };
	Piece* crux{ nullptr };
	piece_container pl_piece;
	piece_container pl_captured;
};

#endif // !PLAYER_H
