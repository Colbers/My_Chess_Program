#include "Move_Logic.h"

Cell* Board::position(const Piece* piece) {
	return position(piece->origin());
}

void Board::put(Piece* piece) {
	if (position(piece)->isEmpty())
	position(piece)->nowHolds(piece);
}

Cell* iter_thru_cell(Board* board, Trajectory traj){

	auto current{ traj.origin };
	auto direction{ traj.direction };

	bool arrive, occupied;

	while (current < board->size) {

		current = proceed(current, direction);

		arrive = current == traj.toward;
		occupied = board->position(current)->notEmpty();

		if (arrive || occupied) break;
	}

	return board->position(current);
}

Cell* iter_thru_cell(Motion& motion) {
	return iter_thru_cell(motion.board, motion.trajectory);
}

void Move(Motion& motion) { //self-explanatory

	Cell* origin{ motion.board->position(motion.piece) };
	Cell* destination{ motion.board->position(motion.toward) };

	if (destination->isEmpty()) { //only move there if vacant space,

		origin->release(); //piece has left home
		destination->nowHolds(motion.piece);  //piece found new home
		motion.piece->get_pos() = motion.toward;  //update the position
	}
}

Suppose::Suppose(Motion& _motion) ://hypothetical move
	ogPos{ position(_motion.piece) }, //remember where we start
	motion{ _motion }
{
	Cell* cell = { motion.board->position(motion.trajectory.toward) };

	if (cell->notEmpty()
		&& (cell->piece->team != motion.piece->team)) {

		obstacle = { motion.board, cell->piece, position(cell->piece) };

		cell->release();
		Move(motion);
	}
	else if (cell->isEmpty()) {
		Move(motion);
	}
}

Suppose::~Suppose() { //undo hypothetical
	if (position(motion.piece) != ogPos) //make sure we only move piece back if it ain't back
		Move(motion);

	if (obstacle.piece)  //if we moved an obstacle, put it back!
		Move(obstacle);
}

bool check_safe(Motion& motion, Piece* crux) {
					
	auto position = [&motion](const position2d_t& pos) {
		return motion.board->position(pos);
	};

	auto proceed = [&](const position2d_t& pos, int n=1) {
		return ::proceed(pos, motion.trajectory.direction, n);
	};

	auto check = [&](int _dir) { 
		return iter_thru_cell(motion.board, { crux->pos, cardinal(_dir) });
	};

	auto danger_piece = [&crux](Cell* cell) { 
		return (cell->piece->team != crux->team)
			&& cell->piece->canMove(crux->pos);
	};

	auto sneaky_knight = [&]() {
		for (auto c{ 1 }; c <= 4; c++) { // 1234 == NESW

			//if north or south, proceed twice, then check east and west directions
			//if east or west, proceed twice, then check north and south directions

			switch (cardinal(c)) {

			case cardinal::north:
			case cardinal::south: {
				position2d_t vertical{ proceed(crux->pos, 2) };

				if (danger_piece(position(East(vertical)))
					|| danger_piece(position(West(vertical))))

					return true;
			} break;

			case cardinal::east:
			case cardinal::west: {
				position2d_t horizontal{ proceed(crux->pos, 2) };

				if (danger_piece(position(North(horizontal)))
					|| danger_piece(position(South(horizontal))))

					return true;
			} break;

			default:
				break;
			}
		}
		return false; //no sneaky knight
	};

	Suppose hypothetical{ motion }; //indeed, quite the supposition

	//anyways, carry on with the checks!

	int O_dir[]{ 1,2,3,4,5,6,7,8 }; //direction 1: north

	for (auto dir : O_dir)  { //eight directions to check: N E S W + NE NW SE SW

		if (danger_piece(check(dir)) || sneaky_knight()) {			
			return false;	//bad piece found, move is not safe
		}
	}
	return true;	//no bad piece found, (hopefully) move is safe
}

bool Legal_Move(Motion& motion, Piece* crux) {

	if (!(motion.toward <= motion.board->size)  //check 'toward' is in bounds of the board

	  || !motion.piece->canMove(motion.toward)  //check that 'piece' may reach 'toward'

	  || !check_safe(motion, crux))  //check if move is safe

			return false;

	Cell* target_cell { motion.board->position(motion.toward) };
	Piece* found_piece { target_cell->piece };

	bool friendly {
		found_piece ? found_piece->team == motion.piece->team : true
	};

	if (motion.piece->type == Type::knight) {    //knight doesn't care about inbetween cells
		return !found_piece || !friendly;		//knight just jump
	}
	else {
		Cell* destination = { iter_thru_cell(motion) };

		found_piece = destination->piece;

		friendly = found_piece ? (found_piece->team == motion.piece->team) : true;

		if (destination->isEmpty())	//iter_thru_cell() found the path empty
			return target_cell == destination;  //a sanity check
		else 
			if (found_piece && 
				found_piece->pos == motion.toward)
				return !friendly;  //the found piece can be reached and is very bad
	}

	return false;  //if toPos has friendly piece,
				  //it should fall through loops
				 //we dont capture friends
}