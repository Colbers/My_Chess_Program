#include "Move_Logic.h"

Cell* Board::cell_position(const Piece* piece) {
	return cell_position(piece->pos);
}

      // this function iterates from a starting point,
     // returning one of these options:
    //
   // a cell at the specified location
  // a cell at the edge of board
 // a cell holding first piece found during iteration
//
Cell* iter_thru_cell(Board* board, Trajectory traj){

	auto current{ traj.origin };
	auto direction{ traj.direction };

	bool arrive, occupied;

	while (current < board->size) {

		current = proceed(current, direction);

		arrive = current == traj.toward;
		occupied = board->cell_position(current)->notEmpty();

		if (arrive || occupied) break;
	}

	return board->cell_position(current);
}

Cell* iter_thru_cell(Motion& motion) {
	return iter_thru_cell(motion.board, motion.trajectory);
}

void Move(Motion& motion) { //self-explanatory

	Cell* origin{ motion.board->cell_position(motion.piece) };
	Cell* destination{ motion.board->cell_position(motion.toward) };
    
    auto motion_piece{ motion.board->get_sharedPiece(motion.piece)};

	if (destination->isEmpty()) { //only move there if vacant space,

		origin->release(); //piece has left home
		destination->nowHolds(motion_piece);  //piece found new home
		motion.piece->get_pos() = motion.toward;  //update the position
	}
}

Suppose::Suppose(Motion& _motion) : // hypothetical move
	ogPos{ position_of(_motion.piece) }, // remember where we start
	motion{ _motion } // motion in question
{
	Cell* target_cell = { motion.board->cell_position(motion.trajectory.toward) };

	if (target_cell->notEmpty()
		&& (target_cell->piece->team != motion.piece->team)) {

		obstacle = { motion.board,
                     target_cell->piece.get(),
                     position_of(target_cell->piece.get()) };

		target_cell->release();
		Move(motion);
	}
	else if (target_cell->isEmpty()) {
		Move(motion);
	}
}

Suppose::~Suppose() { //undo hypothetical
	if (position_of(motion.piece) != ogPos) //make sure we only move piece back if it ain't back
		Move(motion);

	if (obstacle.piece)  //if we moved an obstacle, put it back!
		Move(obstacle);
}

bool check_safe(Motion& motion, Piece* crux) {
    
    /* lambdas for sake of readability */
					
	auto position = [&motion](const position2d_t& pos) {
		return motion.board->cell_position(pos);
	};

	auto proceed = [&](const position2d_t& pos, int n=1) {
		return ::proceed(pos, motion.trajectory.direction, n);
	};

	auto check = [&](int _dir) { 
		return iter_thru_cell(motion.board, { crux->pos, cardinal(_dir) });
	};

	auto danger_piece = [&crux](Cell* cell) {
          // if piece can move to king's position
         // AND piece is not same team,
        // piece is evil and danger
        
		return (cell->piece->team != crux->team)
             && cell->piece->canMove(crux->pos);
         // check team first; we dont care if teammates
        // can fill the king's spot, early judgement
	};

	auto sneaky_knight = [&]() {
		for (auto c{ 1 }; c <= 4; c++) { // 1234 == NESW

			// if north or south, proceed twice, then check east and west directions
			// if east or west, proceed twice, then check north and south directions

			switch (cardinal(c)) {

			case cardinal::north: // clever fallthrough to
                                 // check east and west of vertical
			case cardinal::south: {
				position2d_t vertical{ proceed(crux->pos, 2) };

				if (danger_piece(position(East(vertical)))
					|| danger_piece(position(West(vertical))))

					return true; // bad knight
			} break;

			case cardinal::east: // more falling to
                                // check north and south of horizontal
			case cardinal::west: {
				position2d_t horizontal{ proceed(crux->pos, 2) };

				if (danger_piece(position(North(horizontal)))
					|| danger_piece(position(South(horizontal))))

					return true; // no, bad knight attack king
			} break;

			default:
				break;
			}
		}
        
        // no sneaky knight
		return false;
    };

	Suppose hypothetical{ motion }; //indeed, quite the supposition
    /*
        Functional Appreciation:
         when we "suppose hypothetical motion",
         we're essentially pretending as if the move
         has been made, only then may we check
         an accurate board
     
         when our hypothetical motion falls out of scope,
         the user-defined destructor makes sure to put
         everything back, effectively undoing our
         hypothetical supposition
     */

	// anyways, carry on with the checks!

    for (int dir{0}; dir < 8; ++dir)  {
        
        // eight directions to check: N E S W + NE NW SE SW
		
        if (danger_piece(check(dir)) || sneaky_knight())
			// bad piece found, move is not safe
            return false;
	}
    
    // no bad piece found; ideally, move is safe
	return true;
}

bool Legal_Move(Motion& motion, Piece* crux) {

    // check 'toward' is in bounds of the board
	if (!(motion.toward <= motion.board->size)

    // check that 'piece' may reach 'toward'
	  || !motion.piece->canMove(motion.toward)

    // check if move is safe
	  || !check_safe(motion, crux))
			return false;

	Cell* target_cell { motion.board->cell_position(motion.toward) };
	Piece* found_piece { target_cell->piece.get() };

	bool friendly { // if we found a piece, check allegiance;
                   // otherwise, an empty cell is a friendly cell
		found_piece ? found_piece->team == motion.piece->team : true
	};

	if (motion.piece->type == Type::knight) { //knight doesn't care about inbetween cells
		return !found_piece || !friendly;	 //knight just jump
	}
	else {
		Cell* destination = { iter_thru_cell(motion) };

		found_piece = destination->piece.get();

		friendly = found_piece ? (found_piece->team == motion.piece->team) : true;

		if (destination->isEmpty())	// iter_thru_cell() found the path empty
			return target_cell == destination;  // a sanity check
		else 
			if (found_piece && 
				found_piece->pos == motion.toward)
				return !friendly;  // the found piece can be reached and is very bad
	}

	return false;  // if toPos has friendly piece,
				  // it should fall through loops
				 // we dont capture friends
}
