#ifndef PIECE_H
#define PIECE_H

#include "includes.h"
#include "vector.h"
#include "Direction.h"

inline pos_t file(position2d_t const& pPos) { return pPos.x; }
inline pos_t rank(position2d_t const& pPos) { return pPos.y; }

enum class Team { null = 0, white = 1, black = 2 };
enum class Type { null = 0, king, queen, bishop, knight, rook, pawn };

class Piece {
public:
	Piece() = default;
    Piece(Team, pos_t const& x, pos_t const& y);
	Piece(pos_t const& x, pos_t const& y);
	Piece(position2d_t const&);

    /*
     Dev Philosophy:
        I decided that Pieces should generally be aware
        of how they may technically move, the idea
        being that validaters query the piece to move
     */
    
            /* various checks */
    
	bool initial_position() const { return initPos; }
    virtual bool canMove(position2d_t const& position);
    virtual bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }

    position2d_t& get_pos() { return atPos; }
    void set_team(Team t) { p_team = t; }
    void set_direction(cardinal dir) { facing = dir; }
    void has_moved() { initPos = false; }

            /* const references */
    position2d_t const& pos{ atPos };
    Type const& type{ p_type };
	Team const& team{ p_team };
        
            /* the innate properties of a Piece */
protected:
	position2d_t atPos{};
	Direction facing{ cardinal::null };
	Team p_team{ Team::null };
	Type p_type{ Type::null };
	bool initPos{ true };
};

 // simple utility function to (loudly)
// grab the position of a piece
inline position2d_t const& position_of(Piece* piece) { return piece->pos; }

        /* each Piece type is its own class */
class King : public Piece {
public:
	King(pos_t const& pos_x, pos_t const& pos_y) :
        Piece(pos_x, pos_y) { p_type = Type::king; }

	King(position2d_t const& pos) :
        King(pos.x, pos.y) {}
    
    King() { p_type = Type::king; }

	bool canMove(position2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Queen : public Piece {
public:
	Queen(pos_t const& pos_x, pos_t const& pos_y) :
        Piece(pos_x, pos_y) { p_type = Type::queen; }

	Queen(position2d_t const& pos) :
		Queen(pos.x, pos.y) {}
    
    Queen() { p_type = Type::queen; }

	bool canMove(position2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Bishop : public Piece {
public:
	Bishop(pos_t const& pos_x, pos_t const& pos_y) :
        Piece(pos_x, pos_y) { p_type = Type::bishop; }

	Bishop(position2d_t const& pos) :
		Bishop(pos.x, pos.y) {}
    
    Bishop() { p_type = Type::bishop; }

	bool canMove(position2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Knight : public Piece {
public:
	Knight(pos_t const& pos_x, pos_t const& pos_y) :
        Piece(pos_x, pos_y) { p_type = Type::knight; }

	Knight(position2d_t const& pos) :
		Knight(pos.x, pos.y) {}
    
    Knight() { p_type = Type::knight; }

	bool canMove(position2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Rook : public Piece {
public:
	Rook(pos_t const& pos_x, pos_t const& pos_y) :
        Piece(pos_x, pos_y) { p_type = Type::rook; }

	Rook(position2d_t const& pos) :
		Rook(pos.x, pos.y) {}
    
    Rook() { p_type = Type::rook; }
	
	bool canMove(position2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Pawn : public Piece {
public:
	Pawn(pos_t const& pos_x, pos_t const& pos_y) :
        Piece(pos_x, pos_y) { p_type = Type::pawn; }

	Pawn(position2d_t const& pos) :
		Pawn(pos.x, pos.y) {}
    
    Pawn() { p_type = Type::pawn; }

	bool canMove(position2d_t const&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Player;

namespace alt {
class King {
public:
    King(pos_t const& x, pos_t const& y) :
        pos{ x, y } {}
    
    position2d_t pos;
    Type type{ Type::king };
    bool canMove(pos_t const& x, pos_t const& y);
};

}

#endif
