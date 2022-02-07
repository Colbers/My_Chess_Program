#ifndef MOVE_LOGIC_H
#define MOVE_LOGIC_H

#include "includes.h"
#include "vector.h"
#include "Board.h"
#include "Piece.h"
#include "Direction.h"

struct Trajectory {
	Trajectory() = default;

	Trajectory(position2d_t _origin, position2d_t _toward) :
		origin{ _origin },
		toward{ _toward }, 
		direction{
			create_direction(_origin, _toward)
		} 
	{}

	Trajectory(position2d_t _origin, direction _direction) :
		origin{ _origin }, 
		direction { _direction } {}

	position2d_t origin{};
	position2d_t toward{};
	direction direction{};
};

struct Motion {
	Motion() = default;

	Motion(Board* _board, Piece* _piece) :
		board{ _board },
		piece{ _piece }
	{}

	Motion(Board* _board, Piece* _piece, const position2d_t& _pos) :
		board{ _board },
		piece { _piece },
		trajectory{ _piece->origin(), _pos }
	{}

	Board* board{ nullptr };
	Piece* piece{ nullptr };
	Trajectory trajectory{};

	const position2d_t& toward{ trajectory.toward };

	void operator=(Motion motion) { 
		this->board = motion.board;
		this->piece = motion.piece;
		this->trajectory = motion.trajectory;
	}
};

struct Suppose {
	Suppose(Motion&);
	~Suppose();
	position2d_t ogPos;
	Motion& motion;
	Motion obstacle;
};

void Move(Motion&);
void Put(Motion&);

bool check_safe(Motion&, Piece* crux);
//iterate through each direction, checking that 'crux' is safe

bool Legal_Move(Motion&, Piece* crux);
 //crux is the piece that determines fate of the game
//traditionally, for chess, that is the king

#endif
