#ifndef MOVE_LOGIC_H
#define MOVE_LOGIC_H

#include "includes.h"
#include "Board.h"
#include "Piece.h"

struct Trajectory {
	Trajectory() = default;

	Trajectory(pos2d_t _origin, pos2d_t _toward) :
		origin{ _origin },
		toward{ _toward }, 
		direction{
			create_direction(_origin, _toward)
		} 
	{}

	Trajectory(pos2d_t _origin, direction _direction = cardinal::null) :
		origin{ _origin }, 
		direction { _direction } {}

	pos2d_t origin{};
	pos2d_t toward{};
	direction direction{};
};

struct Motion {
	Motion() = default;

	Motion(Board* _board, Piece* _piece) :
		board{ _board },
		piece{ _piece }
	{}

	Motion(Board* _board, Piece* _piece, pos2d_t const& _pos) :
		board{ _board },
		piece { _piece },
		trajectory{ _piece->pos, _pos }
	{}

	Motion(Board* _board, pos2d_t const& og_pos, pos2d_t const& to_pos) :
		board{ _board },
		piece{ _board->cell_position(og_pos).piece.get() },
		trajectory{ og_pos, to_pos }
	{}

	Motion(Motion const& _m) :
		board{ _m.board },
		piece{ _m.piece },
		trajectory{ _m.trajectory }
	{}

	Board* board{ nullptr };
	Piece* piece{ nullptr };
	Trajectory trajectory{};

    pos2d_t const& origin{ trajectory.origin };
	pos2d_t const& toward{ trajectory.toward };
	direction const& direction{ trajectory.direction };

	void update_to(pos2d_t const& pos) {
		trajectory.toward = pos;
	}

	void operator=(Motion const& motion) {
		this->board = motion.board;
		this->piece = motion.piece;
		this->trajectory = motion.trajectory;
	}
};

struct Suppose {
	Suppose(Motion const&);
	~Suppose();
	pos2d_t ogPos;
	Motion motion;
	Motion obstacle;
};

void Move(Motion&);
void Put(Motion&);

bool check_safe(Motion const&, Piece* crux);
//iterate through each direction, checking that 'crux' is safe

bool Legal_Move(Motion const&, Piece* crux);
 //crux is the piece that determines fate of the game
//traditionally, for chess, that is the king

#endif
