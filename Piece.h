#ifndef PIECE_H
#define PIECE_H

#include "includes.h"
#include "vector.h"
#include "Direction.h"

inline pos_t file(const position2d_t& pPos) { return pPos.x; }
inline pos_t rank(const position2d_t& pPos) { return pPos.y; }

enum class Team { null = 0, white = 1, black = 2 };
enum class Type { null = 0, king, queen, bishop, knight, rook, pawn };

class Piece {
public:
	Piece() = default;
    Piece(Type, Team, const pos_t& x, const pos_t& y);
	Piece(Type, const pos_t& x, const pos_t& y);
	Piece(Type, const position2d_t&);
    Piece(Type);

            /* various checks */
    /*
     Dev Philosophy:
        I decided that Pieces should generally be aware
        of how they may technically move, the idea
        being that validaters query the piece to move
     */
    
	bool initial_position() const { return initPos; }
	void has_moved() { initPos = false; }
	virtual bool canMove(const position2d_t& position);
    virtual	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }

	position2d_t& get_pos() { return atPos; }
    void set_team(Team t) { p_team = t; }

    friend const position2d_t position_of(Piece*);

            /* const references */
    const position2d_t& pos{ atPos };
    const Type& type{ p_type };
	const Team& team{ p_team };
        
            /* the innate properties of a Piece */
protected:
	position2d_t atPos{};
	cardinal facing{ cardinal::null };
	Team p_team{ Team::null };
	Type p_type{ Type::null };
	bool initPos{ true };
};

 // simple utility function to (loudly)
// grab the position of a piece

inline const position2d_t position_of(Piece* piece) { return piece->atPos; }

        /* each Piece type is its own class */
class King : public Piece {
public:
	King(const pos_t& pos_x, const pos_t& pos_y) :
		Piece(Type::king, pos_x, pos_y)
	{}

	King(const position2d_t& pos) :
		King(pos.x, pos.y)
	{}
    
    King() :
        Piece(Type::king)
    {}

	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Queen : public Piece {
public:
	Queen(const pos_t& pos_x, const pos_t& pos_y) :
		Piece(Type::queen, pos_x, pos_y)
	{}

	Queen(const position2d_t& pos) :
		Queen(pos.x, pos.y)
	{}
    
    Queen() :
        Piece(Type::queen)
    {}

	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Bishop : public Piece {
public:
	Bishop(const pos_t& pos_x, const pos_t& pos_y) :
		Piece(Type::bishop, pos_x, pos_y)
	{}

	Bishop(const position2d_t& pos) :
		Bishop(pos.x, pos.y)
	{}
    
    Bishop() :
        Piece(Type::bishop)
    {}

	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Knight : public Piece {
public:
	Knight(const pos_t& pos_x, const pos_t& pos_y) :
		Piece(Type::knight, pos_x, pos_y)
	{}

	Knight(const position2d_t& pos) :
		Knight(pos.x, pos.y)
	{}
    
    Knight():
        Piece(Type::knight)
    {}

	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Rook : public Piece {
public:
	Rook(const pos_t& pos_x, const pos_t& pos_y) :
		Piece(Type::rook, pos_x, pos_y)
	{}

	Rook(const position2d_t& pos) :
		Rook(pos.x, pos.y)
	{}
    
    Rook() :
        Piece(Type::rook)
    {}
	
	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

class Pawn : public Piece {
public:
	Pawn(const pos_t& pos_x, const pos_t& pos_y, const direction& _face) :
		Piece(Type::pawn, pos_x, pos_y)
    {}

	Pawn(const position2d_t& pos, const direction& _face) :
		Pawn(pos.x, pos.y, _face)
	{}
    
    Pawn(const pos_t& _x, const pos_t& _y) :
        Piece(Type::pawn, _x, _y)
    {}
    
    Pawn() :
        Piece(Type::pawn)
    {}

	bool canMove(const position2d_t&);
	bool canMove(const pos_t x, const pos_t y) {
        return canMove({x, y});
    }
};

#endif
