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
    
    void constexpr create_pieces();
    void constexpr assimilate_pieces(const Board&);
	std::vector<std::shared_ptr<Piece>> pl_pieces;
	std::vector<Piece*> pl_captured;
};

#endif // !PLAYER_H
