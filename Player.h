#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "Piece.h"


class Player {
public:
	Player(Team t);
	Team pl_team{ Team::null };
    Piece* crux{ nullptr };
    
    void create_pieces();
	std::vector<piece_ptr> pl_pieces;
	std::vector<Piece*> pl_captured;
};

#endif // !PLAYER_H
