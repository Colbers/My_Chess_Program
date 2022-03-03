#include "Move_Logic.h"

      // this function iterates from a starting point,
     // returning one of these options:
    //
   // a cell at the specified location
  // a cell at the edge of board
 // a cell holding first piece found during iteration
//
Cell& iter_thru_cell(Board* board, Trajectory traj) {

	auto current{ traj.origin };
	auto direction{ traj.direction };

	bool arrive, occupied;

	while (current < board->size) {

		current = proceed(current, direction);

		arrive = (current == traj.toward);
		occupied = board->cell_position(current).notEmpty();

		if (arrive || occupied) break;
	}

	return board->get_cell_at(current);
}

Cell const& iter_thru_cell(Motion const& motion) {
	return iter_thru_cell(motion.board, motion.trajectory);
}

        /* The fabled Move function */

void Move(Motion& motion) { //self-explanatory

    // where we start
	auto& origin{ motion.board->get_cell_at(motion.piece->pos) };
	// where we go
    auto& destination{ motion.board->get_cell_at(motion.toward) };
    
       // we require a reference to the shared_ptr object
      // to simplify memory relocation
     // using the std::move()
    // called by Cell::nowHolds(Piece*)
    auto motion_piece{ motion.board->get_sharedPiece(motion.piece->pos)};

	if (destination.isEmpty()) { // only move there if vacant space,

		origin.release();
		destination.nowHolds(motion_piece);  // piece found new home
		motion.piece->get_pos() = motion.toward;  // update the position

	}
}

Suppose::Suppose(Motion const& _motion) : // hypothetical move
	ogPos{ position_of(_motion.piece) }, // remember where we start
	motion{ _motion } // motion in question
{
	Cell& target_cell = { motion.board->get_cell_at(motion.toward) };

	if (target_cell.notEmpty() // if we found a bad(capturable) piece
		&& (target_cell.piece->team != motion.piece->team)) {

		 // store the location
		// & prepare to move after hypothetical
		obstacle = {
			motion.board,
			target_cell.piece.get(),
			position_of(target_cell.piece.get())
		};

		target_cell.release();
		Move(motion);
		motion.update_to(ogPos);
	}
	else if (target_cell.isEmpty()) {
		Move(motion);
		motion.update_to(ogPos);
	}
}

Suppose::~Suppose() { // undo hypothetical
	if (position_of(motion.piece) != ogPos) // make sure we only move piece back if it ain't back
		Move(motion);

	if (obstacle.piece)  //if we moved an obstacle, put it back!
		Move(obstacle);
}

bool check_safe(Motion const& motion, Piece* crux) {
    
    /* lambdas for sake of readability */
					
	auto position = [&motion](pos2d_t const& pos) {
		return motion.board->cell_position(pos);
	};

	auto proceed = [&](pos2d_t const& pos, int n=1) {
		return ::proceed(pos, motion.trajectory.direction, n);
	};

	auto check = [&](int _dir) {
		return iter_thru_cell(motion.board, { crux->pos, cardinal(_dir) });
	};

	auto danger_piece = [&crux](Cell const& cell) {
          // if piece can move to king's position
         // AND piece is not same team,
        // piece is evil and danger
        
		return (cell.piece->team != crux->team)
             && cell.piece->canMove(crux->pos);

         // check team first; we dont care if teammates
        // can fill the king's spot, early judgement
	};

	auto sneaky_knight = [&]() {
		for (auto c{ 1 }; c < 5; c++) { // 1234 == NESW

			// if north or south, proceed twice, then check east and west directions
			// if east or west, proceed twice, then check north and south directions

			switch (cardinal(c)) {

			case cardinal::north: // clever fallthrough to
                                 // check east and west of vertical
			case cardinal::south: {
				pos2d_t vertical{ proceed(crux->pos, 2) };

				if (danger_piece(position(East(vertical)))
				 || danger_piece(position(West(vertical))))

					return true; // bad knight
			} break;

			case cardinal::east: // more fallthrough to
                                // check north and south of horizontal
			case cardinal::west: {
				pos2d_t horizontal{ proceed(crux->pos, 2) };

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

    for (int dir{1}; dir < 9; ++dir)  {
        
        // eight directions to check: N E S W + NE NW SE SW
		
        if (danger_piece(check(dir)))
			// bad piece found, move is not safe
            return false;
	}
    
    // make sure no sneaky knight around; if not, move *should* be safe
	return !sneaky_knight();
}

bool danger_squares(Motion const& _motion) {
	// check the two squares in front of king move

	bool danger{ false };

	auto& origin{ _motion.origin };
	auto& direction{ _motion.direction };

	pos2d_t ogPos{ origin };

	Motion hypothetical{ _motion };

	auto crux{ hypothetical.piece };

	for (int i{ 0 }; i < 2; ++i) {
		hypothetical.update_to(proceed(origin, direction));
		Move(hypothetical);
		danger = { !check_safe(hypothetical, crux) };
	}
	hypothetical.update_to(ogPos);
	Move(hypothetical);

	return danger;
}

bool mayCastle(Motion const& motion){
    if ( file(motion.origin) != file(motion.toward) )
        return false;
	if (!motion.piece->initial_position())
		return false;
    
    Cell const& target_side = {
        iter_thru_cell(motion)
    };
	
	if (!target_side.piece)
		return false;

	if (!target_side.piece->initial_position())
		return false;
    
	bool rook {
		target_side.piece->type == Type::rook
    };
    
	if (rook)
		return !danger_squares(motion);

	return false;
}

bool Technical_Move(Motion const& motion){
    bool default_move{
        motion.piece->canMove(motion.toward)
    };
    
    switch (motion.piece->type){
        case Type::king:
            return mayCastle(motion)
                || default_move;
        default:
            return default_move;
    }
}

bool Legal_Move(Motion const& motion, Piece* crux) {

    // check 'toward' is in bounds of the board
	if (!(motion.toward <= motion.board->size)

    // check if our move is a special case
	  || !Technical_Move(motion)

    // check if move is safe
	  || !check_safe(motion, crux))
			return false;

	Cell const& target_cell { motion.board->cell_position(motion.toward) };
	Piece* found_piece { target_cell.piece.get() };

	bool friendly { // if we found a piece, check allegiance;
                   // otherwise, an empty cell has no friend
		found_piece ? found_piece->team == motion.piece->team : false
	};

	if (motion.piece->type == Type::knight) { //knight doesn't care about inbetween cells
		return !found_piece || !friendly;	 //knight just jump
	}
	else {
		Cell const& destination = { iter_thru_cell(motion) };

		found_piece = destination.piece.get();

		friendly = found_piece ? (found_piece->team == motion.piece->team) : false;

		if (destination.isEmpty())	// iter_thru_cell() found the path empty
			return &target_cell == &destination;  // a sanity check
		else 
			if (found_piece && 
				found_piece->pos == motion.toward)
				return !friendly;  // the found piece can be reached and is very bad
	}

	std::cout << "\nIllegal Move.\n";

	return false;  
}
